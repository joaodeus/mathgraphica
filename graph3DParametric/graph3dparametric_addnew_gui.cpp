#include "graph3dparametric_addnew_gui.h"
#include "ui_graph3dparametric_addnew_gui.h"

#include <QColorDialog>

Graph3DParametric_AddNew_gui::Graph3DParametric_AddNew_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph3DParametric_AddNew_gui)
{
    ui->setupUi(this);

    returnValue = -1;
}

Graph3DParametric_AddNew_gui::~Graph3DParametric_AddNew_gui()
{
    delete ui;
}


QString Graph3DParametric_AddNew_gui::strFromColor(QColor color)
{
    return QString("background-color: rgb(%1, %2, %3)").arg(color.red()).arg(color.green()).arg(color.blue());
}
void Graph3DParametric_AddNew_gui::on_pushButton_color_clicked()
{
    QColorDialog dlg;
    QColor color = dlg.getColor();
    //m_graph3D.setColorA(color);
    ui->pushButton_color->setAutoFillBackground(true);
    ui->pushButton_color->setStyleSheet(strFromColor(color));
}

void Graph3DParametric_AddNew_gui::on_pushButton_cancel_clicked()
{
    returnValue = 0;
    close();
}

void Graph3DParametric_AddNew_gui::on_pushButton_ok_clicked()
{
    returnValue = 1;
    close();
}

void Graph3DParametric_AddNew_gui::on_pushButton_f1_clicked()
{

}

void Graph3DParametric_AddNew_gui::on_pushButton_f2_clicked()
{

}

void Graph3DParametric_AddNew_gui::on_pushButton_f3_clicked()
{

}
