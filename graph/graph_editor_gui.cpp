#include "graph_editor_gui.h"
#include "ui_graph_editor_gui.h"

Graph_Editor_gui::Graph_Editor_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph_Editor_gui)
{
    ui->setupUi(this);
}

Graph_Editor_gui::~Graph_Editor_gui()
{
    delete ui;
}

void Graph_Editor_gui::setTimeDelta(const QString t_delta_)
{
    ui->lineEdit_t_delta->setText(t_delta_);
}

QString Graph_Editor_gui::getTimeDelta()
{
    return ui->lineEdit_t_delta->text();
}



void Graph_Editor_gui::on_pushButton_add_clicked()
{

}

void Graph_Editor_gui::on_pushButton_edit_clicked()
{

}

void Graph_Editor_gui::on_pushButton_delete_clicked()
{

}

void Graph_Editor_gui::on_pushButton_backGndColor_clicked()
{
    QColorDialog dlg;
    m_backGroundColor = dlg.getColor();
}
