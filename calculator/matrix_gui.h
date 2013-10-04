#ifndef MATRIX_SHOW_DLG_H
#define MATRIX_SHOW_DLG_H

#include <QDialog>
#include <QHeaderView>


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
    QVector<QString> matrixList;
    int returnValue;


    void setMatrix(const int &row, const int &column, const QVector<QString> &matrixList_);
    void setHeaderInteractive();
    void setHeaderResize();

    //if true, only displays matrix, if false also allows editing
    void setMatrixDisplayOnly(const bool &bDisplayMatrix);

protected:
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

private:
    Ui::Matrix_gui *ui;

    QHeaderView *headerH;
    QHeaderView *headerV;
};

#endif // MATRIX_SHOW_DLG_H
