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
public:
    RecursiveDescentParser(const QVector<Token>& t);
    QSharedPointer<ASTNode> parse() const;
};




} // end namespace



#endif // RECURSIVEDESCENTPARSER_H
