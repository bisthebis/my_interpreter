#include "recursivedescentparser.h"
#include <QString>

namespace RecursiveDescent {
RecursiveDescentParser::RecursiveDescentParser(const QVector<Token>& t) : tokens(t), it(t.begin()), end(t.end()) {

}

bool RecursiveDescentParser::accept(Token::TokenType t) const
{
    if (it->type == t)
    {
        ++it;
        return true;
    }
    return false;
}
void RecursiveDescentParser::expect(Token::TokenType t, QString err) const
{
    if (it->type != t)
        throw MyException(QStringLiteral("Syntax Error : ") + err);
}

QSharedPointer<ASTNode> RecursiveDescentParser::parse() const {
    using TreePtr = QSharedPointer<ASTNode>;

    return TreePtr(nullptr);
}




}

