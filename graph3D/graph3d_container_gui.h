#ifndef GRAPH3D_CONTAINER_GUI_H
#define GRAPH3D_CONTAINER_GUI_H

#include <QWidget>
#include "graph2D/graph2d_container_gui.h"
#include "graph3D/graph3d_opengl.h"


class Graph3D_Container_gui : public Graph2D_Container_gui
{
    //Q_OBJECT
public:
    //explicit Graph3D_Container_gui(Graph2D_Container_gui *parent = 0);
    Graph3D_Container_gui();
    ~Graph3D_Container_gui();

    Graph3D_OpenGL m_graph3D_OpenGL;
    QList<Graph3D> *m_graph3DcontainerListPtr;

    void showEvent(QShowEvent *event);
    void keyPressEvent(QKeyEvent *event);


private:
    //virtual slots
    void on_pushButton_exit_clicked();
    void on_pushButton_options_clicked();
    void on_pushButton_saveImage_clicked();
    void on_pushButton_startStop_clicked();

};

#endif // GRAPH3D_CONTAINER_GUI_H
