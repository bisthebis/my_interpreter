#ifndef TOKEN_H
#define TOKEN_H

#include <QString>
#include <QVariant>

struct Token
{
public:
    enum TokenType {
        PLUS, MINUS, TIMES, SLASH, EQUAL, END_OF_STATEMENT, LEFT_PAREN, RIGHT_PAREN, EXPONENT,

        LET, PRINT,

        IDENTIFIER, NUMBER, //An identifier starts by a letter or _ and an number is a double
        INCORRECT_TOKEN
    };


public:
    Token(TokenType type = INCORRECT_TOKEN, QString lexeme = "Default constructed token. ERROR", QVariant value = "Error", int line = -1);
    QString toString() const;

    TokenType type;
    QString lexeme;
    QVariant value;
    int line;
};

#endif // TOKEN_H
