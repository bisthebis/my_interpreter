#include <QCoreApplication>
#include <QtCore>
#include <QtDebug>
#include "myexception.h"

QString getFileContent(const QString& path);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString path = QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0] + "/sample.mt";
    try {
        auto content = getFileContent(path);
        qDebug() << "Content is : " << content;
        for (QChar c : content)
            qDebug() << (c.isSpace() ? ' ' : c);
    }
    catch (MyException& e)
    {
        qCritical() << e.msg;
        return -1;
    }


    //return a.exec();
    return 0;
}

QString getFileContent(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw MyException("Couldn't locate file : " + file.errorString());

    const QByteArray data = file.readAll();

    return QString::fromUtf8(data.data());
}
