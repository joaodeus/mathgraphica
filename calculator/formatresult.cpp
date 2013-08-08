#include "formatresult.h"

FormatResult::FormatResult()
{
    bAutomaticPrecision = true;
    precision = -1;
    format = 'G';
    bGroup = false;

    //int precision=-1;//default
    //char format='G'; //auto, 'E' or 'f'
    //E - format as [-]9.9E[+|-]999
    //f - format as [-]9.9
    //G - use E or f format, whichever is the most concise
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

    if (z.i ==0) //if imaginary is null
    {
        aux=QString("%1").arg(z.r,0,format,precision);
        aux=groupDigits(aux,bGroup);
        //aux=QString("%1").arg(z.r,0,'G',25);
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

            /*
            if (z.i > 0)
                aux=QString("%1+%2i").arg(z.r,0,format,precision).arg(z.i,0,format,precision);
            else
                aux=QString("%1-%2i").arg(z.r,0,format,precision).arg(-z.i,0,format,precision);
                */
        }
        else
        {
            aux=groupDigits(QString("%1").arg(z.i,0,format,precision),bGroup);
            aux=aux+"i";
            //aux=QString("%1i").arg(z.i,0,format,precision);
        }
    }

//  AfxMessageBox(aux);
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
        m.Show();
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
