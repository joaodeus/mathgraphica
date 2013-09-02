#include "integraldouble.h"

IntegralDouble::IntegralDouble(Parser *parser_)
{
    parser                      = parser_;
   // innerLowerLimit             = "x";
    innerLowerLimitExpression   = "x";
    //innerUpperLimit             = ;
    innerUpperLimitExpression   = "x^2+3x";
    outerLowerLimit             = 1;
    outerLowerLimitExpression   = "1";
    outerUpperLimit             = 4;
    outerUpperLimitExpression   = "4";
    innerVariable               = "y";
    outerVariable               = "x";
    integralDoubleExpression    = "1+x-y";
    numberOfIntervals           = 100;
    numberOfIntervalsExpression = "100";
}


/*
void IntegralDouble::setInnerLimits(const double &innerLowerLimit_, const double &innerUpperLimit_)
{
    innerLowerLimit = innerLowerLimit_;
    innerUpperLimit = innerUpperLimit_;
    innerLowerLimitExpression = QString("%1").arg(innerLowerLimit);
    innerUpperLimitExpression = QString("%1").arg(innerUpperLimit);
}*/

void IntegralDouble::setInnerLimits(const QString &innerLowerLimitExpression_, const QString &innerUpperLimitExpression_)
{
    innerLowerLimitExpression = innerLowerLimitExpression_;
    innerUpperLimitExpression = innerUpperLimitExpression_;

   /* innerLowerLimit = parser->SolveExpression(innerLowerLimitExpression).numberReal();
    if (parser->error())
    {
        QMessageBox::about(0,"Error!","Invalid inner lower limit");
    }

    innerUpperLimit = parser->SolveExpression(innerUpperLimitExpression).numberReal();
    if (parser->error())
    {
        QMessageBox::about(0,"Error!","Invalid inner upper limit");
    }*/
}

void IntegralDouble::setOuterLimits(const double &outerLowerLimit_, const double &outerUpperLimit_)
{
    outerLowerLimit = outerLowerLimit_;
    outerUpperLimit = outerUpperLimit_;
    outerLowerLimitExpression = QString("%1").arg(outerLowerLimit);
    outerUpperLimitExpression = QString("%1").arg(outerUpperLimit);
}

void IntegralDouble::setOuterLimits(const QString &outerLowerLimitExpression_, const QString &outerUpperLimitExpression_)
{
    outerLowerLimitExpression = outerLowerLimitExpression_;
    outerUpperLimitExpression = outerUpperLimitExpression_;

    outerLowerLimit = parser->SolveExpression(outerLowerLimitExpression).numberReal();
    if (parser->error())
    {
        QMessageBox::about(0,"Error!","Invalid outer lower limit");
    }

    outerUpperLimit = parser->SolveExpression(outerUpperLimitExpression).numberReal();
    if (parser->error())
    {
        QMessageBox::about(0,"Error!","Invalid outer upper limit");
    }

}


void IntegralDouble::setNumberOfIntervals(const uint &numberOfIntervals_)
{
    if (numberOfIntervals_ <= 0)
    {
        QMessageBox::about(0,QObject::tr("Error!"),QObject::tr("Invalid number of intervals."));
    }
    numberOfIntervals = numberOfIntervals_;
    numberOfIntervalsExpression = QString("%1").arg(numberOfIntervals);

}

void IntegralDouble::setNumberOfIntervals(const QString &numberOfIntervals_)
{
    numberOfIntervalsExpression = numberOfIntervals_;
    numberOfIntervals = parser->SolveExpression(numberOfIntervalsExpression).numberReal();
    if (parser->error())
    {
        QMessageBox::about(0,"Error!","Invalid number of intervals");
    }

    if (numberOfIntervals_ <= 0)
    {
        QMessageBox::about(0,QObject::tr("Error!"),QObject::tr("Number of intervals must be greater than zero."));
    }
}


void IntegralDouble::setVaribles(const QString &innerVariable_, const QString &outerVariable_)
{
    innerVariable = innerVariable_;
    outerVariable = outerVariable_;
}

void IntegralDouble::setIntegralDoubleExpression(const QString &integralDoubleExpression_)
{
    integralDoubleExpression = integralDoubleExpression_;
}

Complexo IntegralDouble::solveIntegralDouble(const QString &integralDoubleExpression_)
{
    setIntegralDoubleExpression(integralDoubleExpression_);
    return solveIntegralDouble();
}


Complexo IntegralDouble::solveIntegralDouble()
{

    double hx;
    double hy;
    double ix,iy,i;
    double fay, fby;// fay, fby;
    bool parity;
    double Isc=0;

    double Ax = outerLowerLimit;
    double Bx = outerUpperLimit;

    QString fAy = innerLowerLimitExpression;
    QString fBy = innerUpperLimitExpression;
    QString varx = outerVariable;
    QString vary = innerVariable;

    if ( Ax > Bx)//swap
    { i=Ax;Ax=Bx;Bx=i; }
    hx=(Bx-Ax)/numberOfIntervals;


    for(ix=Ax;ix<=Bx;ix+=hx)
    {
        parity=true;
        //fay=fx(fAy,ix,varx).r;
        //fby=fx(fBy,ix,varx).r;
        fay = parser->SolveExpression_fx(fAy,ix,varx).numberReal();
        fby = parser->SolveExpression_fx(fBy,ix,varx).numberReal();

        if (fay > fby) //swap
        { i=fay;fay=fby;fby=i; }
        hy=(fby-fay)/numberOfIntervals;


        iy=fay;
        Isc += hy/3 * parser->SolveExpression_fxy(integralDoubleExpression,fay,varx,iy,vary).numberReal()
                + hy/3 * parser->SolveExpression_fxy(integralDoubleExpression,fby,varx,iy,vary).numberReal() ;

        for(iy=fay+hy;iy<fby;iy+=hy)
        {
            if (parity == true)
            {
                Isc += hy * 4/3 * parser->SolveExpression_fxy(integralDoubleExpression,ix,varx,iy,vary).numberReal();
                parity=false;
            }
            else
            {
                Isc += hy * 2/3 * parser->SolveExpression_fxy(integralDoubleExpression,ix,varx,iy,vary).numberReal();
                parity=true;
            }
        }
    }

    return Isc*hx;
}
