#ifndef CALCULATOR_GUI_H
#define CALCULATOR_GUI_H

#include <QDialog>
#include <QSignalMapper>

namespace Ui {
class Calculator_gui;
}

class Calculator_gui : public QDialog
{
    Q_OBJECT
    
public:
    explicit Calculator_gui(QWidget *parent = 0);
    ~Calculator_gui();

    QString GetLineEditCalcExpression();
    void SetLineEditCalcExpression(const QString &expression_);
    
private:
    Ui::Calculator_gui *ui;

    QSignalMapper *mapper;


private slots:
    void setTextfromBtnClicked(const QString &);
    void clicked_del();
};

#endif // CALCULATOR_GUI_H
