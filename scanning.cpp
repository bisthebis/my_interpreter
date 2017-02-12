#include "scanning.h"
#include <QFile>


QString getFileContent(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw MyException("Couldn't locate file : " + file.errorString() + ". Path is : " + path);

    const QByteArray data = file.readAll();

    return QString::fromUtf8(data.data());
}

QVector<Token> scan(const QString source)
{
    decltype(scan("")) result;

    auto it = source.begin();
    auto endOfFile = source.end();

    QString currentWord;

    int line = 1;

    while (it != endOfFile)
    {
        const auto c = *it;
        if (c == QChar::LineFeed)
        {
            ++line;
        }   else if (c.isLetter() || c == '_')
        {
            currentWord = parseWord(it);
            if (currentWord == "let")
            {
                result.append(Token(Token::LET, currentWord, currentWord, line));
            } else if (currentWord == "print")
            {
                result.append(Token(Token::PRINT, currentWord, currentWord, line));
            } else if (currentWord == "if")
            {
                result.append(Token(Token::IF, currentWord, currentWord, line));
            } else if (currentWord == "then")
            {
                result.append(Token(Token::THEN, currentWord, currentWord, line));
            } else if (currentWord == "else")
            {
                result.append(Token(Token::ELSE, currentWord, currentWord, line));
            } else if (currentWord == "endif")
            {
                result.append(Token(Token::ENDIF, currentWord, currentWord, line));
            } else {
                result.append(Token(Token::IDENTIFIER, currentWord, currentWord, line));
            }

        }   else if (c.isDigit())
        {
            currentWord = parseNumber(it);
            double number = currentWord.toDouble();
            result.append(Token(Token::NUMBER, currentWord, number, line));
        }   else if (c == ';')
        {
            result.append(Token(Token::END_OF_STATEMENT, ";", ";", line));
        }   else if (c == '=') {
            result.append(Token(Token::EQUAL, "=", "=", line));
        }   else if (c == '+') {
            result.append(Token(Token::PLUS, "+", "+", line));
        }   else if (c == '-') {
            result.append(Token(Token::MINUS, "-", "-", line));
        }   else if (c == '*') {
                result.append(Token(Token::TIMES, "*", "*", line));
        }   else if (c == '/') {
                if (*(it+1) == '/')
                    skipLineComment(it, endOfFile);
                else if (*(it+1) == '*')
                    skipMultiLinesComment(++it, endOfFile);
                else result.append(Token(Token::SLASH, "/", "/", line));
        }   else if (c == '^') {
            result.append(Token(Token::EXPONENT, "^", "^", line));
        }   else if (c == '(') {
                result.append(Token(Token::LEFT_PAREN, "(", "(", line));
        }   else if (c == ')') {
                result.append(Token(Token::RIGHT_PAREN, ")", ")", line));
        }

        ++it;
    }

    return result;
}

QString parseWord(QString::ConstIterator &it)
{
    QString lexeme;
    lexeme.reserve(16);
    while (it->isDigit() || it->isLetter() || *it == '_')
    {
        lexeme += *it;
        ++it;
    }
    --it; //The unused token must be read later
    return lexeme;
}
QString parseNumber(QString::ConstIterator &it) {
    QString lexeme;
    lexeme.reserve(16);
    while (it->isDigit() || *it == '.')
    {
        lexeme += *it;
        ++it;
    }
    --it;
    return lexeme;
}
void skipLineComment(QString::ConstIterator& it, QString::ConstIterator eof) {
    while (*(++it) != QChar::LineFeed && it != eof) ;
}
void skipMultiLinesComment(QString::ConstIterator &it, QString::ConstIterator eof) {
    while(it != eof)
    {
        ++it;
        const auto c = *it;
        if (c == '*') {
            ++it;
            if (*it == '/')
                return;
        }
    }
}
