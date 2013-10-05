#include "graph2d_addnew_gui.h"
#include "ui_graph2d_addnew_gui.h"


#include <QColorDialog>



Graph2D_AddNew_gui::Graph2D_AddNew_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph2D_AddNew_gui),
    m_graph2D(&calc)
{
    ui->setupUi(this);

    ui->lineEdit_expression->setText("12*cos(2*x)");
    ui->lineEdit_xmax->setText("50");
    ui->lineEdit_xmin->setText("-50");
    ui->lineEdit_dx->setText("0.1");

    returnValue = -1;
}

Graph2D_AddNew_gui::~Graph2D_AddNew_gui()
{
    delete ui;
}

void Graph2D_AddNew_gui::showEvent(QShowEvent * event)
{
    Q_UNUSED(event);
    // loading the graph values
    //qDebug()<<"show";
    ui->lineEdit_expression->setText(m_graph2D.getGraph2DExpression());
    ui->lineEdit_xmin->setText(m_graph2D.getIntervalMin());
    ui->lineEdit_xmax->setText(m_graph2D.getIntervalMax());
    ui->lineEdit_dx->setText(m_graph2D.getDelta());


    ui->pushButton_color2D->setAutoFillBackground(true);
    ui->pushButton_color2D->setStyleSheet( strFromColor(m_graph2D.getColor()) );

}

QString Graph2D_AddNew_gui::strFromColor(QColor color)
{
    return QString("background-color: rgb(%1, %2, %3)").arg(color.red()).arg(color.green()).arg(color.blue());
}

void Graph2D_AddNew_gui::closeEvent(QCloseEvent * event)
{
    Q_UNUSED(event);
    // saving the user values to the graph
    //qDebug()<<"close";
    m_graph2D.setGraph2DExpression(ui->lineEdit_expression->text());
    m_graph2D.setInterval(ui->lineEdit_xmin->text(), ui->lineEdit_xmax->text());
    m_graph2D.setDelta(ui->lineEdit_dx->text());
}


void Graph2D_AddNew_gui::on_pushButton_Ok_clicked()
{
    returnValue = 1;
    close();
}

void Graph2D_AddNew_gui::on_pushButton_cancel_clicked()
{
    returnValue = 0;
    close();
}

void Graph2D_AddNew_gui::on_pushButton_color2D_clicked()
{            
    QColorDialog dlg;
    QColor color = dlg.getColor();
    m_graph2D.setColor(color);
    ui->pushButton_color2D->setAutoFillBackground(true);
    ui->pushButton_color2D->setStyleSheet(strFromColor(color));
}

void Graph2D_AddNew_gui::on_checkBox_polarGraph_clicked(bool checked)
{
    m_graph2D.setPolarGraph(checked);
}
