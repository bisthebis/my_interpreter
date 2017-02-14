#ifndef RECURSIVEDESCENTPARSER_H
#define RECURSIVEDESCENTPARSER_H

#include "myexception.h"
#include "token.h"
#include <QSharedPointer>
#include <QScopedPointer>
#include <QQueue>
#include "astvisitor.h"
#include "astnode.h"

namespace RecursiveDescent {

class RecursiveDescentParser
{
using Node = QSharedPointer<ASTNode>;

private:
    const QVector<Token>& tokens;
    QVector<Token>::const_iterator it;
    const QVector<Token>::const_iterator end;
    Token::TokenType peek() const {return it->type;}
    bool accept(Token::TokenType t); //Checks whether the current token is a t, and advance it if it's true
    void expect(Token::TokenType t, QString err); //Checks if current token is a t, and throw Exception if it's not

    Node parseInstruction();
    Node parseAssignment();
    Node parsePrint();
    Node parseAtom();
    Node parseTerm();
    Node parseExpression();
    Node processTerms(QQueue<RecursiveDescentParser::Node>& terms, QQueue<Token::TokenType>& ops);
    Node parseBool();
    Node parseFunctionCall(const QString& name);
public:
    RecursiveDescentParser(const QVector<Token>& t);
    Node parse(); // returns the program, as top-tier
};




} // end namespace



#endif // RECURSIVEDESCENTPARSER_H
