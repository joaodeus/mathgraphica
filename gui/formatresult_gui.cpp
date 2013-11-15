#include "formatresult_gui.h"
#include "ui_formatresult_gui.h"

FormatResult_gui::FormatResult_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormatResult_gui)
{
    ui->setupUi(this);
}

FormatResult_gui::~FormatResult_gui()
{
    delete ui;
}

void FormatResult_gui::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    ui->checkBox_automatic->setChecked(m_format.getAutomaticPrecision());
    ui->checkBox_groupDigits->setChecked(m_format.getGroup());

    if (m_format.getFormat() == 'G')
        ui->radioButton_automatic->setChecked(true);
    else if (m_format.getFormat() == 'E')
        ui->radioButton_scientific->setChecked(true);
    else if (m_format.getFormat() == 'f')
        ui->radioButton_fixedDecimal->setChecked(true);

    //E - format as [-]9.9E[+|-]999 - scientific
    //f - format as [-]9.9 - fixed decimal
    //G - use E or f format, whichever is the most concise - automatic

    ui->spinBox_decimalDigits->setValue(m_format.getPrecision());


    ui->spinBox_decimalDigits->setEnabled(!m_format.getAutomaticPrecision());

}

void FormatResult_gui::on_checkBox_automatic_clicked(bool checked)
{
    m_format.setAutomaticPrecision(checked);
    ui->spinBox_decimalDigits->setEnabled(!checked);

}

void FormatResult_gui::on_spinBox_decimalDigits_valueChanged(int arg1)
{
    m_format.setPrecision(arg1);
}

void FormatResult_gui::on_checkBox_groupDigits_clicked(bool checked)
{
    m_format.setGroupDigits(checked);
}

void FormatResult_gui::on_radioButton_automatic_clicked(bool checked)
{
    m_format.setFormat('G');
}

void FormatResult_gui::on_radioButton_scientific_clicked(bool checked)
{
    m_format.setFormat('E');
}

void FormatResult_gui::on_radioButton_fixedDecimal_clicked(bool checked)
{
    m_format.setFormat('f');
}
