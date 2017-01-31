#ifndef ASTNODE_H
#define ASTNODE_H

#include "astvisitor.h"

namespace RecursiveDescent {


struct ASTNode {
    virtual void accept(ASTVisitor& v) = 0;
    virtual ~ASTNode(){}
};

struct ASTProgram : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitProgram(*this);}
};

struct ASTLetStatement : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitLetStatement(*this);}
};

struct ASTPrintStatement : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitPrintStatement(*this);}
};

struct ASTPlus : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitPlus(*this);}
};

struct ASTMinus : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitMinus(*this);}
};

struct ASTTimes : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitTimes(*this);}
};

struct ASTSlash : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitSlash(*this);}
};

struct ASTVariable : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitVariable(*this);}
};

struct ASTNumber : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitNumber(*this);}
};

}
#endif // ASTNODE_H
