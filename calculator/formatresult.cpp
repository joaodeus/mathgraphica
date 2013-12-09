#include "formatresult.h"

#define DEGREE  0
#define RAD     1
#define GRAD    2


FormatResult::FormatResult()
{
    Degree_Rad_Grad = 1;

    bAutomaticPrecision = true;
    precision           = -1;
    format              = 'G';
    bGroup              = true;
    bPolarForm          = false;

    //int precision=-1;//default
    //char format='G'; //auto, 'E' or 'f'
    //E - format as [-]9.9E[+|-]999 - scientific
    //f - format as [-]9.9 - fixed decimal
    //G - use E or f format, whichever is the most concise - automatic

    // add polar form
    //P - format complex numbers as r*e^(o*i)
    //where r is radius and o is the angle, i is imaginary

}


QString FormatResult::groupDigits(const QString &str, const bool &bGroup)
{
    if (bGroup == false)
        return str;

    QString aux=str;
    QString auxE;
    QStringList listE; //splits the number in the exponential E
    //i.e  3.435E+7 , splits into 3.435 and E+7
    listE=aux.split("E");

    if (listE.size() == 2)
        auxE=listE[1];
    else
        auxE="";

    QStringList listPoint;//split the number in the decimal point
    //i.e.:  45.23 is split into 45 and 23
    listPoint=listE[0].split(".");

    QString aux1="";//

    int count=0;
    for(int i=listPoint[0].size()-1;i>=0;i--)
    {
        if (count ==3)
        {
            aux1.prepend(" ");
            count=0;
        }
        aux1.prepend(listPoint[0].at(i));
        count++;
    }

    QString aux2="";
    if (listPoint.size() == 2)
    {
        count=0;
        for(int i=0;i<listPoint[1].size();i++)
        {
            if (count ==3)
            {
                aux2.append(" ");
                count=0;
            }

            aux2.append(listPoint[1].at(i));
            count++;
        }
    }

    QString final;
    final=aux1;
    if (listPoint.size() == 2)
        final=final+"."+aux2;

    if (listE.size() == 2)
        final=final+"E"+auxE;

    return final;
}


QString FormatResult::formatPolarForm(const Complexo &z)
{
    double radius = sqrt(z.r * z.r + z.i * z.i);
    double angle = atan2(z.i, z.r);

    if (angle < 0)
    {
        angle = PI + (PI + angle);
    }

    switch (Degree_Rad_Grad)
    {
    case DEGREE: //degree
        angle = angle * 180/PI;
        //Degree_Rad_Grad_aux.SetMyNumber(180/PI);
        break;

    case RAD: //rad
        break;

    case GRAD: //grad
        angle = angle * 200/PI;
        break;
    }

    QString radius_str = groupDigits(QString("%1").arg(radius,0,format,precision),bGroup);
    QString angle_str = groupDigits(QString("%1").arg(angle,0,format,precision),bGroup);
    return QString("%1cis(%2)").arg(radius).arg(angle);

}

//QString FormatResult::formatResult(const Complexo &z, bool bAutomaticPrecision, int precision, char format, bool bGroup)
QString FormatResult::formatResult(const Complexo &z)
{
    //options:
    //general - G
    //fixed decimal - f
    //scientific - E

    if (bAutomaticPrecision)
        precision=-1;

    QString aux;
   // char format;
   // format='G';

    // if format is polar form
    if (bPolarForm)
    {
        return formatPolarForm(z);
    }


    // if format is not polar form

    if (z.i ==0) //if imaginary is null
    {            
        aux=QString("%1").arg(z.r, 0, format, precision);
        aux=groupDigits(aux,bGroup);
    }
    else // imaginary is not null
    {
        if (z.r != 0)
        {
            QString aux1=groupDigits(QString("%1").arg(z.r,0,format,precision),bGroup);
            QString aux2;

            if (z.i >0)
            {
                aux2=groupDigits(QString("%1").arg(z.i,0,format,precision),bGroup);
                aux=aux1+" + "+aux2+"i";
                if (aux2 == "1")
                {
                    aux=aux1+" + i";
                }
                else
                {
                    aux=aux1+" + "+aux2+"i";
                }

            }
            else
            {
                aux2=groupDigits(QString("%1").arg(-z.i,0,format,precision),bGroup);
                //aux=aux1+" - "+aux2+"i";
                if (aux2 == "1")
                {
                    aux=aux1+" - i";
                }
                else
                {
                    aux=aux1+" - "+aux2+"i";
                }
            }

        }
        else
        {
            aux=groupDigits(QString("%1").arg(z.i,0,format,precision),bGroup);
            aux=aux+"i";
        }
    }

    return aux;
}

QString FormatResult::formatResult(const double &x)
{
    Complexo z(x,0);
    return formatResult(z);
}


QString FormatResult::formatResult(MyNumber &num)
{
    if (num.Type() == "number")
        return formatResult(num.numberComplexo());
    else if (num.Type() == "matrix")
    {
        Matrix m = num.numberMatrix();
        //m.Show();
        return formatResult(m);
    }
    return "";
}

QString FormatResult::formatResult(Matrix &matrix)
{
    QString mat = "[";
    for (int l=0;l<matrix.lineCount();l++)
    {
        mat += matrix.GetLineColText(l,0) ;
        for (int c=1;c<matrix.columnCount();c++)
        {
            mat += ", "+matrix.GetLineColText(l,c);
        }
        mat += " ; ";
    }
    mat.chop(3);
    mat += "]";


    return mat;
}

void FormatResult::setFormatResult(const bool &bAutomaticPrecision_, const int &precision_, const char &format_, const bool &bGroup_)
{
    bAutomaticPrecision = bAutomaticPrecision_;
    precision = precision_;
    format = format_;
    bGroup = bGroup_;
}

void FormatResult::setAutomaticPrecision(const bool &bAutomaticPrecision_)
{
    bAutomaticPrecision = bAutomaticPrecision_;
}

void FormatResult::setPrecision(const int &precision_)
{
    precision = precision_;
}


void FormatResult::setFormat(const char &format_)
{
    format = format_;
}

void FormatResult::setGroupDigits(const bool &bGroup_)
{
    bGroup = bGroup_;
}

void FormatResult::setPolarForm(const bool &bPolarForm_)
{
    bPolarForm = bPolarForm_;
}


bool FormatResult::getAutomaticPrecision()
{
    return bAutomaticPrecision;
}

int FormatResult::getPrecision()
{
    return precision;
}

char FormatResult::getFormat()
{
    return format;
}

bool FormatResult::getGroup()
{
    return bGroup;
}

bool FormatResult::getPolarForm()
{
    return bPolarForm;
}

/*
QString FormatResult::formatResult( const Complexo &z)
{
    //int precision=-1;//default
    //char format='G'; //auto, 'E' or 'f'
    //E - format as [-]9.9E[+|-]999
    //f - format as [-]9.9
    //G - use E or f format, whichever is the most concise

    return formatResult(z, true, precision, format, true);
}
*/

/*
QString FormatResult::formatResult( const Complexo &z, const int &precision)
{
    char format='G';
    return formatResult(z, false, precision, format, true);
}*/
