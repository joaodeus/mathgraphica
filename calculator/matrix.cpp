#include "matrix.h"
#include <QMessageBox>
#include "calculator.h"
#include "formatresult.h"
#include "matrix_gui.h"

Matrix::Matrix()
{
    NCol=NLine=0;
    ERRO=false;
    bAbortSystemEquationCalculation=false;
    isCalculating=false;
   // bShowButtons =true;
  //  sizeHeader=1;

}


Matrix::~Matrix()
{

}

void Matrix::AddLines(int n_lines)
{

    QVector<QString>    aux1(NCol*n_lines,"");
    QVector<Complexo>   aux2(NCol*n_lines,Complexo());

    NLine                   += n_lines;
    matriz                  += aux1;
    matrixComplexElements   += aux2;

    /*
    for(int l=0;l<2*n_lines;l++)
    {
        matriz.append("");
        matrixComplexElements.append(Complexo());
    }*/

}


void Matrix::SetLinesCols(int Lines, int Columns)
{
    NLine = Lines;
    NCol = Columns;

    matriz.resize(Lines*Columns);
    matrixComplexElements.resize(Lines*Columns);

   /* matriz.clear();
    matrixComplexElements.clear();

    for(int i=0;i<C;i++)
    {
        for(int j=0;j<L;j++)
        {
            matriz.append("");
            matrixComplexElements.append(Complexo());
        }
    }*/
}


void Matrix::SetLineColText(int L,int C, QString text)
{
    ERRO=false;
    if (L > NLine-1)
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("The row is bigger then matrix row size"));
        ERRO=true;
        return;
    }

    if (C > NCol-1)
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("The column is bigger then matrix column size"));
        ERRO=true;
        return;
    }

    Calculator calc;
    matriz[L*NCol+C]=text;
    MyNumber aux = calc.SolveExpression(text);
    if (aux.Type() == "real")
            matrixComplexElements[L*NCol+C]=aux.numberReal();
    else
            matrixComplexElements[L*NCol+C]=aux.numberComplexo();
}

void Matrix::SetLineColNumber(int L,int C, Complexo num)
{
    ERRO=false;
    if (L > NLine-1)
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("The row is bigger then matrix row size"));
        ERRO=true;
        return;
    }

    if (C > NCol-1)
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("The column is bigger then matrix column size"));
        ERRO=true;
        return;
    }

    //matriz[L*NCol+C] = ComplexoToQString(num);
    FormatResult format;
    matriz[L*NCol+C] = format.formatResult(num);
    matrixComplexElements[L*NCol+C] = num;
}


bool Matrix::SetLineElements(QStringList &lineElements, int &nLine)
{
    if ( (nLine >= lineCount() || nLine < 0) && (lineElements.size() != columnCount()) )
        return false;


    for (int i=0;i<lineElements.size();i++)
    {
        SetLineColText(nLine,i,lineElements.at(i));
    }

    return true;
}


void Matrix::clear()
{
    SetLinesCols(0,0);
}


////////////////////////////////////////////////////////////
//array methods

//set an array from min to max with increments of step
int Matrix::setArray(const double &min, const double &max, const double &step)
{
    SetLinesCols(1, int((max-min)/step+1));

    double element=min;
    for(int i=0;i<columnCount();i++)
    {
        SetLineColNumber(0,i,element);
        element+=step;
    }

    return columnCount();
}


//set an array with (max-min+1) elements with increments of one unit
int Matrix::setArray(const double &min, const double &max)
{
    SetLinesCols(1, int((max-min)+1));

    double element=min;
    for(int i=0;i<columnCount();i++)
    {
        SetLineColNumber(0,i,element);
        element++;
    }

    return columnCount();
}


//set an array with count elements
void Matrix::setArrayElements(const Complexo &element, const unsigned int &count)
{
    NLine   = 1;
    NCol    = count;
    FormatResult format;
    matriz.fill(format.formatResult(element), count);
    //matriz.fill(ComplexoToQString(element), count);
    matrixComplexElements.fill(element, count);

    /*SetLinesCols(1, count);
    for(int i=0;i<columnCount();i++)
    {
        SetLineColNumber(0,i,element);
    }*/
}



///////////////////////////


