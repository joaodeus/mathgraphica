#include "variables_gui.h"
#include "ui_variables_gui.h"
#include "globalfunctions.h"
#include "calculator/calculator.h"

#include <QMessageBox>

Variables_gui::Variables_gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Variables_gui)
{
    ui->setupUi(this);

    valueReturn         = -1;
    m_variables_ListPtr   = NULL;
    m_values_ListPtr      = NULL;

}

Variables_gui::~Variables_gui()
{
    delete ui;
}


void Variables_gui::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    updateVariables();

}

void Variables_gui::updateVariables()
{
    if (m_variables_ListPtr == NULL)
        return;

    if (m_values_ListPtr == NULL)
        return;



    Calculator calc;
    QStringList m_variables_List;
    for (int i = 0; i < m_variables_ListPtr->size(); i++)
    {
        QString aux;
        aux = m_variables_ListPtr->at(i) + "=" +calc.formatResult( m_values_ListPtr->at(i) );
        m_variables_List.append(aux);
    }

    QStringListToTableWidget(m_variables_List, *ui->tableWidget);

}


void Variables_gui::on_pushButton_new_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
}

void Variables_gui::on_pushButton_delete_clicked()
{

    int index = ui->tableWidget->currentRow();

    //if (index < 0 || index >= m_functions_List.size())
      //  return;

    if (index < 0 || index >= m_variables_ListPtr->size())
        return;


    QString aux = tr("Delete variable ?\n") + ui->tableWidget->item(index,0)->text();
    int r = QMessageBox::warning(this, tr("Delete variable"), aux, QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (r == QMessageBox::Yes)
    {
        m_variables_ListPtr->removeAt(index);
        m_values_ListPtr->removeAt(index);
        updateVariables();
    }

}

void Variables_gui::on_pushButton_cancel_clicked()
{
    valueReturn = 0;
    close();
}

void Variables_gui::on_pushButton_ok_clicked()
{

    if (m_variables_ListPtr == NULL)
        return;

    if (m_values_ListPtr == NULL)
        return;



    //-- to refactor, check wich functions have been changed and only update those
    // for now wI'm felling lazy and will just delete all and then copy all from tablewidget

    m_variables_ListPtr->clear();
    m_values_ListPtr->clear();

    //m_functions_List.clear();

    Calculator calc;

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        if (ui->tableWidget->item(i,0) != 0)
        {
            QString aux = ui->tableWidget->item(i,0)->text();
            QString variable;
            MyNumber number;
            if (calc.isValidEquation_Explicit_From_Constant(aux, variable, number) )
            {
                calc.setVariable_Value(variable, number);
            }

        }
    }


    for (int i=0;i < calc.variables_List.size();i++)
    {
        m_variables_ListPtr->append(calc.variables_List.at(i));
        m_values_ListPtr->append(calc.values_List.at(i));
    }



/*if (calc.isValidEquation_Explicit_From_Constant(str_cmd_line_aux, variable, number))
    {
        calc.setVariable_Value(variable, number);
        QListWidgetItem *item = new QListWidgetItem(str_cmd_line_aux,0,TYPE_EQUATION_ASSIGNMENT);
        ui->listWidget_results_history->addItem(item);
        ui->listWidget_results_history->scrollToBottom();
        return;
    }
*/

    valueReturn = 1;
    close();
}
