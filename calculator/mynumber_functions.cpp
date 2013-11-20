#include "mynumber_functions.h"


//////////////////////////////////////////////////////////////////
// trignometric functions

MyNumber sinc(MyNumber &number_)
{
    MyNumber z;


    if (number_.Type() == "number")
    {
        z.SetMyNumber( sinc(number_.numberComplexo()) );
        return z;
    }   

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(sinc(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( sinc(mat) );
        return z;
    }

    return z;
}



MyNumber cis(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( cis(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(cis(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( cis(mat) );
        return z;
    }

    return z;
}


MyNumber sin(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( sin(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(sin(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( sin(mat) );
        return z;
    }

    return z;
}

MyNumber cos(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( cos(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(cos(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( cos(mat) );
        return z;
    }

    return z;
}


MyNumber tan(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( tan(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(tan(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( tan(mat) );
        return z;
    }

    return z;
}

MyNumber cot(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( cot(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(cot(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( cot(mat) );
        return z;
    }

    return z;
}

MyNumber sec(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( sec(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(sec(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( sec(mat) );
        return z;
    }

    return z;
}

MyNumber csc(MyNumber &number_)
{
    MyNumber z;


    if (number_.Type() == "number")
    {
        z.SetMyNumber( csc(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(csc(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( csc(mat) );
        return z;
    }

    return z;
}

//////////////////////////////////////////////////////////////////


MyNumber sinh(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( sinh(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(sinh(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( sinh(mat) );
        return z;
    }

    return z;
}

MyNumber cosh(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( cosh(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(cosh(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( cosh(mat) );
        return z;
    }

    return z;
}

MyNumber tanh(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( tanh(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(tanh(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( tanh(mat) );
        return z;
    }

    return z;
}

MyNumber coth(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( coth(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(coth(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( coth(mat) );
        return z;
    }

    return z;
}

MyNumber sech(MyNumber &number_)
{
    MyNumber z;


    if (number_.Type() == "number")
    {
        z.SetMyNumber( sech(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(sech(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( sech(mat) );
        return z;
    }

    return z;
}

MyNumber csch(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( csch(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(csch(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( csch(mat) );
        return z;
    }

    return z;
}


///////////////////////////////////////////////////////////////


MyNumber asin(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( asin(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(asin(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( asin(mat) );
        return z;
    }

    return z;
}

MyNumber acos(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( acos(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(acos(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( acos(mat) );
        return z;
    }

    return z;
}

MyNumber atan(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( atan(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(atan(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( atan(mat) );
        return z;
    }

    return z;
}

MyNumber acot(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( acot(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(acot(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( acot(mat) );
        return z;
    }

    return z;
}

MyNumber asec(MyNumber &number_)
{
    MyNumber z;


    if (number_.Type() == "number")
    {
        z.SetMyNumber( asec(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(asec(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( asec(mat) );
        return z;
    }

    return z;
}

MyNumber acsc(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( acsc(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(acsc(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( acsc(mat) );
        return z;
    }

    return z;
}



///////////////////////////////////////////////////////////////


MyNumber asinh(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( asinh(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(asinh(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( asinh(mat) );
        return z;
    }

    return z;
}

MyNumber acosh(MyNumber &number_)
{
    MyNumber z;


    if (number_.Type() == "number")
    {
        z.SetMyNumber( acosh(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(acosh(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( acosh(mat) );
        return z;
    }

    return z;
}

MyNumber atanh(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( atanh(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(atanh(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( atanh(mat) );
        return z;
    }

    return z;
}

MyNumber acoth(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( acoth(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(acoth(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( acoth(mat) );
        return z;
    }

    return z;
}

MyNumber asech(MyNumber &number_)
{
    MyNumber z;


    if (number_.Type() == "number")
    {
        z.SetMyNumber( asech(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(asech(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( asech(mat) );
        return z;
    }

    return z;
}

MyNumber acsch(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( acsch(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(acsch(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( acsch(mat) );
        return z;
    }

    return z;
}


///////////////////////////////////////////////////////////////


MyNumber log(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( log(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(log(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( log(mat) );
        return z;
    }

    return z;
}

MyNumber ln(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( ln(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(ln(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( ln(mat) );
        return z;
    }

    return z;
}

MyNumber exp(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( exp(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(exp(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( exp(mat) );
        return z;
    }

    return z;
}


MyNumber sqrt(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( sqrt(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(sqrt(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( sqrt(mat) );
        return z;
    }

    return z;
}

MyNumber cbrt(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( cbrt(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(cbrt(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( cbrt(mat) );
        return z;
    }

    return z;
}


//////////////////////////////////////////////////////////////////////


MyNumber real(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( real(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(real(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( real(mat) );
        return z;
    }

    return z;
}

MyNumber imag(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( imag(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(imag(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( imag(mat) );
        return z;
    }

    return z;
}

MyNumber arg(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( arg(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(arg(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( arg(mat) );
        return z;
    }

    return z;
}

MyNumber conj(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( conj(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(conj(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( conj(mat) );
        return z;
    }

    return z;
}


MyNumber cabs(MyNumber &number_)
{
    MyNumber z;

    if (number_.Type() == "number")
    {
        z.SetMyNumber( cabs(number_.numberComplexo()) );
        return z;
    }

    if (number_.Type() == "list")
    {
        QList<Complexo> list = number_.numberListComplexo();
        z.SetMyNumber(cabs(list));
        return z;
    }

    if (number_.Type() == "matrix")
    {
        Matrix mat = number_.numberMatrix();
        z.SetMyNumber( abs(mat) );
        return z;
    }

    return z;
}

