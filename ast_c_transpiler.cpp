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
