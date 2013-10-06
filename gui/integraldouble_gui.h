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

    /*QString GetLowerLimit();
    QString GetUpperLimit();
    QString GetIntegralExpression();
    QString GetNumberOfIntervals();
    //QString GetVariable();

    void SetLowerLimit(const QString &str);
    void SetUpperLimit(const QString &str);
    void SetIntegralExpression(const QString &str);
    void SetNumberOfIntervals(const QString &str);
    //void SetVariable(const QString &str);
    */

    void setInnerLimits(const QString &innerLowerLimitExpression_, const QString &innerUpperLimitExpression_);
    void setOuterLimits(const QString &outerLowerLimitExpression_, const QString &outerUpperLimitExpression_);
    void setNumberOfIntervals(const QString &numberOfIntervals_);
    void setVaribles(const QString &innerVariable_, const QString &outerVariable_);
    void setIntegralDoubleExpression(const QString &integralDoubleExpression_);

    QString getInnerLowerLimit();
    QString getInnerUpperLimit();
    QString getOuterLowerLimit();
    QString getOuterUpperLimit();
    QString getNumberOfIntervals();
    QString getInnerVarible();
    QString getOuterVarible();
    QString getIntegralDoubleExpression();


private slots:
    void on_pushButton_fxy_clicked();

private:
    Ui::IntegralDouble_gui *ui;
};

#endif // INTEGRALDOUBLE_GUI_H
