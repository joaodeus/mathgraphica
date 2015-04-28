#include "formulas_gui.h"
#include "ui_formulas_gui.h"
#include "calculator/formulas.h"
#include <QMessageBox>

Formulas_gui::Formulas_gui(QWidget *parent, Calculator *calculator_) :
    QWidget(parent),
    ui(new Ui::Formulas_gui)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose,true);
   // setWindowFlags(Qt::WindowSystemMenuHint); /*Qt::WindowMinMaxButtonsHint | */

    currentFormulaIndex = 0;
    m_calculator = calculator_;


}

Formulas_gui::~Formulas_gui()
{
    delete ui;
}

void Formulas_gui::on_pushButton_new_clicked()
{

    int count = ui->tableWidget_formulas->rowCount();
    ui->tableWidget_formulas->setRowCount(count+1);
    m_calculator->addFormula();

    if (ui->tableWidget_formulas->item(count, 0) == 0)
    {
        QTableWidgetItem *newFormula = new QTableWidgetItem("");
        ui->tableWidget_formulas->setItem(count, 0, newFormula);
    }

    if (ui->tableWidget_formulas->item(count, 1) == 0)
    {
        QTableWidgetItem *newDescription = new QTableWidgetItem("");
        ui->tableWidget_formulas->setItem(count, 1, newDescription);
    }

}

