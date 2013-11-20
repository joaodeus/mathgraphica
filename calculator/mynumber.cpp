#include "mynumber.h"

MyNumber::MyNumber()
{
}


MyNumber::MyNumber(const double &x)
{
    SetMyNumber(x);
}

MyNumber::MyNumber(const Complexo &z)
{
    SetMyNumber(z);
}

MyNumber::MyNumber(const QList<double> &list_)
{
    SetMyNumber(list_);
}

MyNumber::MyNumber(const QList<Complexo> &list_)
{
    SetMyNumber(list_);
}

MyNumber::MyNumber(const Matrix &matrix)
{
    SetMyNumber(matrix);
}



void MyNumber::SetMyNumber(const double &real)
{
    number_complexo.r   = real;
    number_complexo.i   = 0;
    type                = "number";
}


void MyNumber::SetMyNumber(const Complexo &complex_)
{
    number_complexo = complex_;
    type            = "number";
}


void MyNumber::SetMyNumber(const Matrix &matrix_)
{
    number_matrix   = matrix_;  
    type            = "matrix";   
}

void MyNumber::SetMyNumber(const QList<Complexo> &list_)
{
    number_list = list_;
    type        = "list";
}

void MyNumber::SetMyNumber(const QList<double> &list_)
{
    number_list.clear();
    Complexo z;
    for (int i=0;i<list_.size();i++)
    {
        z.r=list_.at(i); z.i=0;
        number_list.append( z );
        //number_list.append( Complexo(list_.at(i),0) );
    }
    type = "list";
}


void MyNumber::setOperatorFunction(const QString &type_)
{  
    type    = type_;
    number_complexo.clear();   
}


bool MyNumber::isNumber()
{
    if ( (type == "number") || (type == "list") || (type == "matrix"))
        return true;
    else
        return false;
}

bool MyNumber::isOperator()
{
    if (type == "+")
        return true;

    if (type == "-")
        return true;

    if (type == "*")
        return true;

    if (type == "/")
        return true;

    if (type == "^")
        return true;

    if (type == "E")
        return true;

    return false;
}




bool MyNumber::isOperatorPlus()
{
    if (type == "+")
        return true;
    else
        return false;
}

bool MyNumber::isOperatorMinus()
{
    if (type == "-")
        return true;
    else
        return false;
}

bool MyNumber::isOperatorMultiplication()
{
    if (type == "*")
        return true;
    else
        return false;
}

bool MyNumber::isOperatorDivision()
{
    if (type == "/")
        return true;
    else
        return false;
}

bool MyNumber::isOperatorPower()
{
    if (type == "^")
        return true;
    else
        return false;
}

bool MyNumber::isOperatorE()
{
    if (type == "E")
        return true;
    else
        return false;
}




bool MyNumber::isFunction()
{
    QString aux;
    return isFunction(aux);
}

