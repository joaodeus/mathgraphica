#include "graph3d_container_gui.h"

#include <QIcon>
#include "graph3d_editor_gui.h"


//Graph3D_Container_gui::Graph3D_Container_gui(Graph2D_Container_gui *parent) :
//    Graph2D_Container_gui(parent)
Graph3D_Container_gui::Graph3D_Container_gui()
{

 //   setAttribute(Qt::WA_DeleteOnClose); //qDebug()<<"Delete on close: "<<testAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Graph 3D");
    setWindowIcon(QIcon(":/images/images/graf3d.png"));


}

Graph3D_Container_gui::~Graph3D_Container_gui()
{
    m_graph3DcontainerListPtr = NULL;
}


void Graph3D_Container_gui::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    m_graph3DcontainerListPtr = &m_graph3D_OpenGL.m_graph3DList;
    m_HBoxLayout->addWidget(&m_graph3D_OpenGL);
}

void Graph3D_Container_gui::closeEvent(QCloseEvent *event)
{
    m_graph3D_OpenGL.closeEvent(event);
}

void Graph3D_Container_gui::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"container: "<<event->key();
    m_graph3D_OpenGL.keyPressEvent(event);
}

void Graph3D_Container_gui::on_pushButton_exit_clicked()
{
    close();
    //Graph2D_Container_gui::on_pushButton_exit_clicked();
}


void Graph3D_Container_gui::on_pushButton_options_clicked()
{

    Graph3D_Editor_gui graph3D_edit;
    graph3D_edit.m_graph3DEditorListPtr = m_graph3DcontainerListPtr;

    QString aux = QString("%1").arg(m_graph3D_OpenGL.getTimeDelta());
    graph3D_edit.setTimeDelta(aux);

    graph3D_edit.checkBox3DRotation->setChecked(m_graph3D_OpenGL.getAutoRotation());

    graph3D_edit.exec();

    m_graph3D_OpenGL.setAutoRotation(graph3D_edit.checkBox3DRotation->isChecked());

    Calculator calc;
    m_graph3D_OpenGL.setTimeDelta(calc.SolveExpression(graph3D_edit.getTimeDelta()).numberReal());


    m_graph3D_OpenGL.prepareGraphs();
    m_graph3D_OpenGL.setBackGroundColor(graph3D_edit.getBackGroundColor());

    if (!m_graph3D_OpenGL.areTimeGraphs())
    {
        m_graph3D_OpenGL.stopTimer3D();
    }

}

void Graph3D_Container_gui::on_pushButton_saveImage_clicked()
{
    m_graph3D_OpenGL.SaveImageAs();
}

void Graph3D_Container_gui::on_pushButton_startStop_clicked()
{
    m_graph3D_OpenGL.startStopTimer3D();
}
