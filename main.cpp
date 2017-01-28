#include <QCoreApplication>
#include <QtCore>
#include <QtDebug>
#include "scanning.h"
#include "symbols.h"

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
        auto context = Context();
        auto statements = parseTokens(tokens);
        for (auto s : statements)
        {
            s->run(context);
        }
    }
    catch (MyException& e)
    {
        qCritical() << e.msg;
        return -1;
    }


    //return a.exec();
    return 0;
}