void Matrix::SetMatrixOnes(int L, int C)
{
    NLine = L;
    NCol = C;
    int count = L*C;

    matriz.fill("1",count);
    matrixComplexElements.fill(Complexo(1,0),count);

    /*matriz.clear();
    matrixComplexElements.clear();

    for(int j=0;j<L;j++)//lines
    {
        for(int i=0;i<C;i++)//colums
        {
            matriz.append("1");
            matrixComplexElements.append(Complexo(1,0));
        }
    }*/
}

void Matrix::SetMatrixZeros(int L, int C)
{
    NLine = L;
    NCol = C;
    int count = L*C;

    matriz.fill("0",count);
    matrixComplexElements.fill(Complexo(),count);

    /*
    NLine = L;
    NCol = C;
    matriz.clear();
    matrixComplexElements.clear();

    for(int i=0;i<C;i++)//colums
    {
        for(int j=0;j<L;j++)//lines
        {
            matriz.append("0");
            matrixComplexElements.append(Complexo());
        }
    }*/
}


void Matrix::SetMatrixRandom(int L, int C)
{
    NLine = L;
    NCol = C;
    matriz.clear();
    matrixComplexElements.clear();


    for(int i=0;i<C;i++)//colums
    {
        for(int j=0;j<L;j++)//lines
        {
            int number = rand()%1000;
            FormatResult format;
            matriz.append(format.formatResult(number));
            matrixComplexElements.append(Complexo(number,0));
        }
    }
}

void Matrix::random()
{
   // srand ( time(NULL) );

    for(int l=0;l<NLine;l++)
    {
        for(int c=0;c<NCol;c++)
        {
            SetLineColNumber(l,c,rand()%1000);
        }
    }

}


void Matrix::SetMatrixDiagonal(int L, int C)
{
    NLine = L;
    NCol = C;

    matriz.clear();
    matrixComplexElements.clear();

    for(int l=0;l<L;l++)
    {
        for(int i=0;i<C;i++)
        {
            if (i==l)
            {
                matriz.append("1");
                matrixComplexElements.append(Complexo(1,0));
            }
            else
            {
                matriz.append("0");
                matrixComplexElements.append(Complexo());
            }
        }
    }
}

//////////////////////////////////////


void Matrix::VectorToMatrix(int col, int line,QVector<QString> &vect)
{
    NLine = line;
    NCol = col;
    ERRO=false;

    if (vect.size() != (col * line))
    {
        ERRO=true;
        return ;
    }

    matriz.clear();
    //matriz=vect;
    matrixComplexElements.clear();

    int k=0;
    Calculator calc;

    matriz.resize(line*col);
    matrixComplexElements.resize(line*col);


    for(int c=0;c<col;c++)
    {
        for(int l=0;l<line;l++)
        {
            SetLineColNumber(l, c, calc.SolveExpression( vect.at(k) ).numberComplexo() );
            //matrixComplexElements.append( calc.SolveExpression( vect.at(k) ).numberComplexo() );
            k++;
        }
    }



}

void Matrix::MatrixToVector(QVector<QString> &vect)
{
    vect = matriz;
    /*listStr.clear();
    int k=0;
    for(int i=0;i<NCol;i++)
    {
        for(int j=0;j<NLine;j++)
        {
            listStr.append(matriz.at(k));
            k++;
        }
    }*/

}

QVector<QString> Matrix::MatrixToVector()
{
   /* QVector<QString> vect;
    int k=0;


    for(int j=0;j<NLine;j++)
    {
        for(int i=0;i<NCol;i++)
        {
            vect.append(matriz.at(k));
            k++;
        }
    }*/

    return this->matriz;
}


/////////////////////////////////////////////////////

QString Matrix::GetLineColText(int L, int C)
{
    ERRO=false;
    if (L > NLine-1)
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("The row is bigger then matrix row size"));
        ERRO=true;
        return "";
    }

    if (C > NCol-1)
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("The column is bigger then matrix column size"));
        ERRO=true;
        return "";
    }
    return matriz[L*NCol+C];
}

Complexo Matrix::GetLineColNumber(int L,int C)
{
    ERRO=false;
    if (L > NLine-1)
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("The row is bigger then matrix row size"));
        ERRO=true;
        return Complexo();
    }

    if (C > NCol-1)
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("The column is bigger then matrix column size"));
        ERRO=true;
        return Complexo();
    }

    return matrixComplexElements[L*NCol+C];
}

