#include <QCoreApplication>
#include <QtCore>
#include <QtDebug>
#include "scanning.h"
#include "recursivedescentparser.h"
#include "astprinter.h"
#include "ast_c_transpiler.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString path = QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0] + "/sample.mt";
    try {
        auto content = getFileContent(path);
        auto tokens = scan(content);
        for(const auto& e : tokens)
        {
            qDebug() << e.toString();
        }
        auto parser = RecursiveDescent::RecursiveDescentParser(tokens);
        auto Program = parser.parse();
        auto visitor = RecursiveDescent::ASTPrinter();
        auto transpiler = AST_C_Transpiler(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0] + "/out.c");
        Program->accept(visitor);
        if (visitor.hadErrors)
            throw MyException("Didn't convert to C because error(s) were found.");
        Program->accept(transpiler);
        qDebug() << "Successfully parsed program";
    }
    catch (MyException& e)
    {
        qCritical() << e.msg;
        return -1;
    }


    //return a.exec();
    return 0;
}
