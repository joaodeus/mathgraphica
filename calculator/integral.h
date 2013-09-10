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
    void setNumberOfIntervals(const QString &numberOfIntervals_);
    void setIntegralExpression(const QString &integral_);

    QString getLowerLimit(){return lowerLimitExpression;}
    QString getUpperLimit(){return upperLimitExpression;}
    QString getNumberOfIntervals(){return numberOfIntervalsExpression;}
    QString getIntegralExpression(){return integralExpression;}
    QString getIntegral_Sintaxe();


    //check if "integralStr" is a valid integral expression of type "integral(lower,upper,expression,numberintervals)"
    //example: "integral(0,2,cos(x)+2,100)"
    // 0: lower limit;
    // 2: upper limit;
    // cos(x)+2: integral expression
    //100: number of intervals
    //If it's a valid expression, the limits, integral expression, and number of intervals are set
    bool isValidIntegral(QString integralStr);

    //Simpson composite rule
    Complexo solveIntegral(const QString &expression);
    Complexo solveIntegral();



/*
    //Integral double -Simpson rule
    void setInnerLimits(const double &innerLowerLimit, const double &innerUpperLimit);
    void setInnerLimits(const QString &innerLowerLimit, const QString &innerUpperLimit);
    void setOuterLimits(const double &outerLowerLimit, const double &outerUpperLimit);
    void setOuterLimits(const QString &outerLowerLimit, const QString &outerUpperLimit);
    void setVaribles(const QString &innerVarible_, const QString &outerVarible_);
    double solveIntegralDouble(const QString &expression);
*/


private:
    // integral simple
    double lowerLimit;
    QString lowerLimitExpression;
    double upperLimit;
    QString upperLimitExpression;
    double numberOfIntervals; // number of divisions of the interval between lower and upper limit of the simpson composite rule
    QString numberOfIntervalsExpression;
    QString integralExpression;

    //used for integrals
    Parser *parser;



//private:
    // To refactor
    //simple integral, simpson composite rule
    //double integral(Parser *p, QString &expression, QString &variable, double &a, double &b, double &m);

    //double integral, simpson composite rule
    //double integral_double(Parser *p, QString &expression_xy, QString &varx, QString &vary,
      //                     double &Ax, double &Bx, QString &fAy ,QString &fBy,double &m);
};

#endif // INTEGRAL_H
