#include "graph2d_container_gui.h"
#include "ui_graph2d_container_gui.h"
#include "graph2d_editor_gui.h"


Graph2D_Container_gui::Graph2D_Container_gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph2D_Container_gui)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    //qDebug()<<"Delete on close: "<<testAttribute(Qt::WA_DeleteOnClose);


    m_graph2D_OpenGL = new Graph2D_OpenGL;
    m_graph2DcontainerListPtr = &m_graph2D_OpenGL->m_graph2DList;

    ui->horizontalLayout->addWidget(m_graph2D_OpenGL);

   // ui->pushButton_exit->hide();
    //ui->pushButton_options->hide();

}

Graph2D_Container_gui::~Graph2D_Container_gui()
{
    delete m_graph2D_OpenGL;
   // delete m_graph2D_OpenGL2;
    delete ui;
}

void Graph2D_Container_gui::on_pushButton_exit_clicked()
{
    close();
}

void Graph2D_Container_gui::on_pushButton_options_clicked()
{

    Graph2D_Editor_gui graph2D_edit;    
    graph2D_edit.m_graph2DEditorListPtr = m_graph2DcontainerListPtr;

    QString aux = QString("%1").arg(m_graph2D_OpenGL->getTimeDelta());
    graph2D_edit.setTimeDelta(aux);

    graph2D_edit.exec();

    Calculator calc;
    m_graph2D_OpenGL->setTimeDelta(calc.SolveExpression(graph2D_edit.getTimeDelta()).numberReal());


    //m_graph2D_OpenGL->prepareGraph();
    m_graph2D_OpenGL->prepareGraphs();
    m_graph2D_OpenGL->setBackGroundColor(graph2D_edit.getBackGroundColor());

    if (!m_graph2D_OpenGL->areTimeGraphs())
    {
        m_graph2D_OpenGL->stopTimer2D();
    }

}

void Graph2D_Container_gui::on_pushButton_saveImage_clicked()
{
    m_graph2D_OpenGL->SaveImageAs();
}

void Graph2D_Container_gui::on_pushButton_startStop_clicked()
{
    m_graph2D_OpenGL->startStopTimer2D();
}
