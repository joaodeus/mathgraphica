#ifndef GRAPH3D_ADDNEW_GUI_H
#define GRAPH3D_ADDNEW_GUI_H

#include <QDialog>
#include "graph3d.h"

namespace Ui {
class Graph3D_AddNew_gui;
}

class Graph3D_AddNew_gui : public QDialog
{
    Q_OBJECT

public:
    explicit Graph3D_AddNew_gui(QWidget *parent = 0);
    ~Graph3D_AddNew_gui();

    int returnValue;
    Calculator calc;
    Graph3D m_graph3D;

protected:
    void showEvent(QShowEvent * event);
    void closeEvent(QCloseEvent * event);

private slots:
    void on_pushButton_Ok_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_colorA_clicked();

    void on_pushButton_colorB_clicked();

    void on_pushButton_colorC_clicked();

    void on_pushButton_colorD_clicked();

private:
    Ui::Graph3D_AddNew_gui *ui;

    QString strFromColor(QColor color);
};

#endif // GRAPH3D_ADDNEW_GUI_H
