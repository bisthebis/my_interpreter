#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <QVector>
#include <QVariant>
#include <QScopedPointer>
#include <QString>
#include "token.h"

//IMPORTANT : evaluation shall be done using a "Context" variable, aka environment. It is put here... for the time being.
struct Context {
        double getVariable(QString var) const;
    };

/** @brief Abstract class used to represent an expression that can be evaluated, a.k.a number literal,
 * variables and arithmetic combinations of them.
 */
struct Expression {
        virtual double evaluate(Context& c) const = 0;
    };

struct NumberExpression : public Expression {
        virtual double evaluate(Context &c) const Q_DECL_OVERRIDE {
            Q_UNUSED(c);
            return value;
        }
        const double value;
        NumberExpression(double v) : value(v){}
    };

struct VariableExpression : public Expression {
        virtual double evaluate(Context &c) const Q_DECL_OVERRIDE {
            return c.getVariable(name);
        }
        QString name;
        VariableExpression(QString n) : name(n) {}
    };

//QVector<Symbol> parse(const QVector<Token>& tokens);


#endif // SYMBOLS_H
