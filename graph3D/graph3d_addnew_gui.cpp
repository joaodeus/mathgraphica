#include "graph3d_addnew_gui.h"
#include "ui_graph3d_addnew_gui.h"

#include <QColorDialog>
#include "gui/calculator_gui.h"


Graph3D_AddNew_gui::Graph3D_AddNew_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph3D_AddNew_gui)
{
    ui->setupUi(this);

    on_checkBox_parametricGraph_clicked(false);

    existentGraphs_count = 0;
    create_Default_Graphs_List();

    returnValue = -1;
}

Graph3D_AddNew_gui::~Graph3D_AddNew_gui()
{
    delete ui;
}

// creates the defaults graphs that are presented to the user
void Graph3D_AddNew_gui::create_Default_Graphs_List()
{
    QColor color;

    // graph 0
    m_defaultGraph3D_List.append(m_graph3D);

    //graph 1
    m_graph3D.setGraph3DExpression("(x^2+y^2)*cos(t)");
    color.setRgbF(0.0,1.0,0.0); m_graph3D.setColorA(color);
    color.setRgbF(0.2,0.9,0.3); m_graph3D.setColorB(color);
    color.setRgbF(0.9,1.0,0.2); m_graph3D.setColorC(color);
    color.setRgbF(0.8,0.9,0.3); m_graph3D.setColorD(color);
    m_defaultGraph3D_List.append(m_graph3D);

    //graph 2
    m_graph3D.setGraph3DExpression("5*log|x*y|*cos(t)");
    color.setRgbF(1.0,0.5,0.2); m_graph3D.setColorA(color);
    color.setRgbF(1.0,0.7,0.0); m_graph3D.setColorB(color);
    color.setRgbF(1.0,0.5,0.5); m_graph3D.setColorC(color);
    color.setRgbF(1.0,0.4,0.4); m_graph3D.setColorD(color);
    m_defaultGraph3D_List.append(m_graph3D);

    //graph 3
    m_graph3D.setGraph3DExpression("y*cos(t)");
    color.setRgbF(0.6,0.3,0.1); m_graph3D.setColorA(color);
    color.setRgbF(0.4,0.0,0.0); m_graph3D.setColorB(color);
    color.setRgbF(0.8,0.8,0.8); m_graph3D.setColorC(color);
    color.setRgbF(1.0,1.0,1.0); m_graph3D.setColorD(color);
    m_defaultGraph3D_List.append(m_graph3D);

    /*
    //graph 4
    m_graph3D.setGraph3DExpression("12*cos(t)");
    color.setRgbF(0.90,0.80,0.20); m_graph3D.setColorA(color);
    color.setRgbF(0.95,0.65,0.10); m_graph3D.setColorB(color);
    color.setRgbF(0.10,0.30,0.90); m_graph3D.setColorC(color);
    color.setRgbF(1.00,0.40,0.0); m_graph3D.setColorD(color);
    m_defaultGraph3D_List.append(m_graph3D);
*/

    //graph 5
    m_graph3D.setGraph3DExpression("10*abs(cos(t))*(exp((-(((x-4)^2+(y-4)^2)^2))/1000)+exp((-(((x+4)^2+(y+4)^2)^2))/1000)+0.1*exp(-(((x+4)^2+(y+4)^2)^2))+0.1*exp(-(((x-4)^2+(y-4)^2)^2)))");
    color.setRgbF(0,0,0); m_graph3D.setColorA(color);
    color.setRgbF(1,1,1); m_graph3D.setColorB(color);
    color.setRgbF(0.8,0.8,0.8); m_graph3D.setColorC(color);
    color.setRgbF(0.2,0.2,0.2); m_graph3D.setColorD(color);
    m_defaultGraph3D_List.append(m_graph3D);


    //reset m_graph3D to default
    Graph3D graph_aux;
    m_graph3D = graph_aux;

}

void Graph3D_AddNew_gui::showEvent(QShowEvent * event)
{
    Q_UNUSED(event);
    // loading the graph values

    Graph3D graph_aux;
    Graph3D *graph;

    if (existentGraphs_count  == 0)
    {
        graph = &m_graph3D;
    }
    else if (existentGraphs_count < m_defaultGraph3D_List.size())
    {
        m_graph3D = m_defaultGraph3D_List[existentGraphs_count];
        graph = &m_graph3D;
    }
   else
    {
        graph = &m_graph3D;
    }

    ui->lineEdit_fxy->setText(graph->getGraph3DExpression());
    ui->lineEdit_xmin->setText(graph->getIntervalxMin());
    ui->lineEdit_xmax->setText(graph->getIntervalxMax());
    ui->lineEdit_ymin->setText(graph->getIntervalyMin());
    ui->lineEdit_ymax->setText(graph->getIntervalyMax());
    ui->lineEdit_dxdy->setText(graph->getDelta());
    ui->lineEdit_x->setText(graph->getVariable1());
    ui->lineEdit_y->setText(graph->getVariable2());


//    ui->checkBox_polarGraph->setChecked(m_graph2D.isPolarGraph());


    ui->pushButton_colorA->setAutoFillBackground(true);
    ui->pushButton_colorA->setStyleSheet( strFromColor(graph->getColorA()) );
    ui->pushButton_colorB->setAutoFillBackground(true);
    ui->pushButton_colorB->setStyleSheet( strFromColor(graph->getColorB()) );
    ui->pushButton_colorC->setAutoFillBackground(true);
    ui->pushButton_colorC->setStyleSheet( strFromColor(graph->getColorC()) );
    ui->pushButton_colorD->setAutoFillBackground(true);
    ui->pushButton_colorD->setStyleSheet( strFromColor(graph->getColorD()) );


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

void Graph3D_AddNew_gui::on_pushButton_fxy_clicked()
{
    Calculator_gui calc;
    calc.SetLineEditCalcExpression(ui->lineEdit_fxy->text());

    if (calc.exec() == QDialog::Accepted)
    {
        ui->lineEdit_fxy->setText(calc.GetLineEditCalcExpression());
    }
}

void Graph3D_AddNew_gui::on_pushButton_f2_clicked()
{
    Calculator_gui calc;
    calc.SetLineEditCalcExpression(ui->lineEdit_expression2->text());

    if (calc.exec() == QDialog::Accepted)
    {
        ui->lineEdit_expression2->setText(calc.GetLineEditCalcExpression());
    }
}

void Graph3D_AddNew_gui::on_pushButton_f3_clicked()
{
    Calculator_gui calc;
    calc.SetLineEditCalcExpression(ui->lineEdit_expression3->text());

    if (calc.exec() == QDialog::Accepted)
    {
        ui->lineEdit_expression3->setText(calc.GetLineEditCalcExpression());
    }
}

void Graph3D_AddNew_gui::on_checkBox_parametricGraph_clicked(bool checked)
{

    ui->lineEdit_expression2->setVisible(checked);
    ui->lineEdit_expression3->setVisible(checked);
    ui->pushButton_f2->setVisible(checked);
    ui->pushButton_f3->setVisible(checked);
    ui->label_variables->setVisible(!checked);
    ui->lineEdit_x->setVisible(!checked);
    ui->lineEdit_y->setVisible(!checked);
    ui->pushButton_colorB->setVisible(!checked);
    ui->pushButton_colorC->setVisible(!checked);
    ui->pushButton_colorD->setVisible(!checked);

    ui->label_y_minus->setVisible(!checked);
    ui->label_y_plus->setVisible(!checked);
    ui->lineEdit_ymin->setVisible(!checked);
    ui->lineEdit_ymax->setVisible(!checked);


}
