#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_cmdLine->installEventFilter(this);
    ui->listWidget_results_history->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_cmdLine_returnPressed()
{
    QString str_cmd_line = ui->lineEdit_cmdLine->text();

    MyNumber number;
    bool ok = false;

    number = calc.isValidExpression(str_cmd_line, ok);
    //if ( calc.isValidExpression(str_cmd_line) )
    if (ok)
    {
        //QString solution = calc.formatResult(calc.SolveExpression(str_cmd_line));
        QString solution = calc.formatResult(number);
        QListWidgetItem *item   = new QListWidgetItem(str_cmd_line,0,1);
        QListWidgetItem *item1  = new QListWidgetItem(solution,0,1);
        ui->listWidget_results_history->addItem(item);
        ui->listWidget_results_history->addItem(item1);
        ui->listWidget_results_history->scrollToBottom();
    }


}

void MainWindow::on_pushButtonOk_clicked()
{
    on_lineEdit_cmdLine_returnPressed();
}


bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (  event->type() == QEvent::KeyPress)
    {

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        //qDebug("Ate key press %d - %x", keyEvent->key(), keyEvent->key());
        if ((keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_Down)
              && ui->lineEdit_cmdLine->hasFocus())
        {
            ui->listWidget_results_history->setFocus();
            ui->listWidget_results_history->setCurrentRow(ui->listWidget_results_history->count()-1);
        }

        /*Note: 16777220 is the second Enter key from the keyboard*/
        if ((keyEvent->key() == 16777220 || keyEvent->key() == Qt::Key_Enter)
                && ui->listWidget_results_history->hasFocus())
        {
            ui->lineEdit_cmdLine->setFocus();
        }
    }
    // standard event processing
    return QObject::eventFilter(target, event);
}

void MainWindow::on_actionCalculator_triggered()
{

}

void MainWindow::on_actionGraph_3D_triggered()
{
    
}



void MainWindow::on_listWidget_results_history_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->lineEdit_cmdLine->setText(current->text());
}