////////////////////////////////////////////////////////7


int Matrix::RemoveLineCol(int L, int C)
{
    ERRO=false;
    if ( (C > NCol-1) || (C < 0) )
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("The selected column is invalid"));
        ERRO=true;
        return 0;
    }

    if ( (L > NLine-1) || (L < 0) )
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("The selected row is invalid"));
        ERRO=true;
        return 0;
    }

    //remove coluna
    for(int l=NLine-1;l>=0;l--)
    {
        matriz.remove(l*NCol+C);
        matrixComplexElements.remove(l*NCol+C);
    }
    NCol=NCol-1;


    //remove linha
    //matriz.RemoveAt(lr*NCol,NCol);
    for(int l=0;l<NCol;l++)
    {
        matriz.remove(L*NCol);
        matrixComplexElements.remove(L*NCol);
    }

    NLine=NLine-1;

    return 1;
}



int Matrix::RemoveCol(int C)
{
    ERRO=false;
    if ( (C > NCol-1) || (C < 0) )
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("The selected column is invalid"));
        ERRO=true;
        return 0;
    }

    //remove column
    for(int l=NLine-1;l>=0;l--)
    {
        matriz.remove(l*NCol+C);
        matrixComplexElements.remove(l*NCol+C);
    }
    NCol=NCol-1;
    return 1;
}

int Matrix::RemoveLine(int L)
{
    ERRO=false;
    if ( (L > NLine-1) || (L < 0) )
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("The selected row is invalid"));
        ERRO=true;
        return 0;
    }

    //remove row
    //matriz.removeAt(L*NCol,NCol);
    for(int i=0;i<NCol;i++)
    {
        matriz.remove(L*NCol);
        matrixComplexElements.remove(L*NCol);
    }
    NLine=NLine-1;
    return 1;
}

int Matrix::SwapLines(int L1, int L2)
{
    ERRO=false;
    if ( (L1 < 0) || (L1 > lineCount()) || (L2 < 0) || (L2 > lineCount()) )
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("The selected row is invalid"));
        ERRO=true;
        return 0;
    }

    QString aux;
    for(int i=0;i<columnCount();i++)
    {
        aux = GetLineColText(L1,i);
        SetLineColText(L1,i,GetLineColText(L2,i));
        SetLineColText(L2,i,aux);
    }

    return 1;
}

int Matrix::searchInLines(QString word, int column)
{
    if (column > (NCol-1) )
        return -1;

    for(int i=0;i<NLine;i++)
    {
        if ( word == GetLineColText(i,column) )
            return i;
    }

    return -1;
}


////////////////////////////////////////////////////////
// operator's


Matrix &Matrix::operator=(const Matrix &a )
{
    //this->matriz.clear();
    //matriz.SetSize(a.matriz.GetSize());

    this->matriz = a.matriz;
    this->matrixComplexElements = a.matrixComplexElements;
    //for(int i=0;i<a.matriz.size();i++)
    //    matriz.append(a.matriz[i]);

    //X.clear();
    this->X = a.X;
    //for(i=0;i<a.X.size();i++)
    //    X.append(a.X[i]);
    NLine=a.NLine;
    NCol=a.NCol;
    ERRO=a.ERRO;
    bAbortSystemEquationCalculation=a.bAbortSystemEquationCalculation;

    return *this;  // Assignment operator returns left side.
}


Matrix operator+( Matrix &a , Matrix &b )
{

    Matrix z;

    if ( ! (a.columnCount()==b.columnCount() && a.lineCount()==b.lineCount() ) )
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("Sum error. Matrix dimensions don't match."));
        z.ERRO=true;
        return z;
    }

    int L=a.lineCount();
    int C=a.columnCount();
    z.SetLinesCols(L,C);
    //z.Show();

    for(int l=0;l<L;l++)
    {
        for(int c=0;c<C;c++)
        {
            z.SetLineColNumber(l,c,a.GetLineColNumber(l,c)+b.GetLineColNumber(l,c));
        }
    }

    return z;
}


