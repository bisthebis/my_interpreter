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

struct ASTProgram : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitProgram(*this);}
    ASTProgram(QVector<QSharedPointer<ASTNode>> data) : instructions(data){}
    QVector<QSharedPointer<ASTNode>> instructions;
};

struct ASTLetStatement : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitLetStatement(*this);}
    ASTLetStatement(QString v, QSharedPointer<ASTNode> e) : varName(v), expression(e){}
    QString varName;
    QSharedPointer<ASTNode> expression;
};

struct ASTPrintStatement : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitPrintStatement(*this);}
    ASTPrintStatement(QString v) : varName(v) {}
    QString varName;
};

struct ASTPlus : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitPlus(*this);}
    QSharedPointer<ASTNode> lhs, rhs;
    ASTPlus(QSharedPointer<ASTNode> l, QSharedPointer<ASTNode> r) : lhs(l), rhs(r) {}
};

struct ASTMinus : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitMinus(*this);}
    QSharedPointer<ASTNode> lhs, rhs;
    ASTMinus(QSharedPointer<ASTNode> l, QSharedPointer<ASTNode> r) : lhs(l), rhs(r) {}
};

struct ASTTimes : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitTimes(*this);}
    QSharedPointer<ASTNode> lhs, rhs;
    ASTTimes(QSharedPointer<ASTNode> l, QSharedPointer<ASTNode> r) : lhs(l), rhs(r) {}
};

struct ASTSlash : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitSlash(*this);}
    QSharedPointer<ASTNode> lhs, rhs;
    ASTSlash(QSharedPointer<ASTNode> l, QSharedPointer<ASTNode> r) : lhs(l), rhs(r) {}
};

struct ASTExponent : ASTNode {
    virtual void accept(ASTVisitor& v) {v.visitExponent(*this);}
    QSharedPointer<ASTNode> lhs, rhs;
    ASTExponent(QSharedPointer<ASTNode> l, QSharedPointer<ASTNode> r) : lhs(l), rhs(r) {}
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
    QSharedPointer<ASTNode> cond, then, otherwise;
    ASTCond(QSharedPointer<ASTNode> c, QSharedPointer<ASTNode> t, QSharedPointer<ASTNode> o) : cond(c), then(t), otherwise(o){}
};

struct ASTComparison : ASTNode {
    enum Comparator {EQ, NEQ, GT, GET, LT, LET};
    QSharedPointer<ASTNode> lhs, rhs;
    virtual void accept(ASTVisitor& v) {v.visitComparison(*this);}
    ASTComparison(QSharedPointer<ASTNode> lhs, QSharedPointer<ASTNode> rhs, Comparator comp);
};

}
#endif // ASTNODE_H
