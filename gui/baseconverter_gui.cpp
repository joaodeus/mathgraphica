#include "baseconverter_gui.h"
#include "ui_baseconverter_gui.h"

#include "gui/calculator_gui.h"

baseConverter_gui::baseConverter_gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::baseConverter_gui)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose,true);
}

baseConverter_gui::~baseConverter_gui()
{
    delete ui;
}

void baseConverter_gui::on_pushButton_ok_clicked()
{
    close();
}

void baseConverter_gui::on_lineEdit_decimal_textChanged(const QString &arg1)
{
    bool ok;
    long number=arg1.toLong(&ok,10);

    if (ok)
    {
        ui->lineEdit_binary->setText(QString("%1").arg(number,0,2));
        ui->lineEdit_hexadecimal->setText(QString("%1").arg(number,0,16));
        ui->lineEdit_octal->setText(QString("%1").arg(number,0,8));
    }
    else
    {
        ui->lineEdit_binary->setText("");
        ui->lineEdit_hexadecimal->setText("");
        ui->lineEdit_octal->setText("");
    }
}

void baseConverter_gui::on_lineEdit_binary_textChanged(const QString &arg1)
{
    bool ok;
    long number=arg1.toLong(&ok,2);

    if (ok)
    {
        ui->lineEdit_decimal->setText(QString("%1").arg(number,0,10));
        ui->lineEdit_hexadecimal->setText(QString("%1").arg(number,0,16));
        ui->lineEdit_octal->setText(QString("%1").arg(number,0,8));
    }
    else
    {
        ui->lineEdit_decimal->setText("");
        ui->lineEdit_hexadecimal->setText("");
        ui->lineEdit_octal->setText("");
    }
}

void baseConverter_gui::on_lineEdit_hexadecimal_textChanged(const QString &arg1)
{
    bool ok;
    long number=arg1.toLong(&ok,16);

    if (ok)
    {
        ui->lineEdit_decimal->setText(QString("%1").arg(number,0,10));
        ui->lineEdit_binary->setText(QString("%1").arg(number,0,2));
        ui->lineEdit_octal->setText(QString("%1").arg(number,0,8));
    }
    else
    {
        ui->lineEdit_decimal->setText("");
        ui->lineEdit_binary->setText("");
        ui->lineEdit_octal->setText("");
    }
}

void baseConverter_gui::on_lineEdit_octal_textChanged(const QString &arg1)
{
    bool ok;
    long number=arg1.toLong(&ok,8);

    if (ok)
    {
        ui->lineEdit_decimal->setText(QString("%1").arg(number,0,10));
        ui->lineEdit_binary->setText(QString("%1").arg(number,0,2));
        ui->lineEdit_hexadecimal->setText(QString("%1").arg(number,0,16));
    }
    else
    {
        ui->lineEdit_decimal->setText("");
        ui->lineEdit_binary->setText("");
        ui->lineEdit_octal->setText("");
    }
}

void baseConverter_gui::on_pushButton_decimal_clicked()
{
    Calculator_gui calc;
    calc.SetLineEditCalcExpression(ui->lineEdit_decimal->text());
    if (calc.exec() == QDialog::Accepted)
    {
        ui->lineEdit_decimal->setText(calc.GetLineEditCalcExpression());
    }
}

void baseConverter_gui::on_pushButton_binary_clicked()
{
    Calculator_gui calc;
    calc.SetLineEditCalcExpression(ui->lineEdit_binary->text());
    if (calc.exec() == QDialog::Accepted)
    {
        ui->lineEdit_binary->setText(calc.GetLineEditCalcExpression());
    }
}

void baseConverter_gui::on_pushButton_hexadecimal_clicked()
{
    Calculator_gui calc;
    calc.SetLineEditCalcExpression(ui->lineEdit_hexadecimal->text());
    if (calc.exec() == QDialog::Accepted)
    {
        ui->lineEdit_hexadecimal->setText(calc.GetLineEditCalcExpression());
    }
}

void baseConverter_gui::on_pushButton_octal_clicked()
{
    Calculator_gui calc;
    calc.SetLineEditCalcExpression(ui->lineEdit_octal->text());
    if (calc.exec() == QDialog::Accepted)
    {
        ui->lineEdit_octal->setText(calc.GetLineEditCalcExpression());
    }
}

void baseConverter_gui::on_pushButton_clear_clicked()
{
    ui->lineEdit_decimal->setText("");
    ui->lineEdit_binary->setText("");
    ui->lineEdit_hexadecimal->setText("");
    ui->lineEdit_octal->setText("");
}
