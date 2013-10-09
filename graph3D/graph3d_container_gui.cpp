#include "graph3d_container_gui.h"
#include "ui_graph3d_container_gui.h"

Graph3D_Container_gui::Graph3D_Container_gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph3D_Container_gui)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);

    m_graph3D_OpenGL = new Graph3D_OpenGL;
    m_graph3DcontainerListPtr = &m_graph3D_OpenGL->m_graph3DList;

    ui->horizontalLayout->addWidget(m_graph3D_OpenGL);

}

Graph3D_Container_gui::~Graph3D_Container_gui()
{
    delete m_graph3D_OpenGL;
    delete ui;
}

void Graph3D_Container_gui::on_pushButton_options_clicked()
{

}

void Graph3D_Container_gui::on_pushButton_exit_clicked()
{
    close();
}

void Graph3D_Container_gui::on_pushButton_saveImage_clicked()
{

}

void Graph3D_Container_gui::on_pushButton_startStop_clicked()
{

}
