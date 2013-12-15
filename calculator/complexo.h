#ifndef COMPLEXO_H
#define COMPLEXO_H

#include <math.h>
#include <QList>
#include <QDataStream>

//#define PI      3.1415926535897932384
/* Constants rounded for 21 decimals.
#define M_E 2.71828182845904523536
#define M_LOG2E 1.44269504088896340736
#define M_LOG10E 0.434294481903251827651
#define M_LN2 0.693147180559945309417
#define M_LN10 2.30258509299404568402
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define M_PI_4 0.785398163397448309616
#define M_1_PI 0.318309886183790671538
#define M_2_PI 0.636619772367581343076
#define M_1_SQRTPI 0.564189583547756286948
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2 1.41421356237309504880
#define M_SQRT_2 0.707106781186547524401*/

#define PI      3.1415926535897932384626433832795
#define e_Neper 2.71828182845904523536


class Complexo
{

public:
    Complexo();
    Complexo(double r_, double i_);
    Complexo(const Complexo &z);
    Complexo(const double r_);
    virtual ~Complexo();

    double r;
    double i;

    void clear();

    friend Complexo operator+( Complexo a, Complexo b );
   // friend QList<Complexo> operator+(const QList<Complexo> &a, const QList<Complexo> &b);
    friend Complexo operator+( double a, Complexo b );
    friend Complexo operator+( Complexo a, double b );
    friend Complexo operator-( Complexo a, Complexo b );
    friend Complexo operator-( double a, Complexo b );
    friend Complexo operator-( Complexo a, double b );
    friend Complexo operator-( Complexo a);
    friend Complexo operator*( Complexo a, Complexo b );
    friend Complexo operator*( double a, Complexo b );
    friend Complexo operator*( Complexo a, double b );
    friend Complexo operator/( const Complexo a, const Complexo b );
    friend Complexo operator/( const Complexo a, const double b );
    friend Complexo operator/( const double a, const Complexo b );
    friend Complexo operator^( const Complexo x, const Complexo y);
    friend Complexo operator^( const double x, const Complexo y);
    friend Complexo operator^( const Complexo x, const double y);

    friend bool operator ==( Complexo x, Complexo y);
    friend bool operator !=( Complexo x, Complexo y);

    Complexo &operator=(const Complexo & );  // Right side is the argument.
    Complexo &operator=(const double & );  // Right side is the argument.

};


/*
 double j0(double x);
     float j0f(float x);
     double j1(double x);
     float j1f(float x);
     double jn(int n, double x);
     float jnf(int n, float x);
     double y0(double x);
     float y0f(float x);
     double y1(double x);
     float y1f(float x);
     double yn(int n, double x);
     float ynf(int n, float x);
*/


double cabs(Complexo x);
QList<double> abs(QList<Complexo> &x);
QList<Complexo> cabs(QList<Complexo> &x);


double arg(Complexo );
//QList<double> arg(QList<Complexo> &x);
QList<Complexo> arg(QList<Complexo> &x);


Complexo conj(Complexo x);
QList<Complexo> conj(QList<Complexo> &x);

double real(Complexo);
QList<Complexo> real(QList<Complexo> &x);

double imag(Complexo);
QList<Complexo> imag(QList<Complexo> &x);

//double abs(Complexo);
//QList<Complexo> abs(QList<Complexo> &x);

Complexo sqrt(Complexo);
QList<Complexo> sqrt(QList<Complexo> &x);

Complexo cbrt(Complexo);
QList<Complexo> cbrt(QList<Complexo> &x);

Complexo exp(Complexo);
QList<Complexo> exp(QList<Complexo> &x);

double sinc(const double &x);
Complexo sinc(Complexo);
QList<Complexo> sinc(const QList<Complexo> &x);

//polar form for complex numbers
Complexo cis(const Complexo &o);
QList<Complexo> cis(QList<Complexo> &o);


Complexo cos(const Complexo &x);
QList<double> cos(QList<double> &x);
QList<Complexo> cos(QList<Complexo> &x);

Complexo sin(Complexo);
QList<double> sin(QList<double> &x);
QList<Complexo> sin(QList<Complexo> &x);

Complexo tan(Complexo);
QList<Complexo> tan(QList<Complexo> &x);

Complexo cot(Complexo);
QList<Complexo> cot(QList<Complexo> &x);

Complexo csc(Complexo);
QList<Complexo> csc(QList<Complexo> &x);

Complexo sec(Complexo);
QList<Complexo> sec(QList<Complexo> &x);

Complexo cosh(Complexo);
QList<Complexo> cosh(QList<Complexo> &x);

Complexo sinh(Complexo);
QList<Complexo> sinh(QList<Complexo> &x);

Complexo tanh(Complexo);
QList<Complexo> tanh(QList<Complexo> &x);

Complexo coth(Complexo);
QList<Complexo> coth(QList<Complexo> &x);

Complexo csch(Complexo);
QList<Complexo> csch(QList<Complexo> &x);

Complexo sech(Complexo);
QList<Complexo> sech(QList<Complexo> &x);



Complexo acos(Complexo);
QList<Complexo> acos(QList<Complexo> &x);

Complexo asin(Complexo);
QList<Complexo> asin(QList<Complexo> &x);

Complexo atan(Complexo);
QList<Complexo> atan(QList<Complexo> &x);

Complexo atan(Complexo, Complexo);
QList<Complexo> atan(QList<Complexo> &Zy,QList<Complexo> &Zx);

Complexo acot(Complexo);
QList<Complexo> acot(QList<Complexo> &x);

Complexo asec(Complexo);
QList<Complexo> asec(QList<Complexo> &x);

Complexo acsc(Complexo);
QList<Complexo> acsc(QList<Complexo> &x);


Complexo asinh(Complexo);
QList<Complexo> asinh(QList<Complexo> &x);

Complexo acosh(Complexo);
QList<Complexo> acosh(QList<Complexo> &x);

Complexo atanh(Complexo);
QList<Complexo> atanh(QList<Complexo> &x);

Complexo acoth(Complexo);
QList<Complexo> acoth(QList<Complexo> &x);

Complexo acsch(Complexo);
QList<Complexo> acsch(QList<Complexo> &x);

Complexo asech(Complexo);
QList<Complexo> asech(QList<Complexo> &x);


Complexo ln(Complexo);
QList<Complexo> ln(QList<Complexo> &x);

Complexo log(Complexo);
QList<Complexo> log(QList<Complexo> &x);



QDataStream & operator<< (QDataStream& stream, const Complexo& z);
QDataStream & operator>> (QDataStream& stream, Complexo& z);


#endif // COMPLEXO_H
