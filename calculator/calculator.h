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

    void setPreDefinedFormulas();


    MyNumber SolveExpression(const QString &expression);
    MyNumber SolveExpression_fx(const QString &expression);
    QList<double> SolveExpression_list(const QString &expression,const int &size);

    //solves math expressions with n variables, i.e:
    //expression_fn = "5+x+y+z+var1" ; variables_List = {x; y; z; var1} ; values_List = {2.3; 1; 5; 6.1}
    MyNumber SolveExpression_fn(const QString &expression_fn, QList<MyNumber> &values_List_, QStringList &variables_List_);



    //void clear_Variables_Values();
    bool setVariable_Value(const QStringList &variables, const QList<MyNumber> &values);
    void setVariable_Value(const QString &variable, const MyNumber &value);
    void setVariable_Value(const QString &variable, const double &value);
    void setVariable_Value(const QString &variable, const QList<double> &value_list);
    void setVariable_Value(const QString &variable, const Matrix &value_matrix);

    int GrabVariables(const QString &expression, QStringList &list_variables);


    //---format calculations results-------------
    FormatResult format;
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

    //check if expression is a valid math expression with n variables (n > 0), like i.e: "5+x+y*z"
    bool isValidExpression_fn(const QString &expression);

    bool isValidExpression(const QString &expression);
    MyNumber isValidExpression(const QString &expression, bool &ok);

    bool isValidEquation(const QString &equation);
    //QList<Complexo> SolveEquation(const QString &equation_);
    //QList<Complexo> SolveEquation(const QString &f1, const QString &f2);

  /*  //check
    bool isValidEquation_Explicit_From_Constant(const QString &equation);
    //convenience method, saves variable in variable_ and value in value_
    bool isValidEquation_Explicit_From_Constant(const QString &expression, QString &variable_, MyNumber &value_);
*/

    //check if expression is a valid equation, explicit from a constant expression
    //the first member must be only the variable, and second member must be only a expression without variables
    // like i.e.: "x=4-5" or "var1=2+cos(pi)"
    bool isValidEquation_Explicit_From_Constant(const QString &equation);
    //convenience method, saves variable in variable_ and value in value_
    bool isValidEquation_Explicit_From_Constant(const QString &equation, QString &variable_, MyNumber &value_);

    //check if expression is a valid equation, explicit from other variables
    //like i.e.:  "x=2y+z"
    bool isValidEquation_Explicit_From_Variables(const QString &equation);
    //convenience method, saves first member variable in "variable_first_member"
    //and the variables of second member in "variables_second_member"
    bool isValidEquation_Explicit_From_Variables(const QString &equation,
                                                 QString &first_member, QString &second_member);



    Equation m_equation;
    Integral m_integral;
    IntegralDouble m_integralDouble;
    QList<Formulas> m_formulasList;

    void addFormula();
    void removeFormula(int index);

private:

    Parser parser;    

public:
    // saves the variables and values defined by the user in the command line
    // example: in "x=5"  "x" is saved in variables list, "5" is saved in values_list
    QStringList variables_List;
    QList<MyNumber> values_List;


public:
    void addVariableValue(QString variable_, MyNumber value_);
    void addVariableValue(QString variable_, QString value_);


public:
    //---functions-------------------------------
    myFunction m_function;
    QList<myFunction> m_FunctionsList;
    void addFunction(const myFunction &function_);

    //If there's a expression with user defined functions like: 2+f(5)+cos(3)
    //where f() is a user defined function like, for example, f(x)=4*x+2
    //it will return "2+(4*5+2)+cos(3)".
    //This function is called inside ParseExpressionToList(....), so we don't have to worry
    //about it anymore
    QString Expression_Replace_User_Defined_Function(QString &expression_);

};

#endif // CALCULATOR_H
