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