void Formulas_gui::on_pushButton_del_clicked()
{
    int index = ui->tableWidget_formulas->currentRow();
 //   index = ui->tableWidget_formulas->currentItem()->row();
    if ( (index < 0) && (index >= ui->tableWidget_formulas->rowCount()) )
        return;

    QString aux = tr("Delete formula ?\n") + ui->tableWidget_formulas->item(index,0)->text();
    int r = QMessageBox::warning(this, tr("Delete Formula"), aux, QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (r == QMessageBox::Yes)
    {
        m_calculator->removeFormula(index);
        ui->tableWidget_formulas->removeRow(index);
    }

}

void Formulas_gui::on_pushButton_validate_clicked()
{

    m_calculator->m_formulasList[currentFormulaIndex].setFormula(ui->tableWidget_formulas->item(currentFormulaIndex,0)->text());
    //set description
    m_calculator->m_formulasList[currentFormulaIndex].setDescription(ui->tableWidget_formulas->item(currentFormulaIndex,1)->text());
    m_calculator->m_formulasList[currentFormulaIndex].calculateConstants();
    int size = m_calculator->m_formulasList.at(currentFormulaIndex).getConstants().size();

    ui->tableWidget_constants->setRowCount(size);

    for (int l = 0; l < size; l++)
    {
        if (ui->tableWidget_constants->item(l,0) == 0)
        {
            QTableWidgetItem *newConstant = new QTableWidgetItem(m_calculator->m_formulasList.at(currentFormulaIndex).getConstants().at(l));
            ui->tableWidget_constants->setItem(l, 0, newConstant);

            QTableWidgetItem *newValue = new QTableWidgetItem(m_calculator->m_formulasList.at(currentFormulaIndex).getValues().at(l));
            ui->tableWidget_constants->setItem(l, 1, newValue);
        }
        else
        {
            ui->tableWidget_constants->item(l, 0)->setText(m_calculator->m_formulasList.at(currentFormulaIndex).getConstants().at(l));
            ui->tableWidget_constants->item(l, 1)->setText(m_calculator->m_formulasList.at(currentFormulaIndex).getValues().at(l));
        }
        ui->tableWidget_constants->item(l,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }

}

void Formulas_gui::on_pushButton_solve_clicked()
{

    QApplication::setOverrideCursor(Qt::WaitCursor);
    m_calculator->m_formulasList[currentFormulaIndex].setMin(ui->lineEdit_min->text());
    m_calculator->m_formulasList[currentFormulaIndex].setMax(ui->lineEdit_max->text());
    m_calculator->m_formulasList[currentFormulaIndex].setDelta(ui->lineEdit_delta->text());
    m_calculator->m_formulasList[currentFormulaIndex].setPrecision(ui->lineEdit_precision->text());


    QStringList values;
    for (int i = 0; i < ui->tableWidget_constants->rowCount() ; i++)
    {
        values.append( ui->tableWidget_constants->item(i,1)->text() );
    }
    m_calculator->m_formulasList[currentFormulaIndex].setValues(values);
    m_calculator->m_formulasList[currentFormulaIndex].solve();


    ui->listWidget_solutions->clear();
    for (int i=0; i < m_calculator->m_formulasList[currentFormulaIndex].getSolution().size();i++)
    {
        QString solution = m_calculator->formatResult(m_calculator->m_formulasList[currentFormulaIndex].getSolution().at(i));
        ui->listWidget_solutions->addItem(solution);
        ui->listWidget_solutions->item(i)->setFlags(ui->listWidget_solutions->item(i)->flags() | Qt::ItemIsEditable);
    }

    QApplication::restoreOverrideCursor();

}

/*
void Formulas_gui::on_buttonBox_accepted()
{
    close();
}
*/
/*
void Formulas_gui::on_buttonBox_rejected()
{
    close();
}*/

void Formulas_gui::showEvent(QShowEvent * event)
{
    Q_UNUSED(event);

    int size = m_calculator->m_formulasList.size();
    ui->tableWidget_formulas->setRowCount(size);
    for (int i = 0; i < size; i++)
    {
        //Formulas TableWidget
        if (ui->tableWidget_formulas->item(i,0) == 0)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem( m_calculator->m_formulasList.at(i).getFormula() );
            ui->tableWidget_formulas->setItem(i, 0, newItem);
        }
        else
        {
            ui->tableWidget_formulas->item(i,0)->setText( m_calculator->m_formulasList.at(i).getFormula() );
        }

        if (ui->tableWidget_formulas->item(i,1) == 0)
        {
            QTableWidgetItem *newDescription = new QTableWidgetItem( m_calculator->m_formulasList.at(i).getDescription() );
            ui->tableWidget_formulas->setItem(i, 1, newDescription);
        }
        else
        {
            ui->tableWidget_formulas->item(i,1)->setText( m_calculator->m_formulasList.at(i).getDescription() );
        }



        //ui->tableWidget_formulas->setRowCount(m_calculator->m_formulasList.size());
        // Constants TableWidget
        int constants_size = m_calculator->m_formulasList.at(i).getConstants().size();
        ui->tableWidget_constants->setRowCount(constants_size);

        /*
        for (int l = 0; l < constants_size; l++)
        {
            if (ui->tableWidget_constants->item(l,0) == 0)
            {
                QTableWidgetItem *newConstant = new QTableWidgetItem(m_calculator->m_formulasList.at(i).getConstants().at(l));
                ui->tableWidget_constants->setItem(l, 0, newConstant);
            }
            else
            {
                ui->tableWidget_constants->item(l, 0)->setText(m_calculator->m_formulasList.at(i).getConstants().at(l));
            }
        }*/

        currentFormulaIndex = i;
        ui->tableWidget_formulas->setCurrentCell(i,0);

        // Settings
        ui->lineEdit_min->setText(m_calculator->m_formulasList[i].getMin());
        ui->lineEdit_max->setText(m_calculator->m_formulasList[i].getMax());
        ui->lineEdit_delta->setText(m_calculator->m_formulasList[i].getDelta());
        ui->lineEdit_precision->setText(m_calculator->m_formulasList[i].getPrecision());


    }


}

void Formulas_gui::on_tableWidget_formulas_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(currentColumn);
    Q_UNUSED(previousRow);
    Q_UNUSED(previousColumn);
    currentFormulaIndex = currentRow;

    ui->lineEdit_min->setText(m_calculator->m_formulasList[currentFormulaIndex].getMin());
    ui->lineEdit_max->setText(m_calculator->m_formulasList[currentFormulaIndex].getMax());
    ui->lineEdit_delta->setText(m_calculator->m_formulasList[currentFormulaIndex].getDelta());
    ui->lineEdit_precision->setText(m_calculator->m_formulasList[currentFormulaIndex].getPrecision());

   // on_pushButton_validate_clicked();
   // updateTablWidgetConstants();

}

void Formulas_gui::updateTablWidgetConstants()
{
    int size = m_calculator->m_formulasList[currentFormulaIndex].getConstants().size();
    ui->tableWidget_constants->setRowCount(size);

    for (int i = 0; i < size; i++)
    {
        if (ui->tableWidget_constants->item(i, 0) == 0)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem( m_calculator->m_formulasList[currentFormulaIndex].getConstants().at(i) );
            ui->tableWidget_constants->setItem(i, 0, newItem);
        }
        else
        {
            ui->tableWidget_constants->item(i, 0)->setText( m_calculator->m_formulasList[currentFormulaIndex].getConstants().at(i));
        }
    }


}

void Formulas_gui::on_tableWidget_constants_cellDoubleClicked(int row, int column)
{
    if (column == 0)
    {
        ui->tableWidget_constants->item(row,1)->setText("?");
    }
}

void Formulas_gui::on_pushButton_close_clicked()
{
    close();
}
