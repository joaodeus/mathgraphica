#include "calculator.h"

Calculator::Calculator()
{
}

MyNumber Calculator::SolveExpression(const QString &expression)
{
    return parser.SolveExpression(expression);
}

MyNumber Calculator::SolveExpression_fx(const QString &expression)
{
    return parser.SolveExpression_fn(expression, values_List, variables_List);
}



bool Calculator::setVariable_Value(const QStringList &variables, const QList<MyNumber> &values)
{
    if (variables.size() != values.size())
        return false; //error

    for(int i=0;i<variables.size();i++)
    {
        setVariable_Value(variables.at(i), values.at(i));
    }
    return true;
}




void Calculator::setVariable_Value(const QString &variable, const MyNumber &value)
{
    int index = variables_List.indexOf(variable);
    if (index == -1)
    {
        variables_List.append(variable);
        values_List.append(value);
    }
    else
    {
        values_List[index] = value;
    }
}

void Calculator::setVariable_Value(const QString &variable, const double &value)
{
    setVariable_Value(variable, MyNumber(value));
}

void Calculator::setVariable_Value(const QString &variable, const QList<double> &value_list)
{
    setVariable_Value(variable, MyNumber(value_list));
}


void Calculator::setVariable_Value(const QString &variable, const Matrix &value_matrix)
{
    setVariable_Value(variable, MyNumber(value_matrix));
}

QString Calculator::formatResult( const Complexo &z)
{
    return format.formatResult(z);
}

QString Calculator::formatResult( const double &x)
{
    return format.formatResult(x);
}

QString Calculator::formatResult(MyNumber num)
{
    return format.formatResult(num);
}


bool Calculator::error()
{
    return parser.error();
}

bool Calculator::isValid_Expression_with_time_variable(const QString &expression)
{
    return parser.isValidExpression_ft(expression);
}

bool Calculator::isValidExpression(const QString &expression)
{
    parser.SolveExpression(expression);
    return !parser.error();
}

MyNumber Calculator::isValidExpression(const QString &expression, bool &ok)
{
    MyNumber number = parser.SolveExpression(expression);
    ok = !parser.error();
    return number;
}























