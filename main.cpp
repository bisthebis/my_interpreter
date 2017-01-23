#include <QCoreApplication>
#include <QtCore>
#include <QtDebug>
#include "scanning.h"

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
    }
    catch (MyException& e)
    {
        qCritical() << e.msg;
        return -1;
    }


    //return a.exec();
    return 0;
}