bool MyNumber::isFunction(QString &function_)
{

    function_ = type;


    if (!type.compare(QObject::tr("sinc"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("cis"),Qt::CaseInsensitive))
        return true;


    if (!type.compare(QObject::tr("sin"),Qt::CaseInsensitive))
        return true;


    if (!type.compare(QObject::tr("cos"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("tan"),Qt::CaseInsensitive))
        return true;


    if (!type.compare(QObject::tr("cot"),Qt::CaseInsensitive))
        return true;


    if (!type.compare(QObject::tr("csc"),Qt::CaseInsensitive))
        return true;


    if (!type.compare(QObject::tr("sec"),Qt::CaseInsensitive))
        return true;


    if (!type.compare(QObject::tr("sinh"),Qt::CaseInsensitive))
        return true;


    if (!type.compare(QObject::tr("cosh"),Qt::CaseInsensitive))
        return true;


    if (!type.compare(QObject::tr("tanh"),Qt::CaseInsensitive))
        return true;


    if (!type.compare(QObject::tr("coth"),Qt::CaseInsensitive))
        return true;


    if (!type.compare(QObject::tr("csch"),Qt::CaseInsensitive))
        return true;


    if (!type.compare(QObject::tr("sech"),Qt::CaseInsensitive))
        return true;


    if (!type.compare(QObject::tr("asin"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("acos"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("atan"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("acot"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("acsc"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("asec"),Qt::CaseInsensitive))
        return true;


    if (!type.compare(QObject::tr("asinh"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("acosh"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("atanh"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("acoth"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("acsch"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("asech"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("conj"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("real"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("imag"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("abs"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("cbrt"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("sqrt"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("log"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("ln"),Qt::CaseInsensitive))
        return true;

    if (!type.compare(QObject::tr("exp"),Qt::CaseInsensitive))
        return true;


    function_ .clear();
    return false;
}


bool MyNumber::isParentheses()
{
    if (type == "(")
        return true;

    if (type == ")")
        return true;

    if (type == "|")
        return true;

    return false;
}


bool MyNumber::isLeft_Parentheses()
{
    if (type == "(")
        return true;
    else
        return false;
}


bool MyNumber::isRight_Parentheses()
{
    if (type == ")")
        return true;
    else
        return false;
}

bool MyNumber::isParentheses_abs()
{
    if (type == "|")
        return true;
    else
        return false;
}

bool MyNumber::isFunction_or_Operator()
{
    if (isFunction())
        return true;

    if (isOperator())
        return true;

    if (isParentheses())
        return true;

    return false;
}


bool MyNumber::isImaginary()
{
    if ( (type == "number") && (number_complexo.i != 0) )
        return true;
    else
        return false;
}

int MyNumber::operatorPriority()
{
    if (type == "+" || type == "-" )
        return 0;

    if (type == "*" || type == "/" )
        return 1;

    if (type == "^" || type == "E" )
        return 2;

    return -1;
}


//show the number, for debbuging purpose
void MyNumber::showNumber()
{

    if (type == "number")
        QMessageBox::about(0,"results",QString("%1+i%2").arg(number_complexo.r).arg(number_complexo.i));

    // add show to list
    if (type == "list")
        QMessageBox::about(0,"results","todo: add a list viewer");

    if (type == "matrix")
        number_matrix.Show();

}



///////////////////////////////////////////////////////////////////////////////////


// friend operators and assigment operators

MyNumber &MyNumber::operator=(const MyNumber &a)
{  
    type            = a.type;
    number_complexo = a.number_complexo;
    number_matrix   = a.number_matrix;
    number_list     = a.number_list;

    return *this;
}

MyNumber operator+(MyNumber a, MyNumber b)
{

    MyNumber z;


    //  number - number
    if (a.Type() == "number" && b.Type() == "number")
    {
        z.number_complexo   = a.number_complexo + b.number_complexo;
        z.type              = a.type;
        return z;
    }


    //  list - list
    if (a.Type() == "list" && b.Type() == "list")
    {
        z.type      = a.type;

        if (a.numberListComplexo().size() == b.numberListComplexo().size())
        {
            for(int i=0;i<a.number_list.size();i++)
                z.number_list.append(a.number_list[i] + b.number_list[i]);
        }
        else if (a.number_list.size() < b.number_list.size())
        {
            for (int i=0;a.number_list.size();i++)
                z.number_list.append(a.number_list[i] + b.number_list[i]);

            for(int i=a.number_list.size();i<b.number_list.size();i++)
                z.number_list.append(b.number_list[i]);
        }
        else if (a.number_list.size() > b.number_list.size())
        {
            for (int i=0;i<b.number_list.size();i++)
                z.number_list.append(a.number_list[i] + b.number_list[i]);

            for(int i=b.number_list.size();i<a.number_list.size();i++)
                z.number_list.append(a.number_list[i]);
        }

    }


    //  matrix - matrix
    if (a.Type() == "matrix" && b.Type() == "matrix")
    {
        z.number_matrix = a.number_matrix + b.number_matrix;
        z.type          = a.type;
        return z;
    }



    //  number - list
    if (a.Type() == "number" && b.Type() == "list")
    {
        z.type      = b.type;

        for (int i=0;i<b.number_list.size();i++)
            z.number_list.append(a.number_complexo+b.number_list[i]);

        return z;
    }


    //  list - number
    if (a.Type() == "list" && b.Type() == "number")
    {
        z.type = a.type;
        for (int i=0;i<a.number_list.size();i++)
            z.number_list.append(a.number_list[i]+b.number_complexo);

        return z;
    }

    //  number - matrix
    if (a.Type() == "number" && b.Type() == "matrix")
    {
        z.number_matrix = a.number_complexo + b.number_matrix;
        z.type          = b.type;
        return z;
    }

    //  matrix - number
    if (a.Type() == "matrix" && b.Type() == "number")
    {
        z.number_matrix = a.number_matrix + b.number_complexo;
        z.type          = a.type;
        return z;
    }


    return z;
}

MyNumber operator-(MyNumber a, MyNumber b)
{

    MyNumber z;


    //  number - number
    if (a.Type() == "number" && b.Type() == "number")
    {
        z.number_complexo   = a.number_complexo - b.number_complexo;
        z.type              = a.type;
        return z;
    }


    //  list - list
    if (a.Type() == "list" && b.Type() == "list")
    {
        z.type      = a.type;

        if (a.numberListComplexo().size() == b.numberListComplexo().size())
        {
            for(int i=0;i<a.number_list.size();i++)
                z.number_list.append(a.number_list[i] - b.number_list[i]);
        }
        else if (a.number_list.size() < b.number_list.size())
        {
            for (int i=0;a.number_list.size();i++)
                z.number_list.append(a.number_list[i] - b.number_list[i]);

            for(int i=a.number_list.size();i<b.number_list.size();i++)
                z.number_list.append(-b.number_list[i]);
        }
        else if (a.number_list.size() > b.number_list.size())
        {
            for (int i=0;i<b.number_list.size();i++)
                z.number_list.append(a.number_list[i] - b.number_list[i]);

            for(int i=b.number_list.size();i<a.number_list.size();i++)
                z.number_list.append(a.number_list[i]);
        }

    }


    //  matrix - matrix
    if (a.Type() == "matrix" && b.Type() == "matrix")
    {
        z.number_matrix = a.number_matrix - b.number_matrix;
        z.type          = a.type;
        return z;
    }



    //  number - list
    if (a.Type() == "number" && b.Type() == "list")
    {
        z.type      = b.type;

        for (int i=0;i<b.number_list.size();i++)
            z.number_list.append(a.number_complexo - b.number_list[i]);

        return z;
    }


    //  list - number
    if (a.Type() == "list" && b.Type() == "number")
    {
        z.type = a.type;
        for (int i=0;i<a.number_list.size();i++)
            z.number_list.append(a.number_list[i] - b.number_complexo);

        return z;
    }

    //  number - matrix
    if (a.Type() == "number" && b.Type() == "matrix")
    {
        z.number_matrix = a.number_complexo - b.number_matrix;
        z.type          = b.type;
        return z;
    }

    //  matrix - number
    if (a.Type() == "matrix" && b.Type() == "number")
    {
        z.number_matrix = a.number_matrix - b.number_complexo;
        z.type          = a.type;
        return z;
    }


    return z;

}

MyNumber operator-(MyNumber a)
{

    MyNumber z;

/*    if (a.Type() == "matrix")
    {
        z.number_matrix = -1 * a.number_matrix;
        z.type          = a.type;     
        return z;
    }
*/

    if (a.Type() == "number")
    {
        z.number_complexo    = -a.number_complexo;
        z.type      = a.type;      
        return z;
    }

    if (a.Type() == "list")
    {
        for(int i=0;i<a.number_list.size();i++)
            z.number_list.append(-a.number_list[i]);

        z.type = a.type;
        return z;
    }


    if (a.Type() == "matrix")
    {
        z.number_matrix    = -a.number_matrix;
        z.type      = a.type;
        return z;
    }


    return z;
}

MyNumber operator*(MyNumber &a, MyNumber &b)
{
    MyNumber z;



    //  number - number
    if (a.Type() == "number" && b.Type() == "number")
    {
        z.number_complexo   = a.number_complexo * b.number_complexo;
        z.type              = a.type;
        return z;
    }


    //  list - list
    if (a.Type() == "list" && b.Type() == "list")
    {
        z.type      = a.type;

        if (a.numberListComplexo().size() == b.numberListComplexo().size())
        {
            for(int i=0;i<a.number_list.size();i++)
                z.number_list.append(a.number_list[i] * b.number_list[i]);
        }
        else if (a.number_list.size() < b.number_list.size())
        {
            for (int i=0;a.number_list.size();i++)
                z.number_list.append(a.number_list[i] * b.number_list[i]);

            for(int i=a.number_list.size();i<b.number_list.size();i++)
                z.number_list.append(b.number_list[i]);
        }
        else if (a.number_list.size() > b.number_list.size())
        {
            for (int i=0;i<b.number_list.size();i++)
                z.number_list.append(a.number_list[i] * b.number_list[i]);

            for(int i=b.number_list.size();i<a.number_list.size();i++)
                z.number_list.append(a.number_list[i]);
        }

    }


    //  matrix - matrix
    if (a.Type() == "matrix" && b.Type() == "matrix")
    {
        z.number_matrix = a.number_matrix * b.number_matrix;
        z.type          = a.type;
        return z;
    }



    //  number - list
    if (a.Type() == "number" && b.Type() == "list")
    {
        z.type      = b.type;

        for (int i=0;i<b.number_list.size();i++)
            z.number_list.append(a.number_complexo * b.number_list[i]);

        return z;
    }


    //  list - number
    if (a.Type() == "list" && b.Type() == "number")
    {
        z.type = a.type;
        for (int i=0;i<a.number_list.size();i++)
            z.number_list.append(a.number_list[i] * b.number_complexo);

        return z;
    }

    //  number - matrix
    if (a.Type() == "number" && b.Type() == "matrix")
    {
        z.number_matrix = a.number_complexo * b.number_matrix;
        z.type          = b.type;
        return z;
    }

    //  matrix - number
    if (a.Type() == "matrix" && b.Type() == "number")
    {
        z.number_matrix = a.number_matrix * b.number_complexo;
        z.type          = a.type;
        return z;
    }


    return z;

}



//check this function later, division of matrix is always complicate
MyNumber operator/(MyNumber &a, MyNumber &b)
{

    MyNumber z;

    //  number - number
    if (a.Type() == "number" && b.Type() == "number")
    {
        z.number_complexo   = a.number_complexo / b.number_complexo;
        z.type              = a.type;
        return z;
    }


    //  list - list
    if (a.Type() == "list" && b.Type() == "list")
    {
        z.type      = a.type;

        if (a.numberListComplexo().size() == b.numberListComplexo().size())
        {
            for(int i=0;i<a.number_list.size();i++)
                z.number_list.append(a.number_list[i] / b.number_list[i]);
        }
        else if (a.number_list.size() < b.number_list.size())
        {
            for (int i=0;a.number_list.size();i++)
                z.number_list.append(a.number_list[i] / b.number_list[i]);

            for(int i=a.number_list.size();i<b.number_list.size();i++)
                z.number_list.append(b.number_list[i]);
        }
        else if (a.number_list.size() > b.number_list.size())
        {
            for (int i=0;i<b.number_list.size();i++)
                z.number_list.append(a.number_list[i] / b.number_list[i]);

            for(int i=b.number_list.size();i<a.number_list.size();i++)
                z.number_list.append(a.number_list[i]);
        }

    }


    //  matrix - matrix
    if (a.Type() == "matrix" && b.Type() == "matrix")
    {
        z.number_matrix = a.number_matrix / b.number_matrix;
        z.type          = a.type;
        return z;
    }



    //  number - list
    if (a.Type() == "number" && b.Type() == "list")
    {
        z.type      = b.type;

        for (int i=0;i<b.number_list.size();i++)
            z.number_list.append(a.number_complexo / b.number_list[i]);

        return z;
    }


    //  list - number
    if (a.Type() == "list" && b.Type() == "number")
    {
        z.type = a.type;
        for (int i=0;i<a.number_list.size();i++)
            z.number_list.append(a.number_list[i] / b.number_complexo);

        return z;
    }

    //  number - matrix
    if (a.Type() == "number" && b.Type() == "matrix")
    {
        z.number_matrix = a.number_complexo / b.number_matrix;
        z.type          = b.type;
        return z;
    }

    //  matrix - number
    if (a.Type() == "matrix" && b.Type() == "number")
    {
        z.number_matrix = a.number_matrix / b.number_complexo;
        z.type          = a.type;
        return z;
    }


    return z;
}

MyNumber operator^(MyNumber &a, MyNumber &b)
{

    MyNumber z;

    //  number - number
    if (a.Type() == "number" && b.Type() == "number")
    {
        z.number_complexo   = a.number_complexo ^ b.number_complexo;
        z.type              = a.type;
        return z;
    }


    //  list - list
    if (a.Type() == "list" && b.Type() == "list")
    {
        z.type      = a.type;

        if (a.numberListComplexo().size() == b.numberListComplexo().size())
        {
            for(int i=0;i<a.number_list.size();i++)
                z.number_list.append(a.number_list[i] ^ b.number_list[i]);
        }
        else if (a.number_list.size() < b.number_list.size())
        {
            for (int i=0;a.number_list.size();i++)
                z.number_list.append(a.number_list[i] ^ b.number_list[i]);

            for(int i=a.number_list.size();i<b.number_list.size();i++)
                z.number_list.append(b.number_list[i]);
        }
        else if (a.number_list.size() > b.number_list.size())
        {
            for (int i=0;i<b.number_list.size();i++)
                z.number_list.append(a.number_list[i] ^ b.number_list[i]);

            for(int i=b.number_list.size();i<a.number_list.size();i++)
                z.number_list.append(a.number_list[i]);
        }

    }


    //  matrix - matrix
    if (a.Type() == "matrix" && b.Type() == "matrix")
    {
        z.number_matrix = a.number_matrix ^ b.number_matrix;
        z.type          = a.type;
        return z;
    }



    //  number - list
    if (a.Type() == "number" && b.Type() == "list")
    {
        z.type      = b.type;

        for (int i=0;i<b.number_list.size();i++)
            z.number_list.append(a.number_complexo ^ b.number_list[i]);

        return z;
    }


    //  list - number
    if (a.Type() == "list" && b.Type() == "number")
    {
        z.type = a.type;
        for (int i=0;i<a.number_list.size();i++)
            z.number_list.append(a.number_list[i] ^ b.number_complexo);

        return z;
    }

    //  number - matrix
    if (a.Type() == "number" && b.Type() == "matrix")
    {
        z.number_matrix = a.number_complexo ^ b.number_matrix;
        z.type          = b.type;
        return z;
    }

    //  matrix - number
    if (a.Type() == "matrix" && b.Type() == "number")
    {
        z.number_matrix = a.number_matrix ^ b.number_complexo;
        z.type          = a.type;
        return z;
    }


    return z;

}

///////////////////////////////////////////////////////////
// getters()

Complexo MyNumber::numberComplexo()
{
    return number_complexo;
}

double MyNumber::numberReal()
{
    return number_complexo.r;
}


Matrix MyNumber::numberMatrix()
{
    return number_matrix;
}

QList<Complexo> MyNumber::numberListComplexo()
{
    return number_list;
}

QList<double> MyNumber::numberListReal()
{
    QList<double> aux;
    for (int i=0;i<number_list.size();i++)
    {
        aux.append(number_list.at(i).r);
    }

    return aux;
}

QString MyNumber::Type()
{
    return type;
}
