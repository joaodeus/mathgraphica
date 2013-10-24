#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "calculator/calculator.h"
#include "graph2D/graph2d_container_gui.h"
#include "gui/functions_gui.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
protected:
    bool eventFilter(QObject *target, QEvent *event);


private slots:
    void on_lineEdit_cmdLine_returnPressed();

    void on_listWidget_results_history_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_results_history_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_pushButtonOk_clicked();

    void on_actionCalculator_triggered();

    void on_actionEquation_triggered();

    void on_actionSystem_of_equations_triggered();

    void on_actionIntegral_triggered();

    void on_actionIntegral_double_triggered();

    void on_actionMatrix_triggered();

    void on_actionFormulas_triggered();

    void on_actionGraph_2D_triggered();

    void on_actionGraph_3D_triggered();

    void on_actionFunctions_triggered();

private:
    Ui::MainWindow *ui;

    //---calculator----------------------
    Calculator calc;
    QString defaultCalulatorGuiExpression;

    //---list with the results history in the mainwindow
    QStringList results_history;

    //---Matrix for the System of Equations
    Matrix systemEquationMatrix;

    //---Matrices for Matrix gui
    Matrix mat1;
    Matrix mat2;
    Matrix mat3;
    Matrix mat_copy_paste;

   // Graph2D_Container_gui g1;
   // Graph2D_Container_gui g2;


    Functions_gui *m_functions_gui;


};

#endif // MAINWINDOW_H
