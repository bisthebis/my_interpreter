#include "symbols.h"

double Context::getVariable(QString var) const
{
    if (variables.contains(var))
        return variables[var];

    throw MyException("Unassigned variable !");
}

void Context::setVariable(QString var, double val)
{
    variables[var] = val;
}

Expression* parseExpr(QVector<Token>::const_iterator it, QVector<Token>::const_iterator end)
{
    Q_UNUSED(end);
    Token::TokenType type = it->type;
    if (type != Token::IDENTIFIER && type != Token::NUMBER)
        throw MyException("Expression can't start by and operator");

    Expression* lhs;
    if (type == Token::NUMBER)
        lhs = new NumberExpression(it->value.toDouble());
    else
        lhs = new VariableExpression(it->value.toString());

    //If it is a 1-member expr, return it. Otherwise, it's a "VAR OP VAR" expression
    ++it;
    if (it->type == Token::END_OF_STATEMENT)
        return lhs;
    else {
        Expression* rhs;
        if ((it+1)->type == Token::NUMBER)
            rhs = new NumberExpression((it+1)->value.toDouble());
        else
            rhs = new VariableExpression((it+1)->value.toString());


        Expression* operation;
        auto opertor = it->type;
        switch (opertor) {
        case Token::PLUS:
            operation = new AdditionExpression(lhs, rhs);
            break;
        case Token::MINUS:
            operation = new SubstractExpression(lhs, rhs);
            break;
        case Token::TIMES:
            operation = new MultiplicationExpression(lhs, rhs);
            break;
        case Token::SLASH:
            operation = new DivisionExpression(lhs, rhs);
            break;
        default:
            throw MyException(QString("Wrong operator type : %1").arg(opertor));
            break;
        }
        return operation;
    }
}

QVector<Statement*> parseTokens(const QVector<Token> &src)
{
    QVector<Statement*> result;
    auto it = src.cbegin();
    const auto end = src.cend();
    for (; it != end; ++it)
    {
        if (it->type != Token::PRINT && it->type != Token::LET)
            continue;

        if (it->type == Token::PRINT)
        {
            auto varName = (it+1)->value.toString();
            result.append(new PrintStatement(varName));
        }
        else if (it->type == Token::LET)
        {
            auto varName = (it+1)->value.toString();
            if ((it+2)->type != Token::EQUAL)
                throw MyException("Let statemetn without '=' following");
            Expression* expr = parseExpr(it+3, end);
            result.append(new LetStatement(varName, expr));
        }
    }

    return result;
}
