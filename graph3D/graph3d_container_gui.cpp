#include "graph3d_container_gui.h"
#include "ui_graph3d_container_gui.h"

Graph3D_Container_gui::Graph3D_Container_gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph3D_Container_gui)
{
    ui->setupUi(this);

    graphOpenGL = new Graph3D_OpenGL;
    ui->horizontalLayout->addWidget(graphOpenGL);

}

Graph3D_Container_gui::~Graph3D_Container_gui()
{
    delete graphOpenGL;
    delete ui;
}

void Graph3D_Container_gui::on_pushButton_options_clicked()
{

}

void Graph3D_Container_gui::on_pushButton_exit_clicked()
{
    close();
}