Matrix operator+(const double &a, Matrix &b)
{
    Matrix z;
    int NLines=b.lineCount();
    int NCols=b.columnCount();

    z.SetLinesCols(NLines,NCols);

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            Complexo zz = b.GetLineColNumber(l,c);
            zz = a+b.GetLineColNumber(l,c);
            z.SetLineColNumber(l,c,a+b.GetLineColNumber(l,c));
        }
    }

    return z;
}

Matrix operator+(Matrix &a, const double &b)
{
    return b+a;
}


Matrix operator+(const Complexo &a, Matrix &b)
{
    Matrix z;
    int NLines=b.lineCount();
    int NCols=b.columnCount();

    z.SetLinesCols(NLines,NCols);

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            z.SetLineColNumber(l,c,a+b.GetLineColNumber(l,c));
        }
    }
    return z;
}

Matrix operator+(Matrix &a, const Complexo &b)
{
    return b+a;
}



Matrix operator-( Matrix &a , Matrix &b )
{
    Matrix z;

    if ( ! (a.columnCount()==b.columnCount() && a.lineCount()==b.lineCount() ) )
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("Subtraction error. Matrix dimensions don't match."));
        z.ERRO=true;
        return z;
    }

    int L=a.lineCount();
    int C=a.columnCount();
    z.SetLinesCols(L,C);

    for(int l=0;l<L;l++)
    {
        for(int c=0;c<C;c++)
        {
            z.SetLineColNumber(l,c,a.GetLineColNumber(l,c)-b.GetLineColNumber(l,c));
        }
    }

    return z;
}



Matrix operator-(const double &a, Matrix &b)
{
    Matrix z;
    int NLines=b.lineCount();
    int NCols=b.columnCount();

    z.SetLinesCols(NLines,NCols);

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            z.SetLineColNumber(l,c,a-b.GetLineColNumber(l,c));
        }
    }

    return z;
}

Matrix operator-(Matrix &a, const double &b)
{
    return b-a;
}




Matrix operator-(const Complexo &a, Matrix &b)
{
    Matrix z;
    int NLines=b.lineCount();
    int NCols=b.columnCount();

    z.SetLinesCols(NLines,NCols);

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            z.SetLineColNumber(l,c,a-b.GetLineColNumber(l,c));
        }
    }
    return z;
}

Matrix operator-(Matrix &a, const Complexo &b)
{
    return b-a;
}


Matrix operator-(Matrix &a)
{
    Matrix z;
    int NLines=a.lineCount();
    int NCols=a.columnCount();

    z.SetLinesCols(NLines,NCols);

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            z.SetLineColNumber(l,c,0-a.GetLineColNumber(l,c));
        }
    }

    return z;
}



Matrix operator*( Matrix &a , Matrix &b )
{

    Matrix z;

    Complexo y;
   // Complexo aux1;
  //  Complexo aux2;
    QString mul;

    Complexo multiplication_aux(0,0);
    Calculator calc;

    if (a.columnCount() != b.lineCount())
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("Multiplication error. Matrix dimensions don't match."));
        z.ERRO=true;
        return z;
    }

    int aL=a.lineCount();
    int aC=a.columnCount();
    int bC=b.columnCount();
    z.SetLinesCols(aL,bC);


    for(int l=0;l<aL;l++)
    {
        for(int c=0;c<bC;c++)
        {
            //y=0;
            //mul.clear();
            multiplication_aux.clear();
            for(int i=0;i<aC;i++)
            {
                //mul+=QString("+(%1)*(%2)").arg(a.GetLineColText(l,i)).arg(b.GetLineColText(i,c));
                Complexo aux = a.GetLineColNumber(l,i) * b.GetLineColNumber(i,c);
                multiplication_aux = multiplication_aux + aux;
            }           
            z.SetLineColNumber(l,c,multiplication_aux);    
        }
    }

    return z;
}


Matrix operator*(const double &a, Matrix &b)
{
    Matrix z;
    int NLines=b.lineCount();
    int NCols=b.columnCount();

    z.SetLinesCols(NLines,NCols);

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            z.SetLineColNumber(l,c,a*b.GetLineColNumber(l,c));
        }
    }

    return z;
}

Matrix operator*(Matrix &a, const double &b)
{
    return b*a;
}

