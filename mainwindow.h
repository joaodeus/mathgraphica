#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calculator/calculator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_lineEdit_cmdLine_returnPressed();

    void on_actionCalculator_triggered();

    void on_actionGraph_3D_triggered();
    


private:
    Ui::MainWindow *ui;

    //---calculator----------------------
    Calculator calc;

    //---list with the results history in the mainwindow
    QStringList results_history;


};

#endif // MAINWINDOW_H
