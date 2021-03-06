#include "astprinter.h"
#include <QtDebug>

namespace RecursiveDescent {

ASTPrinter::ASTPrinter() : hadErrors(false)
{
}

void ASTPrinter::visitProgram(ASTProgram &p)
{
    qDebug() << "Visiting program...";
    for (auto& instruction : p.instructions) // Instruction is a shared pointer to node
        instruction->accept(*this);

    if (!semanticErrors.empty())
        {
            qDebug() << "Some errors where found : " << semanticErrors;
            hadErrors = true;
        }
}

void ASTPrinter::visitLetStatement(ASTLetStatement &p)
{
    qDebug() << "Visiting assigmnent. Variable assigned is : " << p.varName;
    if (identifiers.contains(p.varName))
        semanticErrors << QString("Reassigning variable %1").arg(p.varName);
    else
        identifiers.insert(p.varName);
    p.expression->accept(*this);
}

void ASTPrinter::visitPrintStatement(ASTPrintStatement &p)
{
    if (!identifiers.contains(p.varName))
        semanticErrors << QString("Printing undeclared variable %1").arg(p.varName);
    qDebug() << "Visiting print statement. Variable shown is : " << p.varName;
}

void ASTPrinter::visitVariable(ASTVariable &p)
{
    qDebug() << "Visiting variable : " << p.varName;
}

void ASTPrinter::visitNumber(ASTNumber &p)
{
    qDebug() << "Visiting number literal : " << p.value;
}

void ASTPrinter::visitPlus(ASTPlus &p)
{
    qDebug() << "Visiting addition... Subexpressions are going to be visited";
    p.lhs->accept(*this);
    p.rhs->accept(*this);
}

void ASTPrinter::visitMinus(ASTMinus &p)
{
    qDebug() << "Visiting substraction... Subexpressions are going to be visited";
    p.lhs->accept(*this);
    p.rhs->accept(*this);
}

void ASTPrinter::visitTimes(ASTTimes &p)
{
    qDebug() << "Visiting multiplication... Subexpressions are going to be visited";
    p.lhs->accept(*this);
    p.rhs->accept(*this);
}

void ASTPrinter::visitSlash(ASTSlash &p)
{
    qDebug() << "Visiting division... Subexpressions are going to be visited";
    p.lhs->accept(*this);
    p.rhs->accept(*this);
}

void ASTPrinter::visitExponent(ASTExponent &p)
{
    qDebug() << "Visiting exponentiation... Subexpressions are going to be visited";
    p.lhs->accept(*this);
    p.rhs->accept(*this);
}

void ASTPrinter::visitCond(ASTCond &p)
{
    qDebug() << "Visiting condition. Condition, then true case and false case will be visited";
    p.cond->accept(*this);
    p.then->accept(*this);
    p.otherwise->accept(*this);
}

void ASTPrinter::visitComparison(ASTComparison &p)
{
    qDebug() << "Visiting condition. LHS and RHS will be shown. Comparsion operator is : " << p.op;
    p.lhs->accept(*this);
    p.rhs->accept(*this);
}

void ASTPrinter::visitFunctionCall(ASTFunctionCall &p)
{
    qDebug() << "Visiting function call. Name is : " << p.fname << ". It has " << p.args.size() << " elements : ";
    for (auto& arg : p.args)
        arg->accept(*this);
}


}
