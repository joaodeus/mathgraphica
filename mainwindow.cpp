#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_cmdLine_returnPressed()
{
    QString str_cmd_line = ui->lineEdit_cmdLine->text();


    if ( calc.isValidExpression(str_cmd_line) )
    {
        QString solution = calc.formatResult(calc.SolveExpression(str_cmd_line));
        QListWidgetItem *item   = new QListWidgetItem(str_cmd_line,0,1);
        QListWidgetItem *item1  = new QListWidgetItem(solution,0,1);
        ui->listWidget_results_history->addItem(item);
        ui->listWidget_results_history->addItem(item1);
        ui->listWidget_results_history->scrollToBottom();
    }


}

void MainWindow::on_actionCalculator_triggered()
{

}

void MainWindow::on_actionGraph_3D_triggered()
{
    
}


