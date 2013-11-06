#ifndef GRAPH2D_EDITOR_GUI_H
#define GRAPH2D_EDITOR_GUI_H

#include <QDialog>
#include <QTableWidget>
#include "graph2d.h"

namespace Ui {
class Graph2D_Editor_gui;
}

class Graph2D_Editor_gui : public QDialog
{
    Q_OBJECT    

public:
    explicit Graph2D_Editor_gui(QWidget *parent = 0);
    ~Graph2D_Editor_gui();


    QList<Graph2D> *m_graph2DEditorListPtr;
    QColor getBackGroundColor(){return m_backGroundColor;}

    void setTimeDelta(const QString t_delta_);
    QString getTimeDelta();

protected:
    void showEvent(QShowEvent *event);
    QColor m_backGroundColor;

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_backGndColor_clicked();

    void on_pushButton_delete_clicked();

    void on_tableWidget_graph2D_list_cellDoubleClicked(int row, int column);

private:
    Ui::Graph2D_Editor_gui *ui;

    void addNewGraph(const QString &str);

public:
    QTableWidget *tableWidget_graph; // to used in the derived class, to access ui->tableWidget_graph2D_list
};

#endif // GRAPH2D_EDITOR_GUI_H
