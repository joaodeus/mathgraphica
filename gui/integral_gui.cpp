#include "integral_gui.h"
#include "ui_integral_gui.h"

Integral_gui::Integral_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Integral_gui)
{
    ui->setupUi(this);
}

Integral_gui::~Integral_gui()
{
    delete ui;
}

void Integral_gui::on_pushButton_fx_clicked()
{

}

QString Integral_gui::GetLowerLimit()
{
    return ui->lineEdit_xmin->text();
}

QString Integral_gui::GetUpperLimit()
{
    return ui->lineEdit_xmax->text();
}

QString Integral_gui::GetIntegralExpression()
{
    return ui->lineEdit_fx->text();
}

QString Integral_gui::GetNumberOfIntervals()
{
    return ui->lineEdit_m_factor->text();
}

/*
QString Integral_gui::GetVariable()
{
    return ui->lineEdit_dx->text();
}*/



void Integral_gui::SetLowerLimit(const QString &str)
{
    ui->lineEdit_xmin->setText(str);
}

void Integral_gui::SetUpperLimit(const QString &str)
{
    ui->lineEdit_xmax->setText(str);
}

void Integral_gui::SetIntegralExpression(const QString &str)
{
    ui->lineEdit_fx->setText(str);
}

void Integral_gui::SetNumberOfIntervals(const QString &str)
{
    ui->lineEdit_m_factor->setText(str);
}

/*
void Integral_gui::SetVariable(const QString &str)
{
    ui->lineEdit_dx->setText(str);
}*/
