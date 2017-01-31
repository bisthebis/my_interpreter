#include "astprinter.h"
#include <QtDebug>

namespace RecursiveDescent {

ASTPrinter::ASTPrinter()
{
}

void ASTPrinter::visitProgram(ASTProgram &p)
{
    qDebug() << "Visiting program...";
    for (auto& instruction : p.instructions) // Instruction is a shared pointer to node
        instruction->accept(*this);
}

void ASTPrinter::visitLetStatement(ASTLetStatement &p)
{
    qDebug() << "Visiting assigmnent. Variable assigned is : " << p.varName;
    p.expression->accept(*this);
}

void ASTPrinter::visitPrintStatement(ASTPrintStatement &p)
{
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






}
