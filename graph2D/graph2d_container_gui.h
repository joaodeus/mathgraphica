#ifndef GRAPH2D_CONTAINER_GUI_H
#define GRAPH2D_CONTAINER_GUI_H

#include <QWidget>
#include "graph2d_opengl.h"


namespace Ui {
class Graph2D_Container_gui;
}

class Graph2D_Container_gui : public QWidget
{
    Q_OBJECT

public:
    explicit Graph2D_Container_gui(QWidget *parent = 0, Calculator *calc_ = 0);
    ~Graph2D_Container_gui();

    Graph2D_OpenGL *m_graph2D_OpenGL;

    QList<Graph2D> *m_graph2DcontainerListPtr;




private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_options_clicked();

private:
    Ui::Graph2D_Container_gui *ui;

};

#endif // GRAPH2D_CONTAINER_GUI_H
