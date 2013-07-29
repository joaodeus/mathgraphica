#include "integral.h"

Integral::Integral(Parser *parser_)
{
    parser = parser_;
}


void Integral::setLimits(const double &lowerLimit_, const double &upperLimit_)
{
    lowerLimit = lowerLimit_;
    upperLimit = upperLimit_;

    lowerLimitExpression = QString("%1").arg(lowerLimit);
    upperLimitExpression = QString("%1").arg(upperLimit);
}

void Integral::setLimits(const QString &lowerLimitExpression_, const QString &upperLimitExpression_)
{
    lowerLimitExpression = lowerLimitExpression_;
    upperLimitExpression = upperLimitExpression_;

    lowerLimit = parser->SolveExpression(lowerLimitExpression).numberReal();
    if (parser->error())
    {
        QMessageBox::about(0,"Error!","Invalid lower limit");
    }

    upperLimit = parser->SolveExpression(upperLimitExpression).numberReal();
    if (parser->error())
    {
        QMessageBox::about(0,QObject::tr("Error!"),QObject::tr("Invalid upper limit"));
    }

}

void Integral::setNumberOfIntervals(const uint &numberOfIntervals_)
{
    numberOfIntervals = numberOfIntervals_;
    if (numberOfIntervals_ <= 0)
    {
        QMessageBox::about(0,QObject::tr("Error!"),QObject::tr("Invalid number of intervals."));
    }
}

double Integral::solveIntegral(const QString &expression)
{

    double h;
    double Isc;
    double i;
    QString i_str;
    bool par=true;
    double a = lowerLimit;
    double b = upperLimit;
    QStringList variables;

    if (parser->GetVariables(expression,variables) != 1)
    {
        QMessageBox::about(0,QObject::tr("Error!"),QObject::tr("Invalid integral expression."));
        return 0;
    }


    if (a > b)
    {
        i = a;
        a = b;
        b = i;
    }

    h=(b-a)/numberOfIntervals;

    //Isc=h/3*fx(f_x,a,x).r + h/3*fx(f_x,b,x).r;
    Isc=h/3 * parser->SolveExpression_fx(expression,a,variables[0]).numberReal()
            + h/3 * parser->SolveExpression_fx(expression,b,variables[0]).numberReal();

    for(i=a+h;i<b;i=i+h)
    {
        if (par==true)
        {
            //Isc=Isc+(h/3)*4*fx(f_x,i,x).r;
            Isc = Isc + (h/3) * 4 * parser->SolveExpression_fx(expression,i,variables[0]).numberReal();
            par=false;
        }
        else
        {
            //Isc=Isc+(h/3)*2*fx(f_x,i,x).r;
            Isc = Isc + (h/3) * 2 * parser->SolveExpression_fx(expression,i,variables[0]).numberReal();
            par=true;
        }
    }

    return Isc;
}


double Integral::integral(Parser *p, QString &expression, QString &variable, double &a, double &b, double &m)
{

    double h;
    double Isc;
    double i;
    bool par=true;

    if (a > b)
    {
        i=a;
        a=b;
        b=i;
    }

    h=(b-a)/m;

    //Isc=h/3*fx(f_x,a,x).r + h/3*fx(f_x,b,x).r;
    Isc=h/3 * p->SolveExpression_fx(expression,a,variable).numberReal()
            + h/3 * p->SolveExpression_fx(expression,b,variable).numberReal();

    for(i=a+h;i<b;i=i+h)
    {
        if (par==true)
        {
            //Isc=Isc+(h/3)*4*fx(f_x,i,x).r;
            Isc = Isc + (h/3) * 4 * p->SolveExpression_fx(expression,i,variable).numberReal();
            par=false;
        }
        else
        {
            //Isc=Isc+(h/3)*2*fx(f_x,i,x).r;
            Isc = Isc + (h/3) * 2 * p->SolveExpression_fx(expression,i,variable).numberReal();
            par=true;
        }
    }

    return Isc;
}

double Integral::integral_double(Parser *p, QString &expression_xy, QString &varx, QString &vary,
                       double &Ax, double &Bx, QString &fAy ,QString &fBy,double &m)
//double Integral::integral_double(Parser *p, QString &expression_xy, QString &varx, QString &vary,
  //                               double &Ax, double &Bx, &QString &fAy, QString &fBy, double &m)
{
    double hx;
    double hy;
    double ix,iy,i;
    double fay, fby;// fay, fby;
    bool parity;
    double Isc=0;


    if ( Ax > Bx)//swap
    { i=Ax;Ax=Bx;Bx=i; }
    hx=(Bx-Ax)/m;


    for(ix=Ax;ix<=Bx;ix+=hx)
    {
        parity=true;
        //fay=fx(fAy,ix,varx).r;
        //fby=fx(fBy,ix,varx).r;
        fay = p->SolveExpression_fx(fAy,ix,varx).numberReal();
        fby = p->SolveExpression_fx(fBy,ix,varx).numberReal();

        if (fay > fby) //swap
        { i=fay;fay=fby;fby=i; }
        hy=(fby-fay)/m;


        iy=fay;
        Isc += hy/3 * p->SolveExpression_fxy(expression_xy,fay,varx,iy,vary).numberReal()
                + hy/3 * p->SolveExpression_fxy(expression_xy,fby,varx,iy,vary).numberReal() ;
//        Isc+= hy/3*fxyz(func_xy,fay,varx,iy,vary,1,"@").r
  //              + hy/3*fxyz(func_xy,fby,varx,iy,vary,1,"@").r ;

        for(iy=fay+hy;iy<fby;iy+=hy)
        {
            if (parity == true)
            {
                Isc += hy * 4/3 * p->SolveExpression_fxy(expression_xy,ix,varx,iy,vary).numberReal();
                parity=false;
            }
            else
            {
                Isc += hy * 2/3 * p->SolveExpression_fxy(expression_xy,ix,varx,iy,vary).numberReal();
                parity=true;
            }
        }
    }


    return Isc*hx;
}

/*
double Calculadora::IntegralD(QString f_x, QString x, QString y,double a, double b
                                                          , double ay, double by, double m)
{
    double h=(b-a)/m;
    double hy=(by-ay)/m;
    bool par=true;
    //bool pary=true;
    double Isc=0;
    //double Iy=0;

    for(double yy=ay;yy<=by;yy+=hy)
    {
        Isc+=h/3*fxyz(f_x,a,x,yy,y,0,"@").r + h/3*fxyz(f_x,b,x,yy,y,0,"@").r;
        for(double xx=a+h;xx<b;xx+=h)
        {
            if (par==true)
            {
                Isc=Isc+(h/3)*4*fxyz(f_x,xx,x,yy,y,0,"@").r;
                par=false;
            }
            else
            {
                Isc=Isc+(h/3)*2*fxyz(f_x,xx,x,yy,y,0,"@").r;
                par=true;
            }
        }
    }

    return Isc*(by-ay)/m;
}
*/

/*
double Calculadora::IntegralArea(QString f_x, QString x, double a, double b, double h)
{

//	double h=(b-a)/m;
    bool par=true;

    double Isc;

    Isc=fabs(h/3*fx(f_x,a,x).r) + fabs(h/3*fx(f_x,b,x).r);


    for(double i=a+h;i<b;i=i+h)
    {
        if (par==true)
        {
                Isc=Isc+fabs((h/3)*4*fx(f_x,i,x).r);
                par=false;
        }
        else
        {
                Isc=Isc+fabs((h/3)*2*fx(f_x,i,x).r);
                par=true;
        }
    }

    return Isc;
}


*/