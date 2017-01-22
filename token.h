#ifndef TOKEN_H
#define TOKEN_H

#include <QString>
#include <QVariant>

class Token
{
public:
    enum TokenType {
        PLUS, MINUS, TIMES, SLASH, EQUAL,

        LET, PRINT,

        IDENTIFIER, NUMBER
    };

    Token();

private:
    const TokenType type;
    const QString lexeme;
    const QVariant value;
    const int line;
};

#endif // TOKEN_H