Matrix operator*(const Complexo &a, Matrix &b)
{
    Matrix z;
    int NLines=b.lineCount();
    int NCols=b.columnCount();

    z.SetLinesCols(NLines,NCols);

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            z.SetLineColNumber(l,c,a*b.GetLineColNumber(l,c));
        }
    }
    return z;
}

Matrix operator*(Matrix &a, const Complexo &b)
{
    return b*a;
}

//needs to be developed
Matrix operator/( Matrix &a, Matrix &b)
{
    /*
    Matrix z;
    int NLines=a.lineCount();
    int NCols=a.columnCount();

    z.SetLinesCols(NLines,NCols);

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            z.SetLineColNumber(l,c,a.GetLineColNumber(l,c)/b.GetLineColNumber(l,c));
        }
    }

    return z;*/
    return Matrix();
}

////////////////////////////////////////////////////////////////////////////////////////////


Matrix operator/(Matrix &a, const double &b)
{
    Matrix z;
    int NLines=a.lineCount();
    int NCols=a.columnCount();

    z.SetLinesCols(NLines,NCols);

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            z.SetLineColNumber(l,c,a.GetLineColNumber(l,c)/b);
        }
    }

    return z;
}

Matrix operator/(Matrix &a, const Complexo &b)
{
    Matrix z;
    int NLines=a.lineCount();
    int NCols=a.columnCount();

    z.SetLinesCols(NLines,NCols);

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            z.SetLineColNumber(l,c,a.GetLineColNumber(l,c)/b);
        }
    }
    return z;
}


Matrix operator/(const Complexo &a, Matrix &b)
{
    Matrix z;
    int NLines=b.lineCount();
    int NCols=b.columnCount();

    z.SetLinesCols(NLines,NCols);

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            z.SetLineColNumber(l,c,a/b.GetLineColNumber(l,c));
        }
    }
    return z;
}

///////////////////////////////////////////////////////////////

Matrix operator^( Matrix &a, Matrix &b)
{
    /*Matrix z;
    int NLines=a.lineCount();
    int NCols=a.columnCount();

    z.SetLinesCols(NLines,NCols);

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            z.SetLineColNumber(l,c,a.GetLineColNumber(l,c)^b.GetLineColNumber(l,c));
        }
    }
    return z;*/
    return Matrix();
}

Matrix operator^( Matrix &a, const int &b)
{


    if ( b == -1)
    {
        Matrix z = a;
        return z.inverse();
    }

    if (b == 0)
    {
        Matrix z = a;
        z.SetMatrixDiagonal(a.lineCount(), a.columnCount());
        return z;
    }

    Matrix z = a;
    if ( b > 0)
    {
        for (int i = 0; i < b-1; i++)
            z = z * a;

        return z;
    }
    else
    {
        for (int i = 0; i > b+1; i--)
            z = z * a;

        return z.inverse();
    }



    /*Matrix z;
    int NLines=a.lineCount();
    int NCols=a.columnCount();

    z.SetLinesCols(NLines,NCols);

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            z.SetLineColNumber(l,c,a.GetLineColNumber(l,c)^b);
        }
    }
    return z;*/

}

Matrix operator^( Matrix &a, const Complexo &b)
{

    return a^int(b.r);

    /*
    Matrix z;
    int NLines=a.lineCount();
    int NCols=a.columnCount();

    z.SetLinesCols(NLines,NCols);

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            z.SetLineColNumber(l,c,a.GetLineColNumber(l,c)^b);
        }
    }
    return z;
*/

}


Matrix operator^( const Complexo &a, Matrix &b)
{

    Matrix z;
    int NLines=b.lineCount();
    int NCols=b.columnCount();

    z.SetLinesCols(NLines,NCols);

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            z.SetLineColNumber(l,c,a^b.GetLineColNumber(l,c));
        }
    }
    return z;

}


//////////////////////////////////////////////////////////////////////////////////////////////

Matrix Matrix::transpose()
{
    Matrix mat_transpose;

    mat_transpose.SetLinesCols(this->NCol,this->NLine);

    for(int l=0;l<NCol;l++)
    {
        for(int c=0;c<NLine;c++)
        {
            mat_transpose.SetLineColText(l,c,this->GetLineColText(c,l));
        }
    }

    return mat_transpose;
}

