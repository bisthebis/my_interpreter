#include "token.h"

Token::Token(TokenType type, QString lexeme, QVariant value, int line) :
    type(type),
    lexeme(lexeme),
    value(value),
    line(line)
{
}
