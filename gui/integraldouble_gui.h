#ifndef INTEGRALDOUBLE_GUI_H
#define INTEGRALDOUBLE_GUI_H

#include <QDialog>

namespace Ui {
class IntegralDouble_gui;
}

class IntegralDouble_gui : public QDialog
{
    Q_OBJECT
    
public:
    explicit IntegralDouble_gui(QWidget *parent = 0);
    ~IntegralDouble_gui();
    
private:
    Ui::IntegralDouble_gui *ui;
};

#endif // INTEGRALDOUBLE_GUI_H
