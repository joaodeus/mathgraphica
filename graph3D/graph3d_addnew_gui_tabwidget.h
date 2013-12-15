#ifndef GRAPH3D_ADDNEW_GUI_TABWIDGET_H
#define GRAPH3D_ADDNEW_GUI_TABWIDGET_H

#include <QDialog>
#include "graph3D/graph3d_addnew_gui.h"

namespace Ui {
class Graph3D_AddNew_gui_TabWidget;
}

class Graph3D_AddNew_gui_TabWidget : public QDialog
{
    Q_OBJECT

public:
    explicit Graph3D_AddNew_gui_TabWidget(QWidget *parent = 0);
    ~Graph3D_AddNew_gui_TabWidget();

    Graph3D_AddNew_gui m_page1;

private:
    Ui::Graph3D_AddNew_gui_TabWidget *ui;
};

#endif // GRAPH3D_ADDNEW_GUI_TABWIDGET_H
