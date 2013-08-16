#ifndef EQUATION_GUI_H
#define EQUATION_GUI_H

#include <QDialog>

namespace Ui {
class Equation_gui;
}

class Equation_gui : public QDialog
{
    Q_OBJECT
    
public:
    explicit Equation_gui(QWidget *parent = 0);
    ~Equation_gui();


    QString GetLineEdit_fx();
    QString GetLineEdit_gx();
    QString GetLineEdit_min();
    QString GetLineEdit_max();
    QString GetLineEdit_delta();
    QString GetLineEdit_precision();

    void SetLineEdit_fx(const QString &str);
    void SetLineEdit_gx(const QString &str);
    void SetLineEdit_min(const QString &str);
    void SetLineEdit_max(const QString &str);
    void SetLineEdit_delta(const QString &str);
    void SetLineEdit_precision(const QString &str);

    
private slots:
    void on_pushButton_fx_clicked();

    void on_pushButton_gx_clicked();

private:
    Ui::Equation_gui *ui;
};

#endif // EQUATION_GUI_H