Matrix Matrix::cofactor()
{
    Matrix mat_cofactor;

    if (this->NCol != this->NLine)
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("Can not calculate matrix of cofactors, matrix is not square"));
        mat_cofactor.ERRO=true;
        return mat_cofactor;
    }

    mat_cofactor.SetLinesCols(this->NLine,this->NCol);

    for(int l=0;l<NLine;l++)
    {
        for(int c=0;c<NCol;c++)
        {
            Matrix aux=*this;
            aux.RemoveLineCol(l,c);
            if ((l+c)%2 == 0)
                mat_cofactor.SetLineColNumber(l,c,aux.Determinant());
            else
                mat_cofactor.SetLineColNumber(l,c,aux.Determinant()*(-1));
        }
    }

    return mat_cofactor;
}

Matrix Matrix::adjugate()
{

    Matrix mat_adjugate;

    if (this->NCol != this->NLine)
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("Can not calculate matrix adjugate, matrix is not square"));
        mat_adjugate.ERRO=true;
        return mat_adjugate;
    }

   mat_adjugate=this->cofactor().transpose();
   return mat_adjugate;
   // Matrix mat_adjugate=mat_cofactor.transpose();
   // return mat_adjugate;

    //return this->cofactor().transpose();
}

Matrix Matrix::inverse()
{
    Matrix adj;
    if (this->NCol != this->NLine)
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("Can not inverte matrix, matrix is not square"));
        adj.ERRO=true;
        return adj;
    }

    adj=this->adjugate();
    Complexo det=this->Determinant();
    if (this->Determinant().i == 0)
    {
        return 1/det.r*adj;
    }
    else
        return 1/det*adj;

}


//////////////////////////////////////////////////////
// show the matrix in a dialog

void Matrix::Show()
{

    Matrix_gui *matrix_show = new Matrix_gui;
    //matrix_show->setMatrix(NLine,NCol,this->matriz);
    matrix_show->mat = *this;

    matrix_show->setMatrixEditable(false);
    matrix_show->setAttribute(Qt::WA_DeleteOnClose,true);
    //if ( matrix_show.exec() == QDialog::Accepted)
    matrix_show->show();
   // {
//        VectorToMatrix(matrix_show->NCol, matrix_show->NLine, matrix_show->matrixList);
    //}

}


void Matrix::setGuiMatrix()
{
    Matrix_gui mat_gui;

    mat_gui.mat = *this;
//    mat_gui.setMatrix(NLine, NCol, matriz);

    mat_gui.exec();
    if (mat_gui.returnValue == 1)
    {
        VectorToMatrix(mat_gui.NCol, mat_gui.NLine, mat_gui.matrixList);
    }

}






/////////////////////////// system of Equations

int Matrix::Solve_System_Equations()
{
    if (Matrix_triangular_inferior()==0)
        return 0; //calculation aborted by the user

    Matrix_triangular_EquationsSolution();
    return 1;
}

Complexo Matrix::Determinant()
{

    if (this->columnCount() != this->lineCount())
    {
        QMessageBox::about(0,QObject::tr("Error"),QObject::tr("Matrix must be square."));
        ERRO=true;
        return Complexo();
    }


    if ( (this->columnCount()==this->lineCount() ) && (this->lineCount() == 2) )
    {
        return GetLineColNumber(0,0)*GetLineColNumber(1,1)
                -GetLineColNumber(0,1)*GetLineColNumber(1,0);
    }

    Complexo det(1,0);

    Matrix *mat= new Matrix;
    *mat = *this;

    mat->Matrix_triangular_inferior();

    for(int i=0;i<this->lineCount();i++)
    {
        det = det*mat->GetLineColNumber(i,i);
    }

    delete mat;
    return det;
}

