#ifndef RECURSIVEDESCENTPARSER_H
#define RECURSIVEDESCENTPARSER_H

#include "myexception.h"
#include "token.h"
#include <QSharedPointer>
#include <QScopedPointer>
#include "astvisitor.h"
#include "astnode.h"

namespace RecursiveDescent {

class RecursiveDescentParser
{
private:
    const QVector<Token>& tokens;
    QVector<Token>::const_iterator it;
    const QVector<Token>::const_iterator end;
    bool accept(Token::TokenType t) const; //Checks whether the current token is a t, and advance it if it's true
    void expect(Token::TokenType t, QString err) const; //Checks if current token is a t, and throw Exception if it's not
public:
    RecursiveDescentParser(const QVector<Token>& t);
    QSharedPointer<ASTNode> parse() const;
};




} // end namespace



#endif // RECURSIVEDESCENTPARSER_H
