#include "ast_c_transpiler.h"
#include "myexception.h"
#include <QFile>
#include <QtCore>

using namespace RecursiveDescent;

AST_C_Transpiler::AST_C_Transpiler(QString file) : targetFile(file)
{
    if (!mustIncludeMathHeader)
        content << "#include <stdio.h>\n" << "\n" << "int main(void) \n" << "{\n";
    else
        content << "#include <stdio.h>\n" << "#include <math.h>\n" << "\n" << "int main(void) \n" << "{\n";
}

void AST_C_Transpiler::visitProgram(ASTProgram &p)
{
    QFile file(targetFile);
    if (!file.open(QIODevice::WriteOnly))
        throw MyException("Couldn't open file : " + targetFile);

    for (auto& instruction : p.instructions) // Instruction is a shared pointer to node
        instruction->accept(*this);

    content << "return 0; \n" << "} \n";
    QTextStream stream(&file);
    for (auto& s : content)
        {
            stream << s;
        }
    qDebug() << "Writtent to file : " << targetFile;
}

void AST_C_Transpiler::visitLetStatement(ASTLetStatement &p)
{
    currentExpr ="";
    p.expression->accept(*this);
    QString line = "\tconst double " + p.varName + " =" + currentExpr + ";\n";
    content << line;
}

void AST_C_Transpiler::visitPrintStatement(ASTPrintStatement &p)
{
    content << QString("\tprintf(\"%f\\n\", %1)").arg(p.varName) + ";\n";
}

void AST_C_Transpiler::visitVariable(ASTVariable &p)
{
    currentExpr += QString(" %1 ").arg(p.varName);
}

void AST_C_Transpiler::visitNumber(ASTNumber &p)
{
    currentExpr += QString(" %1 ").arg(p.value);
}

void AST_C_Transpiler::visitPlus(ASTPlus &p)
{
    currentExpr += " (";
    p.lhs->accept(*this);
    currentExpr += "+";
    p.rhs->accept(*this);
    currentExpr += ") ";
}

void AST_C_Transpiler::visitMinus(ASTMinus &p)
{
    currentExpr += " (";
    p.lhs->accept(*this);
    currentExpr += "-";
    p.rhs->accept(*this);
    currentExpr += ") ";
}

void AST_C_Transpiler::visitTimes(ASTTimes &p)
{
    currentExpr += " (";
    p.lhs->accept(*this);
    currentExpr += "*";
    p.rhs->accept(*this);
    currentExpr += ") ";
}

void AST_C_Transpiler::visitSlash(ASTSlash &p)
{
    currentExpr += " (";
    p.lhs->accept(*this);
    currentExpr += "/";
    p.rhs->accept(*this);
    currentExpr += ") ";

}

void AST_C_Transpiler::visitExponent(ASTExponent &p)
{
    currentExpr += " (pow(";
    p.lhs->accept(*this);
    currentExpr += ", ";
    p.rhs->accept(*this);
    currentExpr += "))";
}

void AST_C_Transpiler::visitCond(ASTCond &p) {
    currentExpr += " (";
    p.cond->accept(*this);
    currentExpr += "!= 0 ? ";
    p.then->accept(*this);
    currentExpr += " : ";
    p.otherwise->accept(*this);
    currentExpr += " )";
}

void AST_C_Transpiler::visitComparison(ASTComparison &p) {
    currentExpr += " (";
    p.lhs->accept(*this);
    switch (p.op) {
        case ASTComparison::EQ:
            currentExpr += "==";
            break;
        case ASTComparison::NEQ:
             currentExpr += "!=";
            break;
        case ASTComparison::GT:
             currentExpr += ">";
            break;
        case ASTComparison::LT:
             currentExpr += "<";
            break;
        case ASTComparison::LET:
             currentExpr += "<=";
            break;
        case ASTComparison::GET:
             currentExpr += ">=";
            break;
        default: throw MyException("Unknown op !");
    }
    p.rhs->accept(*this);
    currentExpr += ") ";
}

void AST_C_Transpiler::visitFunctionCall(ASTFunctionCall &p)
{
    currentExpr += " " + p.fname + "(";
    if (p.args.size() == 0)
        currentExpr += ")";
    else if (p.args.size() == 1)
    {
        p.args[0]->accept(*this);
        currentExpr += ")";
    }
}
