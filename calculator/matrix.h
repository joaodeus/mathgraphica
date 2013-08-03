#ifndef MATRIX_H
#define MATRIX_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QCoreApplication>
#include "complexo.h"


class Matrix
{
public:
    Matrix();
    ~Matrix();

    int lineCount() const{return NLine;}
    int columnCount() const{return NCol;}

    void AddLines(int n_lines);
    void SetLinesCols(int,int);//defines the size of the matrix lines*columns
    void SetLineColText(int L,int C,QString text);//set text in the position c*l
    void SetLineColNumber(int,int,Complexo);//set number in the position c*l
    //override all elements of line nLine with lineElements, return true if suceed otherwise return false
    bool SetLineElements(QStringList &lineElements, int &nLine);

    void clear(); //set the matrix to null, i.e. 0 cols and rows


    //set an array from min to max with increments of step
    int setArray(const double &min, const double &max, const double &step);
    //set an array with (max-min+1) elements with increments of one unit
    int setArray(const double &min, const double &max);
    //set an array with count elements
    void setArrayElements(const Complexo &element, const unsigned int &count);


    void SetMatrixOnes(int lines, int cols);
    void SetMatrixZeros(int lines, int cols);
    void SetMatrixRandom(int lines, int cols);
    void SetMatrixDiagonal(int lines, int cols);

    Matrix transpose();
    Matrix cofactor();
    Matrix adjugate();
    Matrix inverse();
    void random();
    Complexo Determinant();

    void VectorToMatrix(int col, int line,QVector<QString> &vect);
    void MatrixToVector(QVector<QString> &vect);
    QVector<QString> MatrixToVector();

    QString GetLineColText(int L,int C);//return the text at line L and column C, position C*L
    Complexo GetLineColNumber(int L,int C);//return the number at line L and column C, position C*L

    int RemoveLineCol(int L,int C);
    int RemoveCol(int C);
    int RemoveLine(int L);
    int SwapLines(int L1, int L2);    
    int searchInLines(QString word, int column);

    bool ERRO;
    bool bAbortSystemEquationCalculation;
    bool isCalculating;

    bool bShowButtons;
    void setVisibleButtons(bool bShow);
  //  double sizeHeader; // header size for matrix show
  //  void setHeaderSize(double size);


    ////////////////////
    // operator's
    Matrix &operator=(const Matrix &a);  // Right side is the argument.
    friend Matrix operator*( Matrix &a, Matrix &b);
    friend Matrix operator*( const double &a, Matrix &b);
    friend Matrix operator*( Matrix &a, const double &b);
    friend Matrix operator*( const Complexo &a, Matrix &b);
    friend Matrix operator*( Matrix &a, const Complexo &b);


    friend Matrix operator+( Matrix &a,  Matrix &b);
    friend Matrix operator+( const double &a, Matrix &b);
    friend Matrix operator+( Matrix &a, const double &b);
    friend Matrix operator+( const Complexo &a, Matrix &b);
    friend Matrix operator+( Matrix &a, const Complexo &b);

    friend Matrix operator-( Matrix &a, Matrix &b);
    friend Matrix operator-( const double &a, Matrix &b);
    friend Matrix operator-( Matrix &a, const double &b);
    friend Matrix operator-( const Complexo &a, Matrix &b);
    friend Matrix operator-( Matrix &a, const Complexo &b);

    friend Matrix operator/( Matrix &a, Matrix &b);
    friend Matrix operator/( Matrix &a, const double &b);
    friend Matrix operator/( Matrix &a, const Complexo &b);

    friend Matrix operator^( Matrix &a, Matrix &b);
    friend Matrix operator^( Matrix &a, const double &b);
    friend Matrix operator^( Matrix &a, const Complexo &b);

    //
    //void soma(Matrix &a, Matrix &b);

    ///////////////////////////
    // show matrix in a dialog 

    void Show();

    ///////////////
    // system of Equations
    int Solve_System_Equations();
    int Matrix_triangular_inferior();
    int Matrix_triangular_EquationsSolution();


    QVector<Complexo> X;//array that saves the solution of the equation system

protected:
    //QStringList matriz; //save the matrix elements
    QVector<QString> matriz; //save the matrix elements
    QVector<Complexo> matrixComplexElements;//convenience storage, should contain the same elements as "matriz"
    //however should be used in calculations (sum, multiplication, system equation solving, ...)
    //for the sake of performance
    int NLine;//matrix number os lines
    int NCol;//matrix munber of columns
   // FormatResult format;

};


//////////////////////////////////////////////////////////
//Matrix functions

Matrix sinc(Matrix &mat);
Matrix sin(Matrix &mat);
Matrix cos(Matrix &mat);
Matrix tan(Matrix &mat);
Matrix cot(Matrix &mat);
Matrix sec(Matrix &mat);
Matrix csc(Matrix &mat);
Matrix sinh(Matrix &mat);
Matrix cosh(Matrix &mat);
Matrix tanh(Matrix &mat);
Matrix coth(Matrix &mat);
Matrix sech(Matrix &mat);
Matrix csch(Matrix &mat);
Matrix asin(Matrix &mat);
Matrix acos(Matrix &mat);
Matrix atan(Matrix &mat);
Matrix acot(Matrix &mat);
Matrix asec(Matrix &mat);
Matrix acsc(Matrix &mat);
Matrix asinh(Matrix &mat);
Matrix acosh(Matrix &mat);
Matrix atanh(Matrix &mat);
Matrix acoth(Matrix &mat);
Matrix asech(Matrix &mat);
Matrix acsch(Matrix &mat);

Matrix log(Matrix &mat);
Matrix ln(Matrix &mat);
Matrix exp(Matrix &mat);

Matrix sqrt(Matrix &mat);
Matrix cbrt(Matrix &mat);

Matrix real(Matrix &mat);
Matrix imag(Matrix &mat);

Matrix arg(Matrix &mat);
Matrix conj(Matrix &mat);
Matrix abs(Matrix &mat);


QDataStream & operator<< (QDataStream& stream, Matrix& matrix);
QDataStream & operator>> (QDataStream& stream, Matrix& matrix);


#endif // MATRIX_H
