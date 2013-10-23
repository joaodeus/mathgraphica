#include "graph_container_gui.h"
#include "ui_graph_container_gui.h"

Graph_Container_gui::Graph_Container_gui(QWidget *parent, int type_) :
    QWidget(parent),
    ui(new Ui::Graph_Container_gui), type(type_)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    //qDebug()<<"Delete on close: "<<testAttribute(Qt::WA_DeleteOnClose);

    m_graph3D_OpenGL = NULL;
    m_graph2D_OpenGL = NULL;


    if (type == 1)
    {
        setWindowTitle("Graph2D");
        setWindowIcon(QIcon(":/images/images/graf2d.png"));
        m_graph2D_OpenGL = new Graph2D_OpenGL;
        m_graph2DcontainerListPtr = &m_graph2D_OpenGL->m_graph2DList;
        ui->horizontalLayout->addWidget(m_graph2D_OpenGL);
    }

    if (type == 2)
    {

        setWindowTitle("Graph3D");
        setWindowIcon(QIcon(":/images/images/graf3d.png"));
        m_graph3D_OpenGL = new Graph3D_OpenGL;
        m_graph3DcontainerListPtr = &m_graph3D_OpenGL->m_graph3DList;
        ui->horizontalLayout->addWidget(m_graph3D_OpenGL);
    }


}

Graph_Container_gui::~Graph_Container_gui()
{
    if (m_graph3D_OpenGL != NULL)
        delete m_graph3D_OpenGL;

    if (m_graph2D_OpenGL != NULL)
        delete m_graph2D_OpenGL;

    delete ui;
}

void Graph_Container_gui::on_pushButton_exit_clicked()
{
    close();
}

void Graph_Container_gui::on_pushButton_saveImage_clicked()
{

}

void Graph_Container_gui::on_pushButton_startStop_clicked()
{

}

void Graph_Container_gui::on_pushButton_options_clicked()
{

}
