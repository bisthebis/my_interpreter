#ifndef ASTNODE_H
#define ASTNODE_H

#include "astvisitor.h"
#include <QVector>
#include <QString>
#include <QSharedPointer>

namespace RecursiveDescent {

struct ASTNode {
    virtual void accept(ASTVisitor& v) = 0;
    virtual ~ASTNode(){}
};

using Node = QSharedPointer<ASTNode>;

struct ASTProgram : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitProgram(*this);}
    ASTProgram(QVector<Node> data) : instructions(data){}
    QVector<Node> instructions;
};

struct ASTLetStatement : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitLetStatement(*this);}
    ASTLetStatement(QString v, Node e) : varName(v), expression(e){}
    QString varName;
    Node expression;
};

struct ASTPrintStatement : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitPrintStatement(*this);}
    ASTPrintStatement(QString v) : varName(v) {}
    QString varName;
};

struct ASTPlus : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitPlus(*this);}
    Node lhs, rhs;
    ASTPlus(Node l, Node r) : lhs(l), rhs(r) {}
};

struct ASTMinus : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitMinus(*this);}
    Node lhs, rhs;
    ASTMinus(Node l, Node r) : lhs(l), rhs(r) {}
};

struct ASTTimes : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitTimes(*this);}
    Node lhs, rhs;
    ASTTimes(Node l, Node r) : lhs(l), rhs(r) {}
};

struct ASTSlash : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitSlash(*this);}
    Node lhs, rhs;
    ASTSlash(Node l, Node r) : lhs(l), rhs(r) {}
};

struct ASTExponent : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitExponent(*this);}
    Node lhs, rhs;
    ASTExponent(Node l, Node r) : lhs(l), rhs(r) {}
};

struct ASTVariable : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitVariable(*this);}
    ASTVariable(QString v) : varName(v) {}
    QString varName;
};

struct ASTNumber : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitNumber(*this);}
    const double value;
    ASTNumber (double v) : value(v) {}
};

struct ASTCond : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitCond(*this);}
    Node cond, then, otherwise;
    ASTCond(Node c, Node t, Node o) : cond(c), then(t), otherwise(o){}
};

struct ASTComparison : ASTNode {
    enum Comparator {EQ, NEQ, GT, GET, LT, LET};
    Node lhs, rhs;
    Comparator op;
    virtual void accept(ASTVisitor& v) {v.visitComparison(*this);}
    ASTComparison(Node lhs, Node rhs, Comparator comp) : lhs(lhs), rhs(rhs), op(comp) {}
};

struct ASTFunctionCall : ASTNode {
    QString fname;
    QVector<Node> args;
    ASTFunctionCall(QString name, QVector<Node> args) : fname(name), args(args) {}
    virtual void accept(ASTVisitor&v) {v.visitFunctionCall(*this);}
};

}
#endif // ASTNODE_H
