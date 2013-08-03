
#include "complexo.h"

Complexo::Complexo(double a,double b)
{
    r=a;
    i=b;
}

Complexo::Complexo(const double a)
{
    r=a;
    i=0;
}

Complexo::Complexo(const Complexo &z)
{
    r=z.r;
    i=z.i;
}

Complexo::Complexo()
{
    i=0;
    r=0;
}

Complexo::~Complexo()
{
    i=0;
    r=0;
}

void Complexo::clear()
{
    r = i = 0;
}

Complexo &Complexo::operator =(const Complexo &a)
{
    r=a.r;
    i=a.i;
    return *this;
}

Complexo &Complexo::operator =(const double &a)
{
    r=a;
    i=0;
    return *this;
}



// Operator overloaded using a friend function
Complexo operator+( Complexo a , Complexo b)
{
    Complexo z;
    z.r=a.r+b.r;
    z.i=a.i+b.i;
    return z;
}

Complexo operator+( double a , Complexo b )
{

    Complexo z;
    z.r=a+b.r;
    z.i=b.i;
    return z;
}

Complexo operator+( Complexo a , double b )
{
    Complexo z;
    z.r=a.r+b;
    z.i=a.i;
    return z;
}

/*
QList<Complexo> operator+(const QList<Complexo> &a, const QList<Complexo> &b)
{
    QList<Complexo> z;
    z.clear();


    return z;
}*/

Complexo operator-( Complexo a , Complexo b )
{
    Complexo z;
    z.r=a.r-b.r;
    z.i=a.i-b.i;
    return z;
}

Complexo operator-( double a , Complexo b )
{
    Complexo z;
    z.r=a-b.r;
    z.i=-b.i;
    return z;
}

Complexo operator-( Complexo a , double b )
{
    Complexo z;
    z.r=a.r-b;
    z.i=a.i;
    return z;
}

Complexo operator-( Complexo a )
{
    Complexo z;
    z.r=-a.r;
    z.i=-a.i;
    return z;
}


Complexo operator*( Complexo a , Complexo b )
{
    Complexo z;
    z.r=a.r*b.r-a.i*b.i;
    z.i=a.r*b.i+a.i*b.r;
    return z;
}


Complexo operator*( double a , Complexo b )
{
    Complexo z;
    z.r=a*b.r;
    z.i=a*b.i;
    return z;
}


Complexo operator*( Complexo a , double b )
{
    Complexo z;
    z.r=a.r*b;
    z.i=a.i*b;
    return z;
}

Complexo operator/( const Complexo a , const Complexo b )
{
    /*
    Complexo z;
    z.r=(a.r*b.r + a.i*b.i) / (b.r*b.r + b.i*b.i);
    z.i=(a.i*b.r - a.r*b.i)/ (b.r*b.r + b.i*b.i);
    return z;*/
    Complexo c;
    double r,den;

    if (fabs(b.r) >= fabs(b.i))
    {
            r=b.i/b.r;
            den=b.r+r*b.i;
            c.r=(a.r+r*a.i)/den;
            c.i=(a.i-r*a.r)/den;
    }
    else
    {
            r=b.r/b.i;
            den=b.i+r*b.r;
            c.r=(a.r*r+a.i)/den;
            c.i=(a.i*r-a.r)/den;
    }

    return c;
}

Complexo operator/( const double a , const Complexo b )
{

    Complexo c;
    Complexo aa(a,0);
    double r,den;

    if (fabs(b.r) >= fabs(b.i))
    {
            r=b.i/b.r;
            den=b.r+r*b.i;
            c.r=(aa.r+r*aa.i)/den;
            c.i=(aa.i-r*aa.r)/den;
    }
    else
    {
            r=b.r/b.i;
            den=b.i+r*b.r;
            c.r=(aa.r*r+aa.i)/den;
            c.i=(aa.i*r-aa.r)/den;
    }

    return c;
}


Complexo operator/( const Complexo a , const double b )
{
    Complexo c;
    c.r=a.r/b;
    c.i=a.i/b;
    return c;
}

Complexo operator^( const Complexo x , const Complexo y )
{
    if (x.r==0 && x.i==0)
            return x;
    if(x.i==0 && y.i==0)
        return Complexo(pow(x.r,y.r),0);
    return exp(y*ln(x));

    // x = a+jb
    // y = c+jd

    //  x ^y = ?^c * e^(-d ?)* [cos (c ? + d ln ?) + j sin (c ? + d ln ?)]
    //? =
    //?	 = v a� + b�
    //?	 = arctan b/a

   // double O=atan(x.i/x.r);
   // double P= sqrt( pow(x.r,2)+pow(x.i,2));
   // double aux=y.r*O + y.i*log(P);
   // return pow (P,y.r )* pow(2.7182818284590452354,-y.i*O) * Complexo( cos(aux),sin(aux)) ;
}


