#ifndef FORMULAS_GUI_H
#define FORMULAS_GUI_H

#include <QWidget>

namespace Ui {
class Formulas_gui;
}

class Formulas_gui : public QWidget
{
    Q_OBJECT

public:
    explicit Formulas_gui(QWidget *parent = 0);
    ~Formulas_gui();

private:
    Ui::Formulas_gui *ui;
};

#endif // FORMULAS_GUI_H
