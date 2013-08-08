#ifndef MYNUMBER_H
#define MYNUMBER_H

#include <QVector>
#include <QMessageBox>
#include "complexo.h"
#include "matrix.h"

/*
 The parser transforms a string with a math expression in an list of elements.
 Ex: 2+3*cos(4), will create a list with the following elements:
 '2' ; '+' ; '3' ; '*' ; 'cos' ; '(' ; '4' ; ')'

class Number acts more less like a variant, it stores the elements.
Elements can be numbers or operator/functions
*/


class MyNumber
{
public:
    MyNumber();
    MyNumber(const double &x);
    MyNumber(const Complexo &z);
    MyNumber(const QList<double> &list_);
    MyNumber(const QList<Complexo> &list_);
    MyNumber(const Matrix &matrix);


    MyNumber &operator=(const MyNumber &a );
    friend MyNumber operator+(MyNumber a, MyNumber b);
    friend MyNumber operator-(MyNumber a, MyNumber b);
    friend MyNumber operator-(MyNumber a);
    friend MyNumber operator*(MyNumber &a, MyNumber &b);
    //friend MyNumber operator*(MyNumber a, Complexo b);
    friend MyNumber operator/(MyNumber &a, MyNumber &b);
    friend MyNumber operator^(MyNumber &a, MyNumber &b);


    void SetMyNumber(const double &real);
    void SetMyNumber(const Complexo &complex_);
    void SetMyNumber(const Matrix &matrix_);
    void SetMyNumber(const QList<Complexo> &list_);
    void SetMyNumber(const QList<double> &list_);


    Complexo numberComplexo();
    double numberReal();
    //QString numberString();
    Matrix numberMatrix();
    QList<Complexo> numberListComplexo();
    QList<double> numberListReal();
    QString Type();

    void setOperatorFunction(const QString &type_); //set this has a operator(+,-, ...) or function (sin, cos, ....)
    bool isNumber(); // check if it's a number
    bool isOperator();// check if it's +,-,*,/,^, ...
    bool isOperatorPlus();
    bool isOperatorMinus();
    bool isOperatorMultiplication();
    bool isOperatorDivision();
    bool isOperatorPower();
    bool isOperatorE();

    bool isFunction(); //check if it's sin, cos, log, .... )
    bool isFunction(QString &function_); //convenience method, set the function type (sin , cos, ...) in function_
    bool isFunction_or_Operator();// return true if it's a function or operator
    bool isParentheses(); //true if it's operator ( or )
    bool isLeft_Parentheses();
    bool isRight_Parentheses();
    bool isParentheses_abs();
  //  bool isConstant(); // check if it's a math constan: pi, e (euler) or i (imaginary number)
    bool isImaginary(); //check if it's imaginary number

    int operatorPriority(); //return operator priority
    // priority 0: '+' '-'
    // priority 1: '*' '/'
    // priority 2: '^' 'E' ; Note: 'E' is '*10^'  (  2E3  -> 2*10^3)


    //show the number, for debbuging purpose
    void showNumber();


private:
    //bNumber indicates if Number is storing a number (complex, array, matrix)
    //or a operator/function (+, -, *, /, sin, cos,....)
    //bool bNumber;
    QString type; //stores the type: number, operator or function
    //QString number_string;
    //double number;
    Complexo number_complexo;    
    QList<Complexo> number_list;
    Matrix number_matrix;

};


#endif // MYNUMBER_H
