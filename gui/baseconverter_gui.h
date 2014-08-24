#ifndef BASECONVERTER_GUI_H
#define BASECONVERTER_GUI_H

#include <QWidget>

namespace Ui {
class baseConverter_gui;
}

class baseConverter_gui : public QWidget
{
    Q_OBJECT

public:
    explicit baseConverter_gui(QWidget *parent = 0);
    ~baseConverter_gui();

private slots:
    void on_pushButton_ok_clicked();

    void on_lineEdit_decimal_textChanged(const QString &arg1);

    void on_lineEdit_binary_textChanged(const QString &arg1);

    void on_lineEdit_hexadecimal_textChanged(const QString &arg1);

    void on_lineEdit_octal_textChanged(const QString &arg1);

    void on_pushButton_decimal_clicked();

    void on_pushButton_binary_clicked();

    void on_pushButton_hexadecimal_clicked();

    void on_pushButton_octal_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::baseConverter_gui *ui;
};

#endif // BASECONVERTER_GUI_H
