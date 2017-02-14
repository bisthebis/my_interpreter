#ifndef AST_INTERPRETER_H
#define AST_INTERPRETER_H

#include "astnode.h"
#include "astvisitor.h"
#include <QString>
#include <QMap>
#include <QTextStream>

class ASTInterpreter : public RecursiveDescent::ASTVisitor
{
public:
    ASTInterpreter(QTextStream& stream);
    virtual ~ASTInterpreter(){}
    virtual void visitProgram(RecursiveDescent::ASTProgram& p) Q_DECL_OVERRIDE;
    virtual void visitLetStatement(RecursiveDescent::ASTLetStatement& p) Q_DECL_OVERRIDE;
    virtual void visitPrintStatement(RecursiveDescent::ASTPrintStatement& p) Q_DECL_OVERRIDE;
    virtual void visitPlus(RecursiveDescent::ASTPlus& p) Q_DECL_OVERRIDE;
    virtual void visitMinus(RecursiveDescent::ASTMinus& p) Q_DECL_OVERRIDE;
    virtual void visitTimes(RecursiveDescent::ASTTimes& p) Q_DECL_OVERRIDE;
    virtual void visitSlash(RecursiveDescent::ASTSlash& p) Q_DECL_OVERRIDE;
    virtual void visitNumber(RecursiveDescent::ASTNumber& p) Q_DECL_OVERRIDE;
    virtual void visitVariable(RecursiveDescent::ASTVariable& p) Q_DECL_OVERRIDE;
    virtual void visitExponent(RecursiveDescent::ASTExponent& p) Q_DECL_OVERRIDE;
    virtual void visitCond(RecursiveDescent::ASTCond &p) Q_DECL_OVERRIDE;
    virtual void visitComparison(RecursiveDescent::ASTComparison &p) Q_DECL_OVERRIDE;
    virtual void visitFunctionCall(RecursiveDescent::ASTFunctionCall &p) Q_DECL_OVERRIDE;
private:
    QMap<QString, double> environment;
    QTextStream& stream;
    double buffer; //For visiting expressions;

};



#endif // AST_INTERPRETER_H
