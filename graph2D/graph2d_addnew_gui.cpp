#include "graph2d_addnew_gui.h"
#include "ui_graph2d_addnew_gui.h"

#include <QColorDialog>
#include "gui/calculator_gui.h"


Graph2D_AddNew_gui::Graph2D_AddNew_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph2D_AddNew_gui)
{
    ui->setupUi(this);

    on_checkBox_polarGraph_clicked(false);
    on_checkBox_parametricGraph_clicked(false);

    //hide it for version 2.0.0 has it is not ready
    //ui->checkBox_parametricGraph->setVisible(false);

    existentGraphs_count = 0;
    create_Default_Graphs_List();

    returnValue = -1;
}

Graph2D_AddNew_gui::~Graph2D_AddNew_gui()
{
    delete ui;
}



// creates the defaults graphs that are presented to the user
void Graph2D_AddNew_gui::create_Default_Graphs_List()
{
    QColor color;

    // graph 0
    m_defaultGraph2D_List.append(m_graph2D);

    //graph 1
    m_graph2D.setGraph2DExpression("12*sin(3*x+t)");
    m_graph2D.setPolarGraph(true);
    m_graph2D.setInterval(0,50);
    m_graph2D.setColor(0.25,0.78,0.89);
    m_defaultGraph2D_List.append(m_graph2D);

    //graph 2
    m_graph2D.setGraph2DExpression("22*sin(x/4)*cos(t)");
    m_graph2D.setPolarGraph(false);
    m_graph2D.setInterval(-50,50);
    m_graph2D.setColor(1,0.76,0.04);
    m_defaultGraph2D_List.append(m_graph2D);

    //graph 3
    m_graph2D.setGraph2DExpression("x*cos(t)");
    m_graph2D.setPolarGraph(false);
    m_graph2D.setInterval(-50,50);
    m_graph2D.setColor(0,1,0);
    m_defaultGraph2D_List.append(m_graph2D);


    /*
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

    //graph 4
    m_graph3D.setGraph3DExpression("12*cos(t)");
    color.setRgbF(0.90,0.80,0.20); m_graph3D.setColorA(color);
    color.setRgbF(0.95,0.65,0.10); m_graph3D.setColorB(color);
    color.setRgbF(0.10,0.30,0.90); m_graph3D.setColorC(color);
    color.setRgbF(1.00,0.40,0.0); m_graph3D.setColorD(color);
    m_defaultGraph3D_List.append(m_graph3D);

*/
    //reset m_graph3D to default
    Graph2D graph_aux;
    m_graph2D = graph_aux;

}

void Graph2D_AddNew_gui::showEvent(QShowEvent * event)
{
    Q_UNUSED(event);
    // loading the graph values

    Graph2D graph_aux;
    Graph2D *graph;

    if (existentGraphs_count  == 0)
    {
        graph = &m_graph2D;
    }
    else if (existentGraphs_count < m_defaultGraph2D_List.size())
    {
        m_graph2D = m_defaultGraph2D_List[existentGraphs_count];
        graph = &m_graph2D;
    }
   else
    {
        graph = &m_graph2D;
    }


    ui->lineEdit_expression->setText(graph->getGraph2DExpression());
    ui->lineEdit_xmin->setText(graph->getIntervalMin());
    ui->lineEdit_xmax->setText(graph->getIntervalMax());
    ui->lineEdit_dx->setText(graph->getDelta());
    ui->checkBox_polarGraph->setChecked(graph->isPolarGraph());


    if (graph->isParametricGraph())
    {
        ui->lineEdit_expression->setText(graph->getGraph2DExpression_f1());
        ui->lineEdit_expression2->setText(graph->getGraph2DExpression_f2());
        ui->lineEdit_expression2->setVisible(true);
        ui->pushButton_fx_2->setVisible(true);
        ui->checkBox_parametricGraph->setChecked(true);
    }

    ui->pushButton_color2D->setAutoFillBackground(true);
    ui->pushButton_color2D->setStyleSheet( strFromColor(graph->getColor()) );


  /*
    ui->lineEdit_expression->setText(m_graph2D.getGraph2DExpression());
    ui->lineEdit_xmin->setText(m_graph2D.getIntervalMin());
    ui->lineEdit_xmax->setText(m_graph2D.getIntervalMax());
    ui->lineEdit_dx->setText(m_graph2D.getDelta());
    ui->checkBox_polarGraph->setChecked(m_graph2D.isPolarGraph());


    ui->pushButton_color2D->setAutoFillBackground(true);
    ui->pushButton_color2D->setStyleSheet( strFromColor(m_graph2D.getColor()) );
*/
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

    m_graph2D.setInterval(ui->lineEdit_xmin->text(), ui->lineEdit_xmax->text());
    m_graph2D.setDelta(ui->lineEdit_dx->text());

    m_graph2D.setPolarGraph(ui->checkBox_polarGraph->isChecked());
    m_graph2D.setParametric(ui->checkBox_parametricGraph->isChecked());


    if (m_graph2D.isParametricGraph())
    {
        m_graph2D.setGraph2DExpression_f1(ui->lineEdit_expression->text());
        m_graph2D.setGraph2DExpression_f2(ui->lineEdit_expression2->text());
    }
    else
    {
        m_graph2D.setGraph2DExpression(ui->lineEdit_expression->text());
    }


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
    if (color.isValid())
    {
        m_graph2D.setColor(color);
        ui->pushButton_color2D->setAutoFillBackground(true);
        ui->pushButton_color2D->setStyleSheet(strFromColor(color));
    }
}

void Graph2D_AddNew_gui::on_checkBox_polarGraph_clicked(bool checked)
{
    m_graph2D.setPolarGraph(checked);

    if (checked)
        ui->checkBox_parametricGraph->setDisabled(true);
    else
        ui->checkBox_parametricGraph->setDisabled(false);
}

void Graph2D_AddNew_gui::on_pushButton_fx_clicked()
{
    Calculator_gui calc;
    calc.SetLineEditCalcExpression(ui->lineEdit_expression->text());

    if (calc.exec() == QDialog::Accepted)
    {
        ui->lineEdit_expression->setText(calc.GetLineEditCalcExpression());
    }
}

void Graph2D_AddNew_gui::on_checkBox_parametricGraph_clicked(bool checked)
{

    //parametric graph
    if (checked)
    {
        m_graph2D.setParametric(checked);
        ui->checkBox_polarGraph->setDisabled(true);
        ui->lineEdit_expression2->setVisible(true);
        ui->pushButton_fx_2->setVisible(true);

        ui->pushButton_fx->setText("f1(t) =");
        ui->label_x_plus->setText("+t =");
        ui->label_x_minus->setText("-t =");
        ui->label_delta->setText("dt =");
        ui->lineEdit_xmin->setText("0");
        ui->lineEdit_expression->setText("");
    }
    else //not a parametric graph
    {
        ui->checkBox_polarGraph->setDisabled(false);
        ui->lineEdit_expression2->setVisible(false);
        ui->pushButton_fx_2->setVisible(false);

        ui->pushButton_fx->setText("f(x,t) =");

        ui->label_x_plus->setText("+x =");
        ui->label_x_minus->setText("-x =");
        ui->label_delta->setText("dx =");
        ui->lineEdit_xmin->setText("-50");
    }

}

void Graph2D_AddNew_gui::on_pushButton_fx_2_clicked()
{
    Calculator_gui calc;
    calc.SetLineEditCalcExpression(ui->lineEdit_expression2->text());

    if (calc.exec() == QDialog::Accepted)
    {
        ui->lineEdit_expression2->setText(calc.GetLineEditCalcExpression());
    }
}
