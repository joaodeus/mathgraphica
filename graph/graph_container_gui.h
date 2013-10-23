#ifndef GRAPH_CONTAINER_GUI_H
#define GRAPH_CONTAINER_GUI_H

#include <QWidget>
#include "graph2D/graph2d_opengl.h"
#include "graph3D/graph3d_opengl.h"


namespace Ui {
class Graph_Container_gui;
}

class Graph_Container_gui : public QWidget
{
    Q_OBJECT

public:
    explicit Graph_Container_gui(QWidget *parent = 0, int type_ = 0);
    ~Graph_Container_gui();


    //Graph2D
    Graph2D_OpenGL *m_graph2D_OpenGL;
    QList<Graph2D> *m_graph2DcontainerListPtr;

    //Graph3D
    Graph3D_OpenGL *m_graph3D_OpenGL;
    QList<Graph3D> *m_graph3DcontainerListPtr;


private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_saveImage_clicked();

    void on_pushButton_startStop_clicked();

    void on_pushButton_options_clicked();

private:
    Ui::Graph_Container_gui *ui;

    int type;
};

#endif // GRAPH_CONTAINER_GUI_H
