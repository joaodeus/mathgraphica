#include "integraldouble.h"

IntegralDouble::IntegralDouble(Parser *parser_)
{
    parser                      = parser_;
    innerLowerLimitExpression   = "-x";
    innerUpperLimitExpression   = "2*x";
    outerLowerLimit             = -PI;
    outerLowerLimitExpression   = "-pi";

    outerUpperLimit             = PI;
    outerUpperLimitExpression   = "pi";

    innerVariable               = "y";
    outerVariable               = "x";
    integralDoubleExpression    = "cos(2+x*y)";
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

QString IntegralDouble::getIntegralDouble_Sintaxe()
{
    return QString("integralDouble(%1,%2,%3,%4,%5,%6,%7,%8)")
            .arg(this->integralDoubleExpression,
                 outerLowerLimitExpression, outerUpperLimitExpression,
                 innerLowerLimitExpression, innerUpperLimitExpression,
                 innerVariable, outerVariable,
                 this->numberOfIntervalsExpression);
}

bool IntegralDouble::isValidIntegralDoubleSintaxe(QString integralDoubleStr)
{

    if ( (integralDoubleStr.indexOf("integralDouble(") == 0) && integralDoubleStr.at(integralDoubleStr.size()-1) == ')' )
    {
        integralDoubleStr.remove("integralDouble(");
        integralDoubleStr.remove(integralDoubleStr.size()-1,1);
    }
    else
    {
        return false;
    }

    QStringList list = integralDoubleStr.split(",");

    if (list.size() != 8)
        return false;

    if (!parser->isValidExpression_fn(list[0])) //integrationDouble expression
        return false;


    if (!parser->isValidExpression(list[1])) //outer lower limit
        return false;

    if (!parser->isValidExpression(list[2])) //outer upper limit
        return false;

    if ( ! ( (parser->isValidExpression(list[3]) == true) ||  (parser->isValidExpression_fx(list[3]) == true) ) ) //inner lower limit
        return false;

    if ( ! ( (parser->isValidExpression(list[4]) == true) ||  (parser->isValidExpression_fx(list[4]) == true) ) )  //inner upper limit
        return false;

    if (!parser->isValidExpression(list[7])) //number of intervals
        return false;

    return true;
}

bool IntegralDouble::setIntegralDoubleFromSintaxe(QString integralDoubleSintaxe)
{     
    if (isValidIntegralDoubleSintaxe(integralDoubleSintaxe) == false)
        return false;

    integralDoubleSintaxe.remove("integralDouble(");
    integralDoubleSintaxe.remove(integralDoubleSintaxe.size()-1,1);

    QStringList list = integralDoubleSintaxe.split(",");

    setIntegralDoubleExpression(list[0]);
    setOuterLimits(list[1],list[2]);
    setInnerLimits(list[3],list[4]);
    setVaribles(list[5],list[6]);
    setNumberOfIntervals(list[7]);

    return true;
}