Complexo operator^( const double x , const Complexo y )
{
    Complexo z(x,0);
    if (x==0)
            return z;
    return exp(y*ln(z));
}

Complexo operator^(const Complexo x , const double y )
{
    if (x.r==0 && x.i==0)
            return x;
    return exp(y*ln(x));
}


bool operator == (Complexo x, Complexo y)
{
    if (x.r == y.r && x.i == y.i)
            return true;
    else
            return false;
}

bool operator != (Complexo x, Complexo y)
{
    return !(x == y);
}






QList<Complexo> cabs(QList<Complexo> &x)
{
    for(int i=0;i < x.size(); i++)
    {
        x[i].r=cabs(x.at(i));
        x[i].i=0;
    }
    return x;
}

double cabs(Complexo z)
{
    double x,y,temp;

    x=fabs(z.r);
    y=fabs(z.i);

    if (x==0)
            return y;
    if (y==0)
            return x;
    if (x<=y)
    {
            temp=y/x;
            return x*sqrt(1+temp*temp);
    }
    else
    {
            temp=x/y;
            return y*sqrt(1+temp*temp);

    }
    //return sqrt(z.r*z.r+z.i*z.i);
}

QList<double> abs(QList<Complexo> &x)
{
    QList<double> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(cabs(x.at(i)));
    }
    return y;
}












/*
QList<Complexo> cabs(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(cabs(x.at(i)));
    }
    return y;
}*/

double arg(Complexo x)
{
    return atan2(x.i,x.r);
}

/*
QList<double> arg(QList<Complexo> &x)
{
    QList<double> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(arg(x.at(i)));
    }
    return y;
}*/

QList<Complexo> arg(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(Complexo(arg(x.at(i)),0));
    }
    return y;
}

Complexo conj(Complexo x)
{
    Complexo z;
    z.r=x.r;
    z.i=-x.i;
    return z;
}

QList<Complexo> conj(QList<Complexo> &x)
{
    for(int i=0;i < x.size(); i++)
    {
        x[i].i=0-x[i].i;
    }
    return x;
}

double real(Complexo z)
{
    return z.r;
}




QList<Complexo> real(QList<Complexo> &x)
{
    for(int i=0;i < x.size(); i++)
    {
        x[i].i=0;
    }
    return x;
}


double imag(Complexo z)
{
    return z.i;
}

QList<Complexo> imag(QList<Complexo> &x)
{
    for(int i=0;i < x.size(); i++)
    {
        x[i].r=x[i].i;
        x[i].i=0;
    }
    return x;
}


Complexo cbrt(Complexo x)
{
    return x^0.333333333333333333333333333;
}

QList<Complexo> cbrt(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(cbrt(x.at(i)));
    }
    return y;
}

Complexo sqrt(Complexo x)
{
    Complexo z;
    double  cabs_aux;

  //  if (x.i == 0)
    //    return Complexo(sqrt(x.r),0);

    cabs_aux = cabs(x);

    z.r = sqrt( (cabs_aux+x.r)/2 );

    if (x.i >= 0)
        z.i = sqrt( (cabs_aux - x.r)/2 );
    else
        z.i = - sqrt( (cabs_aux - x.r)/2 );

    return z;

    //double P=cabs(x);
    //double O=arg(x);
   // x.r=sqrt(P)*cos(O/2);
   // x.i=sqrt(P)*sin(O/2);

    //return x;
}

QList<Complexo> sqrt(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(sqrt(x.at(i)));
    }
    return y;
}

Complexo exp(Complexo x)
{
    Complexo y;
    y.r=exp(x.r)*cos(x.i);
    y.i=exp(x.r)*sin(x.i);
    return y;

    /*Complexo z;
        z.r=exp(x.r)*cos(x.i);
        z.i=exp(x.r)*sin(x.i);
        return z;*/
}

QList<Complexo> exp(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(exp(x.at(i)));
    }
    return y;
}

Complexo ln(Complexo x)
{
    Complexo z;
    z.r=log(cabs(x));
    z.i=atan2(x.i,x.r);
    //log(z) = log(abs(z)) + i*atan2(y,x)
    return z;
}

QList<Complexo> ln(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(ln(x.at(i)));
    }
    return y;
}

Complexo log(Complexo x)
{

//    Complexo a(10,0);
    //return ln(x)/ln(a);
    return ln(x)/log(double(10));
    //  return l(x)/log(a);
}

QList<Complexo> log(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(log(x.at(i)));
    }
    return y;
}

double sinc(const double &x)
{
    return sin(M_PI*x)/(M_PI*x);
}

Complexo sinc(Complexo x)
{
    if ( (x.r == 0)  &&  (x.i == 0) )
        return 1;
    else
        return sin(M_PI*x)/(M_PI*x);
}

