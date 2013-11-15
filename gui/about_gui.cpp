#include "about_gui.h"
#include "ui_about_gui.h"

About_gui::About_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About_gui)
{
    ui->setupUi(this);
}

About_gui::~About_gui()
{
    delete ui;
}
