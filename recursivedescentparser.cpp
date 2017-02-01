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
    if (it->type == t)
    {
        ++it;
        return true;
    }
    return false;
}
void RecursiveDescentParser::expect(Token::TokenType t, QString err)
{
    if (it->type != t)
        throw MyException(QStringLiteral("Syntax Error : ") + err + QString(" at line %1").arg(it->line));

    it++;
    return;
}

RecursiveDescentParser::Node RecursiveDescentParser::parseInstruction()
{
    if (accept(Token::LET))
        return parseAssignment();
    if (accept(Token::PRINT))
        return parsePrint();

    throw MyException("Statement beginning with neither print or let");
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
RecursiveDescentParser::Node RecursiveDescentParser::parseExpression()
{
    //WARNING : at the moment, operator precedence is not implemented
    QVariant value = it->value;
    Node lhs;
    if (accept(Token::IDENTIFIER))
    {
        lhs = Node(new ASTVariable(value.toString()));
    }
    else if (accept(Token::NUMBER))
    {
        lhs =  Node(new ASTNumber(value.toDouble()));
    }
    else if (accept(Token::LEFT_PAREN))
    {
        if ((it+1)->type == Token::RIGHT_PAREN)
            {
                if (accept(Token::IDENTIFIER))
                {
                    value = (it-1)->value;
                    lhs = Node(new ASTVariable(value.toString()));
                }
                else if (accept(Token::NUMBER))
                {
                    value = (it-1)->value;
                    lhs =  Node(new ASTNumber(value.toDouble()));
                }
                expect(Token::RIGHT_PAREN, "Single arg parenthesis must end with a parentehsis end");
            }
    }
    else
    {
        throw MyException("Expecting expression to start with number or identifier");
    }

    //Now that lhs is known, decide what to do
    if (accept(Token::END_OF_STATEMENT))
        return lhs;
    else if (accept(Token::PLUS))
    {
        auto rhs = parseExpression();
        return Node(new ASTPlus(lhs, rhs));
    }
    else if (accept(Token::MINUS))
    {
        auto rhs = parseExpression();
        return Node(new ASTMinus(lhs, rhs));
    }
    else if (accept(Token::TIMES))
    {
        auto rhs = parseExpression();
        return Node(new ASTTimes(lhs, rhs));
    }
    else if (accept(Token::SLASH))
    {
        auto rhs = parseExpression();
        return Node(new ASTSlash(lhs, rhs));
    }
    else throw MyException("Expression expects operand or semicolong");

    throw MyException("Expression must (at the moment) start by an identifier or a number");
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

