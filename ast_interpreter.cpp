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
    for (auto& instruction : p.instructions)
        {
            instruction->accept(*this);
        }

}

void ASTInterpreter::visitLetStatement(ASTLetStatement &p)
{
    if (environment.contains(p.varName))
        throw MyException("Assigning previously defined variable !");
    p.expression->accept(*this);
    environment[p.varName] = buffer;//Evaluate expression !
}

void ASTInterpreter::visitPrintStatement(ASTPrintStatement &p)
{
    if (!environment.contains(p.varName))
        throw MyException("Printing unreferenced variable !");
    stream << QString("%1 = %2").arg(p.varName).arg(environment[p.varName]) << endl;
}

void ASTInterpreter::visitVariable(ASTVariable &p)
{
    if (!environment.contains(p.varName))
        throw MyException("Using undefined variable");

    buffer = environment[p.varName];
}

void ASTInterpreter::visitNumber(ASTNumber &p)
{
    buffer = p.value;
}

void ASTInterpreter::visitPlus(ASTPlus &p)
{
    p.lhs->accept(*this);
    double lhs = buffer;
    p.rhs->accept(*this);
    buffer = lhs + buffer;
}

void ASTInterpreter::visitMinus(ASTMinus &p)
{
    p.lhs->accept(*this);
    double lhs = buffer;
    p.rhs->accept(*this);
    buffer = lhs - buffer;
}

void ASTInterpreter::visitTimes(ASTTimes &p)
{
    p.lhs->accept(*this);
    double lhs = buffer;
    p.rhs->accept(*this);
    buffer = lhs * buffer;
}

void ASTInterpreter::visitSlash(ASTSlash &p)
{
    p.lhs->accept(*this);
    double lhs = buffer;
    p.rhs->accept(*this);
    if (buffer == 0)
        throw MyException("Division by zero !");
    buffer = lhs / buffer;

}

void ASTInterpreter::visitExponent(ASTExponent &p)
{
    p.lhs->accept(*this);
    double lhs = buffer;
    p.rhs->accept(*this);
    if (lhs < 0)
        throw MyException("negative number as exponent base");
    buffer = pow(lhs, buffer);
}

void ASTInterpreter::visitCond(ASTCond &p) {
    p.cond->accept(*this);
    bool cond = buffer != 0;
    if (cond)
        p.then->accept(*this);
    else
        p.otherwise->accept(*this);

}

void ASTInterpreter::visitComparison(ASTComparison &p) {
    //evaluate lhs then rhs;
    p.lhs->accept(*this);
    double lhs = buffer;
    p.rhs->accept(*this);
    double rhs = buffer;
    bool result;
    switch (p.op) {
        case ASTComparison::EQ:
            result = lhs == rhs;
            break;
        case ASTComparison::NEQ:
            result = lhs != rhs;
            break;
        case ASTComparison::GT:
            result = lhs > rhs;
            break;
        case ASTComparison::LT:
            result = lhs < rhs;
            break;
        case ASTComparison::LET:
            result = lhs <= rhs;
            break;
        case ASTComparison::GET:
            result = lhs >= rhs;
            break;
        default: throw MyException("Unknown op !");
    }
    buffer = result ? 1 : 0;
}

void ASTInterpreter::visitFunctionCall(ASTFunctionCall &p) {
    if (p.fname == "sin")
    {
        p.args[0]->accept(*this);
        buffer = sin(buffer);
    }
    else throw MyException("Unknown func");
}
