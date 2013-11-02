#include "systemeq_gui.h"
#include "ui_systemeq_gui.h"

//#include <QTime>
#include "calculator/calculator.h"
#include "globalfunctions.h"

SystemEq_gui::SystemEq_gui(QWidget *parent) :
  //  QDialog(parent),
      QWidget(parent),
    ui(new Ui::SystemEq_gui)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose,true);
   // setWindowFlags(Qt::WindowSystemMenuHint); /*Qt::WindowMinMaxButtonsHint | */
    /*
        ui->tableWidget_systemEquations->setColumnCount(4);
        ui->tableWidget_systemEquations->setRowCount(3);
        ui->tableWidget_systemEq_result->setColumnCount(1);
        ui->tableWidget_systemEq_result->setRowCount(3);

        ui->spinBox_nEquations->setRange(1,10000);
        ui->spinBox_nEquations->setValue(3);
        on_pushButton_random_clicked();
    */
}

SystemEq_gui::~SystemEq_gui()
{
    delete ui;
}

void SystemEq_gui::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
    if (mat->isCalculating)
    {
        int r = QMessageBox::warning(this, tr("Calculating..."),
                        tr("If this is taking to long try to redude the number of equations.\n"
                           "Do you want to abort calculations?"),
                        QMessageBox::Yes | QMessageBox::No
                        | QMessageBox::Cancel);
        if (r == QMessageBox::Yes)
        {
            mat->isCalculating=false;
            mat->bAbortSystemEquationCalculation=true;
        }
    }
}

void SystemEq_gui::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    GetMatrixToTableWidget(*mat, *ui->tableWidget_systemEquations);
    ui->spinBox_nEquations->setValue(mat->lineCount());
}


void SystemEq_gui::show_SystemEq_result()
{
    ui->tableWidget_systemEq_result->setColumnCount(1);
    ui->tableWidget_systemEq_result->setRowCount(mat->X.size());

    Calculator calc;

    for(int l=0;l<mat->X.size();l++)
    {
        if (ui->tableWidget_systemEq_result->item(l,0) == 0)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem(calc.formatResult(mat->X.at(l)));
            ui->tableWidget_systemEq_result->setItem(l,0,newItem);
        }
        else
        {
            ui->tableWidget_systemEq_result->item(l,0)->setText(calc.formatResult(mat->X.at(l)));
        }
    }
}

void SystemEq_gui::on_spinBox_nEquations_valueChanged(int arg1)
{
    int n_equations=ui->spinBox_nEquations->value();
    ui->tableWidget_systemEquations->setColumnCount(n_equations+1);
    ui->tableWidget_systemEquations->setRowCount(n_equations);
}

void SystemEq_gui::on_pushButton_random_clicked()
{
    for(int l=0;l<ui->tableWidget_systemEquations->rowCount();l++)
    {
        for(int c=0;c<ui->tableWidget_systemEquations->columnCount();c++)
        {
            if (ui->tableWidget_systemEquations->item(l,c) == 0)
            {
                QTableWidgetItem *newItem = new QTableWidgetItem(
                            QString("%1").arg(qrand()%1000));
                ui->tableWidget_systemEquations->setItem(l,c,newItem);
            }
            else
            {
                ui->tableWidget_systemEquations->item(l,c)->setText(QString("%1").arg(qrand()%1000));
            }
        }
    }

}

void SystemEq_gui::on_pushButton_solve_clicked()
{
    mat->isCalculating=true;
    QApplication::setOverrideCursor(Qt::WaitCursor);    
    GetTableWidgetToMatrix(*ui->tableWidget_systemEquations, *mat);
   // QTime stopwatch;
   // stopwatch.start();
    if (mat->Solve_System_Equations()==0)
    {
        QApplication::restoreOverrideCursor();
        mat->isCalculating=false;
        return;
    }
   // qDebug("system equation time elapsed: %d", stopwatch.elapsed());
    show_SystemEq_result();
    QApplication::restoreOverrideCursor();
    mat->isCalculating=false;
}

void SystemEq_gui::on_pushButton_ok_clicked()
{
    GetTableWidgetToMatrix(*ui->tableWidget_systemEquations,*mat);
    close();
}
