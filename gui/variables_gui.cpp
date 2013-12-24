#include "variables_gui.h"
#include "ui_variables_gui.h"

Variables_gui::Variables_gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Variables_gui)
{
    ui->setupUi(this);

    valueReturn = -1;
}

Variables_gui::~Variables_gui()
{
    delete ui;
}


void Variables_gui::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

}


void Variables_gui::on_pushButton_new_clicked()
{

}

void Variables_gui::on_pushButton_delete_clicked()
{

}

void Variables_gui::on_pushButton_cancel_clicked()
{
    valueReturn = 0;
    close();
}

void Variables_gui::on_pushButton_ok_clicked()
{
    valueReturn = 1;
    close();
}
