#include "functions_gui.h"
#include "ui_functions_gui.h"
#include "globalfunctions.h"


Functions_gui::Functions_gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Functions_gui)
{
    ui->setupUi(this);

    m_functionsListPtr = NULL;
    valueReturn = -1;
}

Functions_gui::~Functions_gui()
{
    m_functionsListPtr = NULL;
    delete ui;
}

void Functions_gui::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    updateFunctions();
}

void Functions_gui::updateFunctions()
{
    if (m_functionsListPtr == NULL)
        return;

    QStringList m_functions_List;
    for (int i = 0; i < m_functionsListPtr->size(); i++)
    {
        m_functions_List.append(m_functionsListPtr->at(i).GetFunctionDefinition());
    }
    QStringListToTableWidget(m_functions_List, *ui->tableWidget);
}

void Functions_gui::on_pushButton_new_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
}

void Functions_gui::on_pushButton_delete_clicked()
{

}

void Functions_gui::on_pushButton_ok_clicked()
{
    //-- to refactor, check wich functions have been changed and only update those
    // for now wI'm felling lazy and will just delete and copy
    m_functionsListPtr->clear();
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QString aux = ui->tableWidget->item(i,0)->text();
        if (m_function->SetFunction(aux)) // only saves valid functions
            m_functionsListPtr->append(*m_function);
    }

    //m_functionsListPtr

    valueReturn = 1;
    close();
}

void Functions_gui::on_pushButton_cancel_clicked()
{
    valueReturn = 0;
    close();
}
