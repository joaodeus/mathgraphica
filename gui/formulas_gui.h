#ifndef FORMULAS_GUI_H
#define FORMULAS_GUI_H

#include <QWidget>
#include "calculator/calculator.h"
#include "calculator/formulas.h"

namespace Ui {
class Formulas_gui;
}

class Formulas_gui : public QWidget
{
    Q_OBJECT

public:
    explicit Formulas_gui(QWidget *parent = 0, Calculator *calculator_ = 0);
    ~Formulas_gui();

private slots:
    void on_pushButton_new_clicked();

    void on_pushButton_del_clicked();    

    void on_pushButton_validate_clicked();

    void on_pushButton_solve_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_tableWidget_formulas_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::Formulas_gui *ui;
    Calculator *m_calculator;

    uint currentFormulaIndex;
    QList<Formulas> formulas_list;

protected:
    void showEvent(QShowEvent * event);

};

#endif // FORMULAS_GUI_H
