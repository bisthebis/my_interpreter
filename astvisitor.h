#ifndef ASTVISITOR_H
#define ASTVISITOR_H

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
};
}
#endif // ASTVISITOR_H
