#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <QVector>
#include <QVariant>
#include <QScopedPointer>
#include <QString>
#include <QDebug>
#include <QMap>
#include "token.h"
#include "myexception.h"

//IMPORTANT : evaluation shall be done using a "Context" variable, aka environment. It is put here... for the time being.
struct Context {
        double getVariable(QString var) const;
        void setVariable(QString var, double val);
        QMap<QString, double> variables;
    };

/** @brief Abstract class used to represent an expression that can be evaluated, a.k.a number literal,
 * variables and arithmetic combinations of them.
 */
struct Expression {
        virtual double evaluate(Context& c) const = 0;
        virtual ~Expression(){}
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
struct AdditionExpression : public Expression {
        virtual double evaluate(Context &c) const Q_DECL_OVERRIDE {
            return lhs->evaluate(c) + rhs->evaluate(c);
        }
        QScopedPointer<Expression> lhs, rhs;
        AdditionExpression(Expression* l, Expression* r) : lhs(l), rhs(r) {}
    };
struct SubstractExpression : public Expression {
        virtual double evaluate(Context &c) const Q_DECL_OVERRIDE {
            return lhs->evaluate(c) - rhs->evaluate(c);
        }
        QScopedPointer<Expression> lhs, rhs;
        SubstractExpression(Expression* l, Expression* r) : lhs(l), rhs(r) {}
    };
struct MultiplicationExpression : public Expression {
        virtual double evaluate(Context &c) const Q_DECL_OVERRIDE {
            return lhs->evaluate(c) * rhs->evaluate(c);
        }
        QScopedPointer<Expression> lhs, rhs;
        MultiplicationExpression(Expression* l, Expression* r) : lhs(l), rhs(r) {}
    };
struct DivisionExpression : public Expression {
        virtual double evaluate(Context &c) const Q_DECL_OVERRIDE {
            double divisor = rhs->evaluate(c);
            if (divisor == 0)
                throw MyException("Divide by zero");
            return lhs->evaluate(c) / divisor;
        }
        QScopedPointer<Expression> lhs, rhs;
        DivisionExpression(Expression* l, Expression* r) : lhs(l), rhs(r) {}
    };

/** @brief Abstract class representing an executable instruction, i.e a print statement or a let statement.
 *
 */
struct Statement {
    virtual void run(Context& c) = 0;
    virtual ~Statement();
};
struct LetStatement : public Statement {
    virtual void run(Context &c) const {
        double value = expr->evaluate(c);
        c.setVariable(varName, value);
    }
    QString varName;
    QScopedPointer<Expression> expr;
    LetStatement(QString var, Expression* e) : varName(var), expr(e) {}
};
struct PrintStatement : public Statement {
    virtual void run(Context &c) const {
        qDebug() << "RUNNING PRINT STATEMETN : " << c.getVariable(varName);
    }
    QString varName;
    PrintStatement(QString var) : varName(var) {}
};

Expression* parseExpr(QVector<Token>::const_iterator it, QVector<Token>::const_iterator end);


#endif // SYMBOLS_H
