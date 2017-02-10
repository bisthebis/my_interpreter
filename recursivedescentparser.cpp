#include "recursivedescentparser.h"
#include "astnode.h"
#include <QString>

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
RecursiveDescentParser::Node RecursiveDescentParser::parseAtom() {
    //Todo parenthesis && exponent (one day ?)
    QVariant value = it->value;
    if (accept(Token::IDENTIFIER)) {
        return Node(new ASTVariable(value.toString()));
    }
    if (accept(Token::NUMBER)) {
        return Node(new ASTNumber(value.toDouble()));
    }
    throw MyException("Atom that is neither id or number");

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

RecursiveDescentParser::Node RecursiveDescentParser::parseExpression() {
    auto lhs = parseTerm();
    if (accept(Token::PLUS)) {
        return Node(new ASTPlus(lhs, parseExpression()));
    }
    if (accept(Token::MINUS)) {
        return Node(new ASTMinus(lhs, parseExpression()));
    }
    return lhs;
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

