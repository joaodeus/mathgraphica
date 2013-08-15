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

    int isDegreeRadGrad;
public:
    void setDegreeRadGrad(const int &DegreeRadGrad_);
    int getDegreeRadGrad(){return isDegreeRadGrad;}

private slots:
    void setTextfromBtnClicked(const QString &);
    void clicked_del();
    void on_radioButton_grad_clicked();
    void on_radioButton_rad_clicked();
    void on_radioButton_degree_clicked();
};

#endif // CALCULATOR_GUI_H
