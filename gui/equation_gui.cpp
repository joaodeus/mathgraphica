#include "equation_gui.h"
#include "ui_equation_gui.h"

#include "gui/calculator_gui.h"

Equation_gui::Equation_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Equation_gui)
{
    ui->setupUi(this);
}

Equation_gui::~Equation_gui()
{
    delete ui;
}



QString Equation_gui::GetLineEdit_fx()
{
    return ui->lineEdit_fx->text();
}

QString Equation_gui::GetLineEdit_gx()
{
    return ui->lineEdit_gx->text();
}

QString Equation_gui::GetLineEdit_min()
{
    return ui->lineEdit_min->text();
}

QString Equation_gui::GetLineEdit_max()
{
    return ui->lineEdit_max->text();
}

QString Equation_gui::GetLineEdit_delta()
{
    return ui->lineEdit_delta->text();
}

QString Equation_gui::GetLineEdit_precision()
{
    return ui->lineEdit_precision->text();
}

////////////////////////


void Equation_gui::SetLineEdit_fx(const QString &str)
{
    ui->lineEdit_fx->setText(str);
}

void Equation_gui::SetLineEdit_gx(const QString &str)
{
    ui->lineEdit_gx->setText(str);
}

void Equation_gui::SetLineEdit_min(const QString &str)
{
    ui->lineEdit_min->setText(str);
}

void Equation_gui::SetLineEdit_max(const QString &str)
{
    ui->lineEdit_max->setText(str);
}

void Equation_gui::SetLineEdit_delta(const QString &str)
{
    ui->lineEdit_delta->setText(str);
}

void Equation_gui::SetLineEdit_precision(const QString &str)
{
    ui->lineEdit_precision->setText(str);
}

void Equation_gui::on_pushButton_fx_clicked()
{
    Calculator_gui calc;
    calc.SetLineEditCalcExpression(ui->lineEdit_fx->text());

    if (calc.exec() == QDialog::Accepted)
    {
        ui->lineEdit_fx->setText(calc.GetLineEditCalcExpression());
    }
}

void Equation_gui::on_pushButton_gx_clicked()
{
    Calculator_gui calc;
    calc.SetLineEditCalcExpression(ui->lineEdit_gx->text());

    if (calc.exec() == QDialog::Accepted)
    {
        ui->lineEdit_gx->setText(calc.GetLineEditCalcExpression());
    }
}