QList<Complexo> sinc(const QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(sinc(x.at(i)));
    }
    return y;
}


Complexo cos(const Complexo &x)
{
    Complexo j(0,1);
    //return ( e^j*x + e^-j*x )/2;
    return ((exp(j*x) + exp(-j*x))/2);
}

QList<double> cos(QList<double> &x)
{
    QList<double> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(cos(x.at(i)));
    }
    return y;
}

QList<Complexo> cos(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(cos(x.at(i)));
    }
    return y;
}

Complexo sin(Complexo x)
{
        Complexo j(0,1);
        return ((exp(j*x) - exp(-j*x))/(j*2));
}

QList<double> sin(QList<double> &x)
{
    QList<double> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(sin(x.at(i)));
    }
    return y;
}

QList<Complexo> sin(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(sin(x.at(i)));
    }
    return y;
}


Complexo tan(Complexo x)
{
        return sin(x)/cos(x);
}

QList<Complexo> tan(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(tan(x.at(i)));
    }
    return y;
}


Complexo cot(Complexo x)
{
        return cos(x)/sin(x);
}

QList<Complexo> cot(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(cot(x.at(i)));
    }
    return y;
}


Complexo csc(Complexo z)
{
    return 1/sin(z);
}

QList<Complexo> csc(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(csc(x.at(i)));
    }
    return y;
}

Complexo sec(Complexo z)
{
    return 1/cos(z);
}

QList<Complexo> sec(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(sec(x.at(i)));
    }
    return y;
}


Complexo cosh(Complexo x)
{
        return ((exp(x) + exp(-x))/2);
}

QList<Complexo> cosh(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(cosh(x.at(i)));
    }
    return y;
}

Complexo sinh(Complexo x)
{
        return ((exp(x) - exp(-x))/2);
}

QList<Complexo> sinh(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(sinh(x.at(i)));
    }
    return y;
}

Complexo tanh(Complexo x)
{

        return (	(exp(x)-exp(-x)) / (exp(x)+exp(-x) ) 	);
        //return senh(x)/cosh(x);
}

QList<Complexo> tanh(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(tanh(x.at(i)));
    }
    return y;
}


Complexo coth(Complexo x)
{
        return (	(exp(x)+exp(-x)) / (exp(x)-exp(-x) ) 	);
        //return cosh(x)/senh(x);
}

QList<Complexo> coth(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(coth(x.at(i)));
    }
    return y;
}

Complexo csch(Complexo z)
{
    return 1/sinh(z);
}

QList<Complexo> csch(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(csch(x.at(i)));
    }
    return y;
}

Complexo sech(Complexo z)
{
    return 1/cosh(z);
}

QList<Complexo> sech(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(sech(x.at(i)));
    }
    return y;
}


/*
The ACOS function returns the angle, expressed in radians, whose cosine is X (i.e., the arc-cosine).
For real input, the range of ACOS is between 0 and pi.
For input of a complex number, Z = X + iY, the complex arccosine is given by,

acos(Z) = acos(B) - i alog(A + sqrt(A^2 - 1)) if Y >= 0

acos(Z) = acos(B) + i alog(A + sqrt(A^2 - 1)) if Y < 0

where

A = 0.5 sqrt((X + 1)^2 + Y^2) + 0.5 sqrt((X - 1)^2 + Y^2)

B = 0.5 sqrt((X + 1)^2 + Y^2) - 0.5 sqrt((X - 1)^2 + Y^2)
*/


Complexo acos(Complexo z)
{
    Complexo j(0,1);

    double A = 0.5 * sqrt( pow(z.r+1,2) + z.i*z.i  ) + 0.5*sqrt( pow(z.r-1,2) + z.i*z.i );
    double B = 0.5*sqrt( pow(z.r+1,2) + z.i*z.i ) - 0.5*sqrt( pow(z.r-1,2) + z.i*z.i );


    if ( z.i >= 0)
        return acos(B) - j * log( A + sqrt(A*A - 1) ) ;
    else
        return acos(B) + j * log( A + sqrt(A*A - 1) ) ;



    //Complexo j(0,1);
    //return -j*ln(z+sqrt(z^2+1));
    // return -j*ln(z+j*sqrt(1-z^2));

}

QList<Complexo> acos(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(acos(x.at(i)));
    }
    return y;
}



/*
For real input, the range of ASIN is between -p/2 and p/2.

For input of a complex number, Z = X + iY, the complex arcsine is given by,

asin(Z) = asin(B) + i alog(A + sqrt(A^2 - 1)) if Y >= 0

asin(Z) = asin(B) - i alog(A + sqrt(A^2 - 1)) if Y < 0

where

A = 0.5 sqrt((X + 1)^2 + Y^2) + 0.5 sqrt((X - 1)^2 + Y^2)

B = 0.5 sqrt((X + 1)^2 + Y^2) - 0.5 sqrt((X - 1)^2 + Y^2)
*/

