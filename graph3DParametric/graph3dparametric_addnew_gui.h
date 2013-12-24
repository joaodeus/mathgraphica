#ifndef GRAPH3DPARAMETRIC_ADDNEW_GUI_H
#define GRAPH3DPARAMETRIC_ADDNEW_GUI_H

#include <QDialog>

namespace Ui {
class Graph3DParametric_AddNew_gui;
}

class Graph3DParametric_AddNew_gui : public QDialog
{
    Q_OBJECT

public:
    explicit Graph3DParametric_AddNew_gui(QWidget *parent = 0);
    ~Graph3DParametric_AddNew_gui();

    int returnValue;


private slots:
    void on_pushButton_color_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_ok_clicked();

    void on_pushButton_f1_clicked();

    void on_pushButton_f2_clicked();

    void on_pushButton_f3_clicked();

private:
    Ui::Graph3DParametric_AddNew_gui *ui;
    QString strFromColor(QColor color);
};

#endif // GRAPH3DPARAMETRIC_ADDNEW_GUI_H