int Matrix::Matrix_triangular_inferior()
{
    int L=lineCount();
    int C=columnCount();
    Complexo Pivot;
    Complexo zero(0,0);
    Complexo number;

    bAbortSystemEquationCalculation=false;


    for(int k=1;k<L;k++)
    {
        for(int i=k;i<L;i++) // lines
        {
            Pivot = GetLineColNumber(i,k-1) / GetLineColNumber(k-1,k-1);

            // the next block checks if the denominator is zero, wich would result
            // in a infinite Pivot
            // then it swaps the matrix rows until he fins a "good" Pivot
            /////////////////
            Complexo denominator = GetLineColNumber(k-1,k-1);
            if( denominator !=  zero )
                Pivot = GetLineColNumber(i,k-1) / denominator;
            else // if the denominator is zero, will try to find a new pivot
            {               
                int ii=i;
                while((ii+1<=L) && (denominator == 0))
                {
                    denominator = GetLineColNumber(ii,k-1);
                    if (denominator != 0)
                    {
                        SwapLines(i-1,ii);
                        Pivot = GetLineColNumber(i,k-1) / denominator;
                    }
                    ii++;
                }           
            }
            //////////////////////////

            for (int j=k-1;j<C ;j++) //columns
            {
                number=GetLineColNumber(i,j)-Pivot*GetLineColNumber(k-1,j);
                SetLineColNumber(i,j,number);

                QCoreApplication::processEvents ();
                if (bAbortSystemEquationCalculation)
                    return 0;
            }
        }
    }

    return 1;
}

int Matrix::Matrix_triangular_EquationsSolution()
{
    int L = lineCount();
    Complexo zero(0,0);
    Complexo aux;
    X.clear();

    for(int i=0;i<L;i++)
        X.append(zero);

    for(int j=L-1;j>=0;j--)
    {
        if (j==L-1)
        {
            X[j]=GetLineColNumber(j,L)/GetLineColNumber(j,j);
            //X.prepend(GetLineColNumber(j,L)/GetLineColNumber(j,j));
        }
        else
        {
            aux=GetLineColNumber(j,L);
            int k;
            for(k=L-1;k>j;k--)
            {
                aux=aux-GetLineColNumber(j,k)*X[k];
            }
            X[j]=aux/GetLineColNumber(j,k);
            //X.prepend(aux/GetLineColNumber(j,k));
        }
    }

    return 1;
}

/*
void Matrix::setHeaderSize(double size)
{
    this->sizeHeader = size;
}*/

/*
void Matrix::setVisibleButtons(bool bShow)
{
    bShowButtons = bShow;
}*/


Matrix sinc(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {            
            z.SetLineColNumber(l,c,sinc(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}


Matrix cis(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,cis(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}


Matrix sin(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,sin(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix cos(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,cos(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}


Matrix tan(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,tan(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix cot(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,cot(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix sec(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,sec(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix csc(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,csc(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}


Matrix sinh(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,sinh(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix cosh(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,cosh(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}


Matrix tanh(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,tanh(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}


Matrix coth(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,coth(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}


Matrix sech(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,sech(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix csch(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,csch(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}


Matrix asin(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,asin(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix acos(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,acos(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix atan(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,atan(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix acot(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,acot(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}


Matrix asec(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,asec(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix acsc(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,acsc(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}



Matrix asinh(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,asinh(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix acosh(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,acosh(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix atanh(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,atanh(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix acoth(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,acoth(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}


Matrix asech(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,asech(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix acsch(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,acsch(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}



Matrix log(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,log(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}


Matrix ln(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,ln(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix exp(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,exp(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}


Matrix sqrt(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,sqrt(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix cbrt(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,cbrt(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}


Matrix real(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,real(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix imag(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,imag(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}


Matrix arg(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,arg(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix conj(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,conj(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

Matrix abs(Matrix &mat)
{
    Matrix z;
    z.SetLinesCols(mat.lineCount(),mat.columnCount());

    for (int c=0;c<mat.columnCount();c++)
    {
        for (int l=0;l<mat.lineCount();l++)
        {
            z.SetLineColNumber(l,c,cabs(mat.GetLineColNumber(l,c)));
        }
    }

    return z;
}

///////////////////////////////////////////////////////////////


QDataStream & operator<< (QDataStream& stream, Matrix& matrix)
{
    QVector<QString> str;
    str=matrix.MatrixToVector();

    stream<<matrix.lineCount();
    stream<<matrix.columnCount();
    stream<<str;

    return stream;
}

QDataStream & operator>> (QDataStream& stream, Matrix& matrix)
{
    int L;
    int C;
    QVector<QString> str;

    stream>>L;
    stream>>C;
    stream>>str;

    matrix.VectorToMatrix(C,L,str);

    return stream;
}





