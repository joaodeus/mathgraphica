#include "integraldouble_gui.h"
#include "ui_integraldouble_gui.h"

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
