#include "graph3d_addnew_gui_tabwidget.h"
#include "ui_graph3d_addnew_gui_tabwidget.h"


Graph3D_AddNew_gui_TabWidget::Graph3D_AddNew_gui_TabWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph3D_AddNew_gui_TabWidget)
{
    ui->setupUi(this);


    ui->tabWidget->insertTab(0, &m_page1, "Graph 2D");


}

Graph3D_AddNew_gui_TabWidget::~Graph3D_AddNew_gui_TabWidget()
{
    delete ui;
}
