#include "graph3d_editor_gui.h"
#include "ui_graph3d_editor_gui.h"

Graph3D_Editor_gui::Graph3D_Editor_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph3D_Editor_gui)
{
    ui->setupUi(this);
}

Graph3D_Editor_gui::~Graph3D_Editor_gui()
{
    delete ui;
}
