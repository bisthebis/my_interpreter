#include "token.h"
#include "myexception.h"

static QString typeToString(Token::TokenType type) {

#define SHOW(t) case t: \
                    return #t; \
                    break

    switch (type) {
    SHOW(Token::PLUS);
    SHOW(Token::MINUS);
    SHOW(Token::TIMES);
    SHOW(Token::SLASH);
    SHOW(Token::EQUAL);
    SHOW(Token::LET);
    SHOW(Token::PRINT);
    SHOW(Token::IDENTIFIER);
    SHOW(Token::NUMBER);
    SHOW(Token::END_OF_STATEMENT);
    SHOW(Token::LEFT_PAREN);
    SHOW(Token::RIGHT_PAREN);
    SHOW(Token::EXPONENT);
    SHOW(Token::IF);
    SHOW(Token::ELSE);
    SHOW(Token::THEN);
    SHOW(Token::ENDIF);
    SHOW(Token::GT);
    SHOW(Token::LT);
    SHOW(Token::EQ);
    SHOW(Token::NEQ);
    SHOW(Token::LESS_OR_EQUAL);
    SHOW(Token::COMMA);


    default:
        throw MyException("UNKNOW TOKEN TYPE");
        break;
    }

#undef SHOW
}

Token::Token(TokenType type, QString lexeme, QVariant value, int line) :
    type(type),
    lexeme(lexeme),
    value(value),
    line(line)
{
}

QString Token::toString() const
{
    return typeToString(type) + " : " + lexeme + ", " + value.toString();
}
