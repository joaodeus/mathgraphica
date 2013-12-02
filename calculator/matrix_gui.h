#ifndef MATRIX_SHOW_DLG_H
#define MATRIX_SHOW_DLG_H

#include <QDialog>
#include <QHeaderView>

#include "matrix.h"

namespace Ui {
class Matrix_gui;
}

class Matrix_gui : public QDialog
{
    Q_OBJECT
    
public:
    explicit Matrix_gui(QWidget *parent = 0);
    ~Matrix_gui();
    
    int NLine;
    int NCol;
    //QStringList matrixList;
    Matrix *mat_copy_paste;
    Matrix mat;
    QVector<QString> matrixList;
    int returnValue;


    void setMatrix(const Matrix &mat_);
    void setMatrixCopyPaste(Matrix &matCopyPaste_);
    //void setMatrix(const int &row, const int &column, const QVector<QString> &matrixList_);

    void setHeaderInteractive();
    void setHeaderResize();

    //if true, only displays matrix, if false also allows editing
    void setMatrixEditable(const bool &bDisplayMatrix);
    bool isMatrixEditable(){return bMatrixEditable;}
    bool bMatrixEditable;

protected:
    void showEvent(QShowEvent *event);

    void closeEvent(QCloseEvent *event);

    void hideEvent(QHideEvent *event);



private slots:
    void on_spinBox_rows_valueChanged(int arg1);

    void on_spinBox_columns_valueChanged(int arg1);

    void on_pushButton_random_clicked();

    void on_pushButton_zeros_clicked();

    void on_pushButton_ones_clicked();

    void on_pushButton_diagonal_clicked();

    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_more_options_clicked();

    // context menu
    void matrixRandom();
    void matrixZeros();
    void matrixOnes();
    void matrixDiagonal();
    void matrixInverse();
    void matrixTranspose();
    void matrixDeterminant();
    void matrixCopy();
    void matrixPaste();
    void on_tableWidget_matrix_customContextMenuRequested(const QPoint &pos);

private:
    Ui::Matrix_gui *ui;

    QHeaderView *headerH;
    QHeaderView *headerV;


    QAction *matrixRandomAct;
    QAction *matrixZerosAct;
    QAction *matrixOnesAct;
    QAction *matrixDiagonalAct;
    QAction *matrixInverseAct;
    QAction *matrixTransposeAct;
    QAction *matrixDeterminantAct;
    QAction *matrixCopyAct;
    QAction *matrixPasteAct;
    QAction *matrixShowAct;//for debugging porpuse

    void createActions();
};

#endif // MATRIX_SHOW_DLG_H
