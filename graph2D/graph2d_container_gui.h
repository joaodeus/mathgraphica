#ifndef GRAPH2D_CONTAINER_GUI_H
#define GRAPH2D_CONTAINER_GUI_H

#include <QWidget>
#include <QHBoxLayout>
#include "graph2d_opengl.h"

namespace Ui {
class Graph2D_Container_gui;
}

class Graph2D_Container_gui : public QWidget
{
    Q_OBJECT

public:
    explicit Graph2D_Container_gui(QWidget *parent = 0);
    ~Graph2D_Container_gui();


    Graph2D_OpenGL m_graph2D_OpenGL;
    QList<Graph2D> *m_graph2DcontainerListPtr;

protected:
    virtual void showEvent(QShowEvent *event);

protected slots:
    virtual void on_pushButton_exit_clicked();

    virtual void on_pushButton_options_clicked();

    virtual void on_pushButton_saveImage_clicked();

    virtual void on_pushButton_startStop_clicked();

private:
    Ui::Graph2D_Container_gui *ui;

public:
    QHBoxLayout *m_HBoxLayout;
  //  Graph2D_Container_gui *m_ui(){return this;}
};

#endif // GRAPH2D_CONTAINER_GUI_H
