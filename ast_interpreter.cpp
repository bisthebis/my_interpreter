#include "ast_interpreter.h"
#include "myexception.h"
#include <QFile>
#include <QtCore>

using namespace RecursiveDescent;

ASTInterpreter::ASTInterpreter(QTextStream& stream) : stream(stream)
{

}

void ASTInterpreter::visitProgram(ASTProgram &p)
{

}

void ASTInterpreter::visitLetStatement(ASTLetStatement &p)
{
    if (environment.contains(p.varName))
        throw MyException("Assigning previously defined variable !");
    environment[p.varName] = 0;//Evaluate expression !
}

void ASTInterpreter::visitPrintStatement(ASTPrintStatement &p)
{
    if (!environment.contains(p.varName))
        throw MyException("Printing unreferenced variable !");
    stream << QString("%1 = %2").arg(p.varName).arg(environment[p.varName]);
}

void ASTInterpreter::visitVariable(ASTVariable &p)
{

}

void ASTInterpreter::visitNumber(ASTNumber &p)
{

}

void ASTInterpreter::visitPlus(ASTPlus &p)
{

}

void ASTInterpreter::visitMinus(ASTMinus &p)
{

}

void ASTInterpreter::visitTimes(ASTTimes &p)
{

}

void ASTInterpreter::visitSlash(ASTSlash &p)
{
    //TODO : exception when dividing by 0

}
