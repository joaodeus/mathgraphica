#ifndef INTEGRAL_GUI_H
#define INTEGRAL_GUI_H

#include <QDialog>

namespace Ui {
class Integral_gui;
}

class Integral_gui : public QDialog
{
    Q_OBJECT
    
public:
    explicit Integral_gui(QWidget *parent = 0);
    ~Integral_gui();

    QString GetLowerLimit();
    QString GetUpperLimit();
    QString GetIntegralExpression();
    QString GetNumberOfIntervals();
    //QString GetVariable();

    void SetLowerLimit(const QString &str);
    void SetUpperLimit(const QString &str);
    void SetIntegralExpression(const QString &str);
    void SetNumberOfIntervals(const QString &str);
    //void SetVariable(const QString &str);
    
private slots:
    void on_pushButton_fx_clicked();

private:
    Ui::Integral_gui *ui;
};

#endif // INTEGRAL_GUI_H
