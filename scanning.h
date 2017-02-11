#ifndef SCANNING_H
#define SCANNING_H

#include <QVector>
#include <QString>
#include <QChar>
#include "myexception.h"
#include "token.h"


QString getFileContent(const QString& path);
QVector<Token> scan(const QString source);
QString parseWord(QString::ConstIterator &it);
QString parseNumber(QString::ConstIterator &it);
void parseComment(QString::ConstIterator& it);



#endif // SCANNING_H
