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
        throw MyException(QStringLiteral("Syntax Error : ") + err);

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
    return Node(new ASTLetStatement(variableName, expr));
}
RecursiveDescentParser::Node RecursiveDescentParser::parsePrint()
{
    //"print" token as already been consumed
    QString variableName = it->value.toString();
    expect(Token::IDENTIFIER, QStringLiteral("Expected identifier following print"));
    return Node(new ASTPrintStatement(variableName));
}
RecursiveDescentParser::Node RecursiveDescentParser::parseExpression()
{
    QVariant value;
    if (accept(Token::IDENTIFIER))
    {
        expect(Token::END_OF_STATEMENT, QStringLiteral("Arithmetic unsupported yet"));
        return Node(new ASTVariable(value.toString()));
    }
    if (accept(Token::NUMBER))
    {
        expect(Token::END_OF_STATEMENT, QStringLiteral("Arithmetic unsupported yet"));
        return Node(new ASTNumber(value.toDouble()));
    }
    throw MyException("Expression must (at the moment) start by an identifier or a number");
}

RecursiveDescentParser::Node RecursiveDescentParser::parse() const {


    return Node(nullptr);
}




}

