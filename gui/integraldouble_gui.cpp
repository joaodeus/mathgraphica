#include "integraldouble_gui.h"
#include "ui_integraldouble_gui.h"

#include "gui/calculator_gui.h"

IntegralDouble_gui::IntegralDouble_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntegralDouble_gui)
{
    ui->setupUi(this);
}

IntegralDouble_gui::~IntegralDouble_gui()
{
    delete ui;
}


void IntegralDouble_gui::setInnerLimits(const QString &innerLowerLimitExpression_, const QString &innerUpperLimitExpression_)
{
    ui->lineEdit_innerLower->setText(innerLowerLimitExpression_);
    ui->lineEdit_innerUpper->setText(innerUpperLimitExpression_);
}

void IntegralDouble_gui::setOuterLimits(const QString &outerLowerLimitExpression_, const QString &outerUpperLimitExpression_)
{
    ui->lineEdit_outerLower->setText(outerLowerLimitExpression_);
    ui->lineEdit_outerUpper->setText(outerUpperLimitExpression_);
}

void IntegralDouble_gui::setNumberOfIntervals(const QString &numberOfIntervals_)
{
    ui->lineEdit_m_factor->setText(numberOfIntervals_);
}

void IntegralDouble_gui::setVaribles(const QString &innerVariable_, const QString &outerVariable_)
{
    ui->lineEdit_variable_Inner->setText(innerVariable_);
    ui->lineEdit_variable_Outer->setText(outerVariable_);
}

void IntegralDouble_gui::setIntegralDoubleExpression(const QString &integralDoubleExpression_)
{
    ui->lineEdit_expression->setText(integralDoubleExpression_);
}


////////////////////////////////////////////////


QString IntegralDouble_gui::getInnerLowerLimit()
{
    return ui->lineEdit_innerLower->text();
}

QString IntegralDouble_gui::getInnerUpperLimit()
{
    return ui->lineEdit_innerUpper->text();
}

QString IntegralDouble_gui::getOuterLowerLimit()
{
    return ui->lineEdit_outerLower->text();
}

QString IntegralDouble_gui::getOuterUpperLimit()
{
    return ui->lineEdit_outerUpper->text();
}

QString IntegralDouble_gui::getNumberOfIntervals()
{
    return ui->lineEdit_m_factor->text();
}

QString IntegralDouble_gui::getInnerVarible()
{
    return ui->lineEdit_variable_Inner->text();
}

QString IntegralDouble_gui::getOuterVarible()
{
    return ui->lineEdit_variable_Outer->text();
}

QString IntegralDouble_gui::getIntegralDoubleExpression()
{
    return ui->lineEdit_expression->text();
}

void IntegralDouble_gui::on_pushButton_fxy_clicked()
{
    Calculator_gui calc;
    calc.SetLineEditCalcExpression(ui->lineEdit_expression->text());

    if (calc.exec() == QDialog::Accepted)
    {
        ui->lineEdit_expression->setText(calc.GetLineEditCalcExpression());
    }
}
