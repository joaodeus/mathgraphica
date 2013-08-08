#ifndef CALCULATOR_H
#define CALCULATOR_H

/*This is the main class for the calculator parser.
It will store the other classes: Number, Complexo, ...
responsible for parsing, calculations, ...
*/

#include "mynumber.h"
#include "parser.h"
#include "matrix.h"
#include "formatresult.h"


class Calculator
{
public:
    Calculator();

    MyNumber SolveExpression(const QString &expression);
    MyNumber SolveExpression_fx(const QString &expression);

    bool setVariable_Value(const QStringList &variables, const QList<MyNumber> &values);
    void setVariable_Value(const QString &variable, const MyNumber &value);
    void setVariable_Value(const QString &variable, const double &value);
    void setVariable_Value(const QString &variable, const QList<double> &value_list);
    void setVariable_Value(const QString &variable, const Matrix &value_matrix);

    QString formatResult( const Complexo &z);
    QString formatResult( const double &x);
    QString formatResult(MyNumber num);

    bool error();
    bool isValid_Expression_with_time_variable(const QString &expression);
    bool isValidExpression(const QString &expression);
    MyNumber isValidExpression(const QString &expression, bool &ok);

private:

    Parser parser;
    QStringList variables_List;
    QList<MyNumber> values_List;
    //QList< QPair<QString, MyNumber> > variables_values;



    FormatResult format;

};

#endif // CALCULATOR_H
