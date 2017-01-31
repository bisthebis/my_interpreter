#include "recursivedescentparser.h"

namespace RecursiveDescent {
RecursiveDescentParser::RecursiveDescentParser(const QVector<Token>& t) : tokens(t) {

}

QSharedPointer<ASTNode> RecursiveDescentParser::parse() const {
    using TreePtr = QSharedPointer<ASTNode>;

    return TreePtr(nullptr);
}




}

