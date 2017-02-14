#include "recursivedescentparser.h"
#include "astnode.h"
#include <QString>
#include <QQueue>

namespace RecursiveDescent {
RecursiveDescentParser::RecursiveDescentParser(const QVector<Token>& t) : tokens(t), it(t.begin()), end(t.end()) {
    if (it == end)
        throw MyException("Empty token list !");
}

bool RecursiveDescentParser::accept(Token::TokenType t)
{
    if (peek() == t)
    {
        ++it;
        return true;
    }
    return false;
}
void RecursiveDescentParser::expect(Token::TokenType t, QString err)
{
    if (peek() != t)
        throw MyException(QStringLiteral("Syntax Error : ") + err + QString(" at line %1").arg(it->line));

    it++;
    return;
}

RecursiveDescentParser::Node RecursiveDescentParser::parseInstruction()
{
    while (accept(Token::END_OF_STATEMENT)) //Many ; are allowed between statements
        continue;
    if (accept(Token::LET))
        return parseAssignment();
    if (accept(Token::PRINT))
        return parsePrint();

    throw MyException(QString("Statement beginning with neither print or let at line %1. Received token %2").arg(it->line).arg(it->lexeme));
}

RecursiveDescentParser::Node RecursiveDescentParser::parseAssignment()
{
    //Since it is called by parseInstruction, "let" token as already been consumed
    QString variableName = it->value.toString();
    expect(Token::IDENTIFIER, QStringLiteral("'Let' expects identifier"));
    expect(Token::EQUAL, QStringLiteral("Expected '=' after identifier in let statement"));
    Node expr = parseExpression();
    //End of statement is not required because parseExpression consumes it
    return Node(new ASTLetStatement(variableName, expr));
}
RecursiveDescentParser::Node RecursiveDescentParser::parsePrint()
{
    //"print" token as already been consumed
    QString variableName = it->value.toString();
    expect(Token::IDENTIFIER, QStringLiteral("Expected identifier following print"));
    expect(Token::END_OF_STATEMENT, QStringLiteral("Expected semicolon"));
    return Node(new ASTPrintStatement(variableName));
}
RecursiveDescentParser::Node RecursiveDescentParser::parseFunctionCall(const QString& name) {
    //left parenthesis has already been consumed
    QVector<Node> args;
    args.append(parseExpression());
    while (!accept(Token::RIGHT_PAREN))
    {
        expect(Token::COMMA, QStringLiteral("Function args must be separated by commas ','."));
        args.append(parseExpression());
    }
    throw MyException(QString("Unimplemented function '%2' call with %1 parameters").arg(args.size()).arg(name));
}

RecursiveDescentParser::Node RecursiveDescentParser::parseAtom() {
    //exponent (one day ?)
    QVariant value = it->value;
    Node lhs;
    if (accept(Token::IDENTIFIER)) {
        //If it's followed by a parenthesis, it's a func call. Otherwise it's a variable
        if (!accept(Token::LEFT_PAREN))
            lhs = Node(new ASTVariable(value.toString()));
        else return parseFunctionCall(value.toString());
    }
    if (accept(Token::NUMBER)) {
        lhs = Node(new ASTNumber(value.toDouble()));
    }
    if (accept(Token::LEFT_PAREN)) {
        lhs = parseExpression();
        expect(Token::RIGHT_PAREN, QStringLiteral("Expected end of parenthesis"));
    }

    if (accept(Token::EXPONENT))
    {
        auto rhs = parseAtom();
        return Node(new ASTExponent(lhs, rhs));
    }
    else return lhs;

    throw MyException("Atom that is neither id, number, or expression within parenthesis");

}

RecursiveDescentParser::Node RecursiveDescentParser::parseTerm() {
    auto lhs = parseAtom();
    if (accept(Token::TIMES)) {
        return Node(new ASTTimes(lhs, parseAtom()));
    }
    if (accept(Token::SLASH)) {
        return Node(new ASTSlash(lhs, parseAtom()));
    }
    return lhs;
}
//Helper for parseExpression
RecursiveDescentParser::Node RecursiveDescentParser::processTerms(QQueue<RecursiveDescentParser::Node>& terms, QQueue<Token::TokenType>& ops) {
    if (ops.size() == 0) throw MyException("Received no operators !");
    switch (terms.size()) {
    case 0:
        throw MyException("Empty list of terms in parsing !");
        break;
    case 1:
        return terms.head();
        break;
    case 2:
    {
        auto lhs = terms.dequeue();
        auto rhs = terms.dequeue();
        auto op = ops.dequeue();
        if (op == Token::PLUS)
            return RecursiveDescentParser::Node(new ASTPlus(lhs, rhs));
        else if (op == Token::MINUS)
            return RecursiveDescentParser::Node(new ASTMinus(lhs, rhs));
        else throw MyException("Neither + or -");
    }
        break;
    default: //Recursive case
    {
        auto lhs = terms.dequeue();
        auto rhs = terms.head(); // rhs will be replaced by (lhs +/- rhs) in the queue, so it's not deleted
        auto op = ops.dequeue();
        auto newHead = [&]() {
            if (op == Token::PLUS)
                return RecursiveDescentParser::Node(new ASTPlus(lhs, rhs));
            else if (op == Token::MINUS)
                return RecursiveDescentParser::Node(new ASTMinus(lhs, rhs));
            else throw MyException("Neither + or -");
        }();
        terms.head().swap(newHead);
        return processTerms(terms, ops);
    }
        break;
    }

}
RecursiveDescentParser::Node RecursiveDescentParser::parseExpression() {
    //Create list of terms && ops, then consume it in FIFO (fort left associativity)
    if (accept(Token::IF))
    {
        auto cond = parseBool();
        expect(Token::THEN, QStringLiteral("Expected \"then\" after a condition."));
        auto then = parseExpression();
        expect(Token::ELSE, QStringLiteral("Expected \"else\" statement"));
        auto otherwise = parseExpression();
        expect(Token::ENDIF, QStringLiteral("Expected \"endif\" after a condition"));
        return Node(new ASTCond(cond, then, otherwise));
    }
    else
    {
        QQueue<Node> terms;
        terms.append(parseTerm());
        QQueue<Token::TokenType> operators; //Only + or -
        do {
            if (accept(Token::PLUS))
                operators.append(Token::PLUS);
            else if (accept(Token::MINUS))
                operators.append(Token::MINUS);
            else
                return terms.head();

            terms.append(parseTerm());
        } while (peek() == Token::PLUS || peek() == Token::MINUS);


        return processTerms(terms, operators);
    }
}

RecursiveDescentParser::Node RecursiveDescentParser::parseBool()
{
    if (!accept(Token::LEFT_PAREN))
    {
        return parseExpression();
    }
    else {
        auto lhs = parseExpression();
        auto opToken = peek(); ++it;
        auto rhs = parseExpression();

        expect(Token::RIGHT_PAREN, QStringLiteral("Expected comparison to be between parenthesis"));

        if (opToken != Token::EQ && opToken != Token::NEQ && opToken != Token::GREATER_OR_EQUAL && opToken != Token::GT && opToken != Token::LESS_OR_EQUAL && opToken != Token::LT)
            throw MyException("boolean expression must use either ==, !=, <, <=, >, >= between members");

        ASTComparison::Comparator op;

        switch (opToken) {
        case Token::EQ:
            op = ASTComparison::EQ;
            break;
        case Token::NEQ:
            op = ASTComparison::NEQ;
            break;
        case Token::GT:
            op = ASTComparison::GT;
            break;
        case Token::LT:
            op = ASTComparison::LT;
            break;
        case Token::LESS_OR_EQUAL:
            op = ASTComparison::LT;
            break;
        case Token::GREATER_OR_EQUAL:
            op = ASTComparison::GT;
            break;
        default:
            throw MyException("Error in parseBool : unexpected comparison operator");
            break;
        }

        return Node(new ASTComparison(lhs, rhs, op));
        }

}


RecursiveDescentParser::Node RecursiveDescentParser::parse() {
    QVector<Node> program;
    do {
        auto instruction = parseInstruction();
        program.append(instruction);
    } while (it != end);

    return QSharedPointer<ASTNode>(new ASTProgram(program));
}




}

