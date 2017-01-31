#include <QCoreApplication>
#include <QtCore>
#include <QtDebug>
#include "scanning.h"
#include "symbols.h"
#include "recursivedescentparser.h"
#include "astprinter.h"

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
        Program->accept(visitor);
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
