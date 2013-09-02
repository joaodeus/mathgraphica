#ifndef INTEGRALDOUBLE_H
#define INTEGRALDOUBLE_H

#include "parser.h"

class IntegralDouble
{
public:
    IntegralDouble(Parser *parser_);


    //Integral double -Simpson rule
    //void setInnerLimits(const double &innerLowerLimit_, const double &innerUpperLimit_);
    void setInnerLimits(const QString &innerLowerLimitExpression_, const QString &innerUpperLimitExpression_);
    void setOuterLimits(const double &outerLowerLimit_, const double &outerUpperLimit_);
    void setOuterLimits(const QString &outerLowerLimitExpression_, const QString &outerUpperLimitExpression_);
    void setNumberOfIntervals(const uint &numberOfIntervals_);
    void setNumberOfIntervals(const QString &numberOfIntervals_);
    void setVaribles(const QString &innerVariable_, const QString &outerVariable_);
    void setIntegralDoubleExpression(const QString &integralDoubleExpression_);
    Complexo solveIntegralDouble(const QString &integralDoubleExpression_);
    Complexo solveIntegralDouble();

private:

    //integral double
    //double innerLowerLimit;
    QString innerLowerLimitExpression;
    //double innerUpperLimit;
    QString innerUpperLimitExpression;
    double outerLowerLimit;
    QString outerLowerLimitExpression;
    double outerUpperLimit;
    QString outerUpperLimitExpression;
    double numberOfIntervals; // number of divisions of the interval between lower and upper limit of the simpson composite rule
    QString numberOfIntervalsExpression;
    QString innerVariable;
    QString outerVariable;
    QString integralDoubleExpression;

    //used for simple and double integrals
    Parser *parser;



};

#endif // INTEGRALDOUBLE_H
