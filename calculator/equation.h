#ifndef EQUATION_H
#define EQUATION_H

#include <QCoreApplication>

#include "parser.h"

class Equation
{
public:
    Equation(Parser *parser_);

    bool flagCalculationEquation;
    bool flagAbortFunction;

    QList<Complexo> equation_solutions;

    void setLimits(const double &min_, const double &max_);
    void setLimits(const QString &minExpression_, const QString &maxExpression_);
    void setPrecision(const double &precision_);
    void setPrecision(const QString &precisionExpression_);
    void setDelta(const double &delta_);
    void setDelta(const QString &deltaExpression_);
    void setEquation(const QString &equation_);
    QList<Complexo> solveEquation(const QString &f1, const QString &f2);
    QList<Complexo> solveEquation(const QString &equation);

    QString getLimitsMin(){return minExpression;}
    QString getLimitsMax(){return maxExpression;}
    QString getDelta(){return deltaExpression;}
    QString getPrecision(){return precisionExpression;}
    QString getEquation(){return m_equation;}
    QString getEquation_member1(){return m_f1;}
    QString getEquation_member2(){return m_f2;}

    void teste();
    bool error;
    QString errorMessage;

private:
    double min;
    QString minExpression;
    double max;
    QString maxExpression;
    double delta;
    QString deltaExpression;
    double precision;
    QString precisionExpression;
    Parser *parser;
    QString m_f1;
    QString m_f2;
    QString m_equation;

    double root_finder(Parser *p, QString f1, QString f2, QString variable, double a, double b, double precision);

};

#endif // EQUATION_H
