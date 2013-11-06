#ifndef GRAPH3D_EDITOR_GUI_H
#define GRAPH3D_EDITOR_GUI_H


#include "graph2D/graph2d_editor_gui.h"
#include "graph3d.h"

/*class TesteWidget : public TesteDlg
{
  //  Q_OBJECT
public:
    explicit TesteWidget(TesteDlg *parent = 0);*/

class Graph3D_Editor_gui : public Graph2D_Editor_gui
{
public:
    explicit Graph3D_Editor_gui(Graph2D_Editor_gui *parent = 0);

    //Graph3D_Editor_gui();
    QList<Graph3D> *m_graph3DEditorListPtr;

protected:
    virtual void showEvent(QShowEvent *event);
};

#endif // GRAPH3D_EDITOR_GUI_H
