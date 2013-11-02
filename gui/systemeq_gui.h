#ifndef SYSTEMEQ_GUI_H
#define SYSTEMEQ_GUI_H

//#include <QDialog>
#include <QWidget>

#include "calculator/matrix.h"

namespace Ui {
class SystemEq_gui;
}

//class SystemEq_gui : public QDialog
class SystemEq_gui : public QWidget
{
    Q_OBJECT
    
public:
    explicit SystemEq_gui(QWidget *parent = 0);
    ~SystemEq_gui();
    
    Matrix *mat;

protected:
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *event);
    void show_SystemEq_result();

private slots:
    void on_spinBox_nEquations_valueChanged(int arg1);

    void on_pushButton_random_clicked();

    void on_pushButton_solve_clicked();

    void on_pushButton_ok_clicked();

private:
    Ui::SystemEq_gui *ui;
};

#endif // SYSTEMEQ_GUI_H
