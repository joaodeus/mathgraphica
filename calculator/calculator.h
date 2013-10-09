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
#include "equation.h"
#include "integral.h"
#include "integraldouble.h"
#include "myfunction.h"
#include "formulas.h"

class Calculator
{
public:
    Calculator();
    ~Calculator();

    MyNumber SolveExpression(const QString &expression);
    MyNumber SolveExpression_fx(const QString &expression);
    QList<double> SolveExpression_list(const QString &expression,const int &size);


    //void clear_Variables_Values();
    bool setVariable_Value(const QStringList &variables, const QList<MyNumber> &values);
    void setVariable_Value(const QString &variable, const MyNumber &value);
    void setVariable_Value(const QString &variable, const double &value);
    void setVariable_Value(const QString &variable, const QList<double> &value_list);
    void setVariable_Value(const QString &variable, const Matrix &value_matrix);

    int GetVariables(const QString &expression, QStringList &list_variables);


    QString formatResult( const Complexo &z);
    QString formatResult( const double &x);
    QString formatResult(MyNumber num);

    bool error();
    void setDegreeRadGrad(const int isDegreeRadGrad_);
    int getDegreeRadGrad();

    //check if expression is a valid math expression f(t) with one 't' time variable, like i.e: "2+t"
    bool isValidExpression_ft(const QString &expression);

    //check if expression is a valid math expression f(variable,t) i.e. with 2 variables,
    //one of them being 't', the time varible, like e.e: "cos(x+t)", "2*y+t"
    bool isValidExpression_fxt(const QString &expression);
    //convenience method, saves the variable other than 't', in "variable"
    bool isValidExpression_fxt(const QString &expression, QString &variable);


    //can have many variables, one of them being a time variable
    bool isValid_Expression_with_time_variable(const QString &expression);
    bool isValidExpression(const QString &expression);
    MyNumber isValidExpression(const QString &expression, bool &ok);

    bool isValidEquation(const QString &equation);
    //QList<Complexo> SolveEquation(const QString &equation_);
    //QList<Complexo> SolveEquation(const QString &f1, const QString &f2);


    Equation m_equation;
    Integral m_integral;
    IntegralDouble m_integralDouble;
    QList<Formulas> m_formulasList;

    void addFormula();
    void removeFormula();

private:

    Parser parser;    
    QStringList variables_List;
    QList<MyNumber> values_List;


    //---functions-------------------------------
    QList<myFunction> m_FunctionsList;

    //If there's a expression with user defined functions like: 2+f(5)+cos(3)
    //where f() is a user defined function like, for example, f(x)=4*x+2
    //it will return "2+(4*5+2)+cos(3)".
    //This function is called inside ParseExpressionToList(....), so we don't have to worry
    //about it anymore
    QString Expression_Replace_User_Defined_Function(const QString &expression_, const QList<myFunction> &list_functions_);


    //---format calculations results-------------
    FormatResult format;

};

#endif // CALCULATOR_H
