#include <QCoreApplication>
#include <QtCore>

QString getFileContent(const QString& path);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString path = QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0] + "/sample.mt";
    qDebug() << getFileContent(path);

    return a.exec();
}

QString getFileContent(const QString &path)
{



    return "";
}
