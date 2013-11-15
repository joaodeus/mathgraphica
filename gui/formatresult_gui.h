#ifndef FORMATRESULT_GUI_H
#define FORMATRESULT_GUI_H

#include <QDialog>
#include "calculator/formatresult.h"

namespace Ui {
class FormatResult_gui;
}

class FormatResult_gui : public QDialog
{
    Q_OBJECT

public:
    explicit FormatResult_gui(QWidget *parent = 0);
    ~FormatResult_gui();

    FormatResult m_format;

    void showEvent(QShowEvent *event);
private slots:
    void on_checkBox_automatic_clicked(bool checked);

    void on_spinBox_decimalDigits_valueChanged(int arg1);

    void on_checkBox_groupDigits_clicked(bool checked);

    void on_radioButton_automatic_clicked(bool checked);

    void on_radioButton_scientific_clicked(bool checked);

    void on_radioButton_fixedDecimal_clicked(bool checked);

private:
    Ui::FormatResult_gui *ui;
};

#endif // FORMATRESULT_GUI_H
