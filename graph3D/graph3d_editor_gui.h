#ifndef GRAPH3D_EDITOR_GUI_H
#define GRAPH3D_EDITOR_GUI_H

#include <QDialog>

namespace Ui {
class Graph3D_Editor_gui;
}

class Graph3D_Editor_gui : public QDialog
{
    Q_OBJECT

public:
    explicit Graph3D_Editor_gui(QWidget *parent = 0);
    ~Graph3D_Editor_gui();


private:
    Ui::Graph3D_Editor_gui *ui;
};

#endif // GRAPH3D_EDITOR_GUI_H
