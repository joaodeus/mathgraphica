#ifndef GRAPH3D_CONTAINER_GUI_H
#define GRAPH3D_CONTAINER_GUI_H

#include <QWidget>
#include "graph3d_opengl.h"


namespace Ui {
class Graph3D_Container_gui;
}

class Graph3D_Container_gui : public QWidget
{
    Q_OBJECT
    
public:
    explicit Graph3D_Container_gui(QWidget *parent = 0);
    ~Graph3D_Container_gui();

    Graph3D_OpenGL *graphOpenGL;
    
private slots:
    void on_pushButton_options_clicked();

    void on_pushButton_exit_clicked();


private:
    Ui::Graph3D_Container_gui *ui;
};

#endif // GRAPH3D_CONTAINER_GUI_H
