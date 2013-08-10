#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
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
    
protected:
    bool eventFilter(QObject *target, QEvent *event);


private slots:
    void on_lineEdit_cmdLine_returnPressed();

    void on_pushButtonOk_clicked();

    void on_actionCalculator_triggered();

    void on_actionGraph_3D_triggered();

    void on_listWidget_results_history_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_actionEquation_triggered();

    void on_listWidget_results_history_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;

    //---calculator----------------------
    Calculator calc;
    QString defaultCalulatorGuiExpression;

    //---list with the results history in the mainwindow
    QStringList results_history;


};

#endif // MAINWINDOW_H
