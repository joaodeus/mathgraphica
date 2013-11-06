#include "graph3d_addnew_gui.h"
#include "ui_graph3d_addnew_gui.h"

#include <QColorDialog>


Graph3D_AddNew_gui::Graph3D_AddNew_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph3D_AddNew_gui)
{
    ui->setupUi(this);

    returnValue = -1;
}

Graph3D_AddNew_gui::~Graph3D_AddNew_gui()
{
    delete ui;
}


void Graph3D_AddNew_gui::showEvent(QShowEvent * event)
{
    Q_UNUSED(event);
    // loading the graph values


    ui->lineEdit_fxy->setText(m_graph3D.getGraph3DExpression());
    ui->lineEdit_xmin->setText(m_graph3D.getIntervalxMin());
    ui->lineEdit_xmax->setText(m_graph3D.getIntervalxMax());
    ui->lineEdit_ymin->setText(m_graph3D.getIntervalyMin());
    ui->lineEdit_ymax->setText(m_graph3D.getIntervalyMax());
    ui->lineEdit_dxdy->setText(m_graph3D.getDelta());
    ui->lineEdit_x->setText(m_graph3D.getVariable1());
    ui->lineEdit_y->setText(m_graph3D.getVariable2());


//    ui->checkBox_polarGraph->setChecked(m_graph2D.isPolarGraph());


    ui->pushButton_colorA->setAutoFillBackground(true);
    ui->pushButton_colorA->setStyleSheet( strFromColor(m_graph3D.getColorA()) );
    ui->pushButton_colorB->setAutoFillBackground(true);
    ui->pushButton_colorB->setStyleSheet( strFromColor(m_graph3D.getColorB()) );
    ui->pushButton_colorC->setAutoFillBackground(true);
    ui->pushButton_colorC->setStyleSheet( strFromColor(m_graph3D.getColorC()) );
    ui->pushButton_colorD->setAutoFillBackground(true);
    ui->pushButton_colorD->setStyleSheet( strFromColor(m_graph3D.getColorD()) );


}

QString Graph3D_AddNew_gui::strFromColor(QColor color)
{
    return QString("background-color: rgb(%1, %2, %3)").arg(color.red()).arg(color.green()).arg(color.blue());
}

void Graph3D_AddNew_gui::closeEvent(QCloseEvent * event)
{
    Q_UNUSED(event);

    m_graph3D.setGraph3DExpression(ui->lineEdit_fxy->text());
    m_graph3D.setMinX(ui->lineEdit_xmin->text());
    m_graph3D.setMinY(ui->lineEdit_ymin->text());
    m_graph3D.setMaxX(ui->lineEdit_xmax->text());
    m_graph3D.setMaxY(ui->lineEdit_ymax->text());
    m_graph3D.setDelta(ui->lineEdit_dxdy->text());
    m_graph3D.setVariable1(ui->lineEdit_x->text());
    m_graph3D.setVariable2(ui->lineEdit_y->text());

}

void Graph3D_AddNew_gui::on_pushButton_Ok_clicked()
{
    returnValue = 1;
    close();
}

void Graph3D_AddNew_gui::on_pushButton_cancel_clicked()
{
    returnValue = 0;
    close();
}

void Graph3D_AddNew_gui::on_pushButton_colorA_clicked()
{
    QColorDialog dlg;
    QColor color = dlg.getColor();
    m_graph3D.setColorA(color);
    ui->pushButton_colorA->setAutoFillBackground(true);
    ui->pushButton_colorA->setStyleSheet(strFromColor(color));
}

void Graph3D_AddNew_gui::on_pushButton_colorB_clicked()
{
    QColorDialog dlg;
    QColor color = dlg.getColor();
    m_graph3D.setColorB(color);
    ui->pushButton_colorB->setAutoFillBackground(true);
    ui->pushButton_colorB->setStyleSheet(strFromColor(color));
}

void Graph3D_AddNew_gui::on_pushButton_colorC_clicked()
{
    QColorDialog dlg;
    QColor color = dlg.getColor();
    m_graph3D.setColorC(color);
    ui->pushButton_colorC->setAutoFillBackground(true);
    ui->pushButton_colorC->setStyleSheet(strFromColor(color));
}

void Graph3D_AddNew_gui::on_pushButton_colorD_clicked()
{
    QColorDialog dlg;
    QColor color = dlg.getColor();
    m_graph3D.setColorD(color);
    ui->pushButton_colorD->setAutoFillBackground(true);
    ui->pushButton_colorD->setStyleSheet(strFromColor(color));
}
