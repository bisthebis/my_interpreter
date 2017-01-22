#ifndef TOKEN_H
#define TOKEN_H

#include <QString>
#include <QVariant>

struct Token
{
public:
    enum TokenType {
        PLUS, MINUS, TIMES, SLASH, EQUAL,

        LET, PRINT,

        IDENTIFIER, NUMBER
    };


public:
    Token(TokenType type, QString lexeme, QVariant value, int line);
    QString toString() const;

    const TokenType type;
    const QString lexeme;
    const QVariant value;
    const int line;
};

#endif // TOKEN_H
