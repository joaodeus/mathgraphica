#ifndef GRAPH_EDITOR_GUI_H
#define GRAPH_EDITOR_GUI_H

#include <QDialog>
#include <QColorDialog>
#include "graph/graph.h"


namespace Ui {
class Graph_Editor_gui;
}

class Graph_Editor_gui : public QDialog
{
    Q_OBJECT

public:
    explicit Graph_Editor_gui(QWidget *parent = 0);
    ~Graph_Editor_gui();

    QList<Graph> *m_graphEditorListPtr;

    QColor getBackGroundColor(){return m_backGroundColor;}
private:
    QColor m_backGroundColor;


public:
    void setTimeDelta(const QString t_delta_);
    QString getTimeDelta();



private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_backGndColor_clicked();

private:
    Ui::Graph_Editor_gui *ui;


};

#endif // GRAPH_EDITOR_GUI_H
