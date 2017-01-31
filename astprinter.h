#ifndef ASTPRINTER_H
#define ASTPRINTER_H

#include "astnode.h"
#include "astvisitor.h"
#include <QString>
#include <QSet>
#include <QStringList>


namespace RecursiveDescent {

class ASTPrinter : public ASTVisitor
{
public:
    ASTPrinter();
    virtual ~ASTPrinter(){}
    virtual void visitProgram(ASTProgram& p) Q_DECL_OVERRIDE;
    virtual void visitLetStatement(ASTLetStatement& p) Q_DECL_OVERRIDE;
    virtual void visitPrintStatement(ASTPrintStatement& p) Q_DECL_OVERRIDE;
    virtual void visitPlus(ASTPlus& p) Q_DECL_OVERRIDE;
    virtual void visitMinus(ASTMinus& p) Q_DECL_OVERRIDE;
    virtual void visitTimes(ASTTimes& p) Q_DECL_OVERRIDE;
    virtual void visitSlash(ASTSlash& p) Q_DECL_OVERRIDE;
    virtual void visitNumber(ASTNumber& p) Q_DECL_OVERRIDE;
    virtual void visitVariable(ASTVariable& p) Q_DECL_OVERRIDE;
private:
    QSet<QString> identifiers;
    QStringList semanticErrors;

};



}
#endif // ASTPRINTER_H
