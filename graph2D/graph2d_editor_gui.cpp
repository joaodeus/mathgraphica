#include "graph2d_editor_gui.h"
#include "ui_graph2d_editor_gui.h"
#include "graph2d_addnew_gui.h"

#include <QColorDialog>

Graph2D_Editor_gui::Graph2D_Editor_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph2D_Editor_gui)
{
    ui->setupUi(this);

    ui->tableWidget_graph2D_list->setColumnCount(1);
}

Graph2D_Editor_gui::~Graph2D_Editor_gui()
{
    delete ui;
}


void Graph2D_Editor_gui::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    int size = m_graph2DEditorListPtr->size();
    ui->tableWidget_graph2D_list->setColumnCount(1);
    ui->tableWidget_graph2D_list->setRowCount(size);


    for (int i = 0; i < size; i++)
    {
        if (ui->tableWidget_graph2D_list->item(i,0) == 0)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem( m_graph2DEditorListPtr->at(i).getGraph2DExpression() );
            ui->tableWidget_graph2D_list->setItem(i, 0, newItem);

        }
        else
        {
            ui->tableWidget_graph2D_list->item(i,0)->setText( m_graph2DEditorListPtr->at(i).getGraph2DExpression()  );
        }

    }

}


void Graph2D_Editor_gui::on_pushButton_ok_clicked()
{
    close();
}

void Graph2D_Editor_gui::on_pushButton_cancel_clicked()
{
    close();
}

void Graph2D_Editor_gui::on_pushButton_add_clicked()
{
    Graph2D_AddNew_gui newGraph2D_gui;
 //   newGraph2D_gui.m_graph2D =
    newGraph2D_gui.exec();
    if ( newGraph2D_gui.returnValue == 1 )
    {
        newGraph2D_gui.m_graph2D.setupGraph();
        m_graph2DEditorListPtr->append(newGraph2D_gui.m_graph2D);

        addNewGraph(newGraph2D_gui.m_graph2D.getGraph2DExpression());

    }


}

void Graph2D_Editor_gui::addNewGraph(const QString &str)
{
    int size = ui->tableWidget_graph2D_list->rowCount();
    ui->tableWidget_graph2D_list->setRowCount(size+1);

    if (ui->tableWidget_graph2D_list->item(size,0) == 0)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(str);
        newItem->setText(str);
        ui->tableWidget_graph2D_list->setItem(size,0,newItem);
    }
    else
    {
        ui->tableWidget_graph2D_list->item(size,0)->setText(str);
    }



}


void Graph2D_Editor_gui::on_pushButton_edit_clicked()
{

    Graph2D_AddNew_gui graph2D_Edit_gui;
    int index = ui->tableWidget_graph2D_list->currentRow();

    graph2D_Edit_gui.m_graph2D = m_graph2DEditorListPtr->at(index);

    graph2D_Edit_gui.exec();
    if ( graph2D_Edit_gui.returnValue == 1 )
    {
        graph2D_Edit_gui.m_graph2D.setupGraph();

        m_graph2DEditorListPtr->removeAt(index);
        m_graph2DEditorListPtr->insert(index,graph2D_Edit_gui.m_graph2D);
        //m_graph2DEditorListPtr->indexOf( graph2D_Edit_gui.m_graph2D);
       // addNewGraph(graph2D_Edit_gui.m_graph2D.getGraph2DExpression());
        ui->tableWidget_graph2D_list->item(index,0)->setText(graph2D_Edit_gui.m_graph2D.getGraph2DExpression());
    }

}


void Graph2D_Editor_gui::on_pushButton_backGndColor_clicked()
{
    QColorDialog dlg;
    m_backGroundColor = dlg.getColor();
}

void Graph2D_Editor_gui::on_pushButton_delete_clicked()
{
    int index = ui->tableWidget_graph2D_list->currentRow();
    if (index >= 0 && index < m_graph2DEditorListPtr->size())
    {
        m_graph2DEditorListPtr->removeAt(index);
        ui->tableWidget_graph2D_list->removeRow(index);

    }


}
