#ifndef AST_C_TRANSPILER_H
#define AST_C_TRANSPILER_H


#include "astnode.h"
#include "astvisitor.h"
#include <QString>
#include <QStringList>


class AST_C_Transpiler : public RecursiveDescent::ASTVisitor
{
public:
    AST_C_Transpiler(QString file);
    virtual ~AST_C_Transpiler(){}
    virtual void visitProgram(RecursiveDescent::ASTProgram& p) Q_DECL_OVERRIDE;
    virtual void visitLetStatement(RecursiveDescent::ASTLetStatement& p) Q_DECL_OVERRIDE;
    virtual void visitPrintStatement(RecursiveDescent::ASTPrintStatement& p) Q_DECL_OVERRIDE;
    virtual void visitPlus(RecursiveDescent::ASTPlus& p) Q_DECL_OVERRIDE;
    virtual void visitMinus(RecursiveDescent::ASTMinus& p) Q_DECL_OVERRIDE;
    virtual void visitTimes(RecursiveDescent::ASTTimes& p) Q_DECL_OVERRIDE;
    virtual void visitSlash(RecursiveDescent::ASTSlash& p) Q_DECL_OVERRIDE;
    virtual void visitNumber(RecursiveDescent::ASTNumber& p) Q_DECL_OVERRIDE;
    virtual void visitVariable(RecursiveDescent::ASTVariable& p) Q_DECL_OVERRIDE;
    virtual void visitExponent(RecursiveDescent::ASTExponent &p) Q_DECL_OVERRIDE;
    virtual void visitCond(RecursiveDescent::ASTCond &p) Q_DECL_OVERRIDE;
    virtual void visitComparison(RecursiveDescent::ASTComparison &p) Q_DECL_OVERRIDE;
private:
    QString currentExpr;
    QString targetFile;
    QStringList content;
    bool mustIncludeMathHeader = true; //Assumed until opposite gets implemented

};



#endif // AST_C_TRANSPILER_H
