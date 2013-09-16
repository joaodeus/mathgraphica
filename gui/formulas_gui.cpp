#include "formulas_gui.h"
#include "ui_formulas_gui.h"

Formulas_gui::Formulas_gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formulas_gui)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose,true);
   // setWindowFlags(Qt::WindowSystemMenuHint); /*Qt::WindowMinMaxButtonsHint | */
}

Formulas_gui::~Formulas_gui()
{
    delete ui;
}
