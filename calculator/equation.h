#ifndef EQUATION_H
#define EQUATION_H

#include <QCoreApplication>
#include <QVector>
#include "parser.h"

class Equation
{
public:
    Equation(Parser *parser_);

    bool flagCalculationEquation;
    bool flagAbortFunction;

    QVector<Complexo> equation_solutions;

    Complexo equation_solver(Parser *p, QString &f1, QString &f2, QString &variable,
                             double &min, double &max, double &step, double &precision);

    void setLimits(const double &min_, const double &max_);
    void setLimits(const QString &minExpression_, const QString &maxExpression_);
    void setPrecision(const double &precision_);
    void setSearchStep(const double &searchStep_);
    void setSearchStep(const QString &searchStepExpression_);
    QVector<Complexo> solveEquation(const QString &expression);


private:
    double min;
    QString minExpression;
    double max;
    QString maxExpression;
    double searchStep;
    QString searchStepExpression;
    double precision;
    Parser *parser;

    double root_finder(Parser *p, QString f1, QString f2, QString variable, double a, double b, double precision);

};

#endif // EQUATION_H