Complexo asin(Complexo z)
{
    Complexo j(0,1);
    double A = 0.5 * sqrt( pow(z.r+1,2) + z.i*z.i  ) + 0.5*sqrt( pow(z.r-1,2) + z.i*z.i );
    double B = 0.5*sqrt( pow(z.r+1,2) + z.i*z.i ) - 0.5*sqrt( pow(z.r-1,2) + z.i*z.i );

    if ( z.i >= 0 )
        return asin( B ) + j * log( A + sqrt(A*A - 1) );
    else
        return asin( B ) - j * log( A + sqrt(A*A - 1) );

    //Complexo j(0,-1),v(0,1);
    //return j*ln(v*z+sqrt(1-z^2));
//	Complexo j(0,1);
        //return -j*ln(j*z+sqrt(1-z^2));
//	return -j*ln(j*z+sqrt(1-z^2));
}

QList<Complexo> asin(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(asin(x.at(i)));
    }
    return y;
}

/*
Replace the formula
        arctan z = - i log ((1+iz) sqrt (1/(1+z^2)))
with the formula
        arctan z = (log (1+iz) - log (1-iz)) / (2i)
*/


Complexo atan(Complexo z)
{
    Complexo j(0,1);
    return ( ln(1+j*z) - ln(1-j*z) ) / (2*j);
   // return 0.5 * atan( (2*z.r) , (1-z.r*z.r - z.i*z.i)  ) + 0.25 * j * ln( (z.r*z.r + pow(z.i+1,2) ) / (z.r*z.r + pow(z.i-1,2) ) );

  //  Complexo j(0,1);
//    return -0.5*j*ln((1+j*x)/(1-j*x));
   //     return 0.5*ln((1+z)/(1-z));
}

QList<Complexo> atan(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(atan(x.at(i)));
    }
    return y;
}

Complexo atan(Complexo Zy, Complexo Zx)
{
    return atan(Zy / Zx);

}

QList<Complexo> atan(QList<Complexo> &Zy, QList<Complexo> &Zx)
{
    QList<Complexo> y;
    if (Zy.size() != Zx.size())
        return y;

    for(int i=0;i < Zy.size(); i++)
    {
        y.append(atan(Zy.at(i),Zx.at(i)));
    }
    return y;
}


Complexo acot(Complexo x)
{

    return atan(1/x);
  //  Complexo j(0,1);
//    return -0.5*j*ln((x+j)/(x-j));//?????????
    //return 0.5*ln((x+1)/(x-1));
}

QList<Complexo> acot(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(acot(x.at(i)));
    }
    return y;
}


Complexo acsc(Complexo z)
{
    return asin(1/z);
}

QList<Complexo> acsc(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(acsc(x.at(i)));
    }
    return y;
}

Complexo asec(Complexo z)
{
    return acos(1/z);
}

QList<Complexo> asec(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(asec(x.at(i)));
    }
    return y;
}

Complexo asinh(Complexo z)
{

    if (z.r >= 0)
        return ln ( sqrt(z*z + 1) + z  );
    else
        return -ln ( sqrt(z*z + 1) - z );

        //return ln(z+sqrt(z^2+1));
//        return ln(z+(z*z+1)^0.5);

        //ln( sqrt( x2 + 1 ) + x ) if x >= 0
    //-ln( sqrt( x2 + 1 ) - x ) if x < 0

}

QList<Complexo> asinh(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(asinh(x.at(i)));
    }
    return y;
}
Complexo acosh(Complexo z)
{
    return ln( z+  sqrt(z*z-1) );
    // return ln(z+sqrt(z^2-1));
}

QList<Complexo> acosh(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(acosh(x.at(i)));
    }
    return y;
}
Complexo atanh(Complexo z)
{
        return 0.5*ln((1+z)/(1-z));
}

QList<Complexo> atanh(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(atanh(x.at(i)));
    }
    return y;
}

Complexo acoth(Complexo z)
{
        return 0.5*ln((z+1)/(z-1));
}

QList<Complexo> acoth(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(acoth(x.at(i)));
    }
    return y;
}


Complexo acsch(Complexo z)
{
    return asinh(1/z);
}

QList<Complexo> acsch(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(acsch(x.at(i)));
    }
    return y;
}

Complexo asech(Complexo z)
{
    return acosh(1/z);
}

QList<Complexo> asech(QList<Complexo> &x)
{
    QList<Complexo> y;
    for(int i=0;i < x.size(); i++)
    {
        y.append(asech(x.at(i)));
    }
    return y;
}
