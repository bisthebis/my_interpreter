#ifndef ASTVISITOR_H
#define ASTVISITOR_H

#include "myexception.h"

namespace RecursiveDescent {

struct ASTProgram;
struct ASTLetStatement;
struct ASTPrintStatement;
struct ASTPlus;
struct ASTMinus;
struct ASTTimes;
struct ASTSlash;
struct ASTNumber;
struct ASTVariable;
struct ASTExponent;
struct ASTCond;
struct ASTComparison;
struct ASTFunctionCall;

class ASTVisitor
{
public:
    ASTVisitor() {}
    virtual ~ASTVisitor(){}
    virtual void visitProgram(ASTProgram& p) = 0;
    virtual void visitLetStatement(ASTLetStatement& p) = 0;
    virtual void visitPrintStatement(ASTPrintStatement& p) = 0;
    virtual void visitPlus(ASTPlus& p) = 0;
    virtual void visitMinus(ASTMinus& p) = 0;
    virtual void visitTimes(ASTTimes& p) = 0;
    virtual void visitSlash(ASTSlash& p) = 0;
    virtual void visitNumber(ASTNumber& p) = 0;
    virtual void visitVariable(ASTVariable& p) = 0;
    virtual void visitExponent(ASTExponent& p) = 0;
    virtual void visitCond(ASTCond& p) = 0;
    virtual void visitComparison(ASTComparison& p) = 0;
    virtual void visitFunctionCall(ASTFunctionCall& p) {Q_UNUSED(p); throw MyException("Unimplemented !");}
};
}
#endif // ASTVISITOR_H
