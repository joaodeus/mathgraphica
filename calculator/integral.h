#ifndef INTEGRAL_H
#define INTEGRAL_H

#include "parser.h"

class Integral
{
public:
    Integral(Parser *parser_);

    //Integral simple - Simpson  rule
    void setLimits(const double &lowerLimit_, const double &upperLimit_);
    void setLimits(const QString &lowerLimitExpression_, const QString &upperLimitExpression_);
    void setNumberOfIntervals(const uint &numberOfIntervals_);
    double solveIntegral(const QString &expression);

    //Integral double -Simpson rule
    void setInnerLimits(const double &innerLowerLimit, const double &innerUpperLimit);
    void setInnerLimits(const QString &innerLowerLimit, const QString &innerUpperLimit);
    void setOuterLimits(const double &outerLowerLimit, const double &outerUpperLimit);
    void setOuterLimits(const QString &outerLowerLimit, const QString &outerUpperLimit);
    void setVaribles(const QString &innerVarible_, const QString &outerVarible_);
    double solveIntegralDouble(const QString &expression);



private:
    // integral simple
    double lowerLimit;
    QString lowerLimitExpression;
    double upperLimit;
    QString upperLimitExpression;


    //integral double
    double innerLowerLimit;
    QString innerLowerLimitExpression;
    double innerUpperLimit;
    QString innerUpperLimitExpresion;
    double outerLowerLimit;
    QString outerLowerLimitExpression;
    double outerUpperLimit;
    QString outerUpperLimitExpression;
    QString innerVarible;
    QString outerVariable;

    //used for simple and double integrals
    Parser *parser;
    double numberOfIntervals;


public:
    // To refactor
    //simple integral, simpson composite rule
    double integral(Parser *p, QString &expression, QString &variable, double &a, double &b, double &m);

    //double integral, simpson composite rule
    double integral_double(Parser *p, QString &expression_xy, QString &varx, QString &vary,
                           double &Ax, double &Bx, QString &fAy ,QString &fBy,double &m);
};

#endif // INTEGRAL_H
