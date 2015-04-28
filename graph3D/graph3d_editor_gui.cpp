#include "graph3d_editor_gui.h"
#include "graph3d_addnew_gui.h"

#include <QMessageBox>

//Graph3D_Editor_gui::Graph3D_Editor_gui()
Graph3D_Editor_gui::Graph3D_Editor_gui(Graph2D_Editor_gui *parent) :
    Graph2D_Editor_gui(parent)
{

    setWindowTitle("Graph3D Editor");

    checkBox3DRotation->setVisible(true);


}


void Graph3D_Editor_gui::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    if (m_graph3DEditorListPtr == NULL)
        return;


    int size = m_graph3DEditorListPtr->size();
    tableWidget_graph->setColumnCount(1);
    tableWidget_graph->setRowCount(size);


    for (int i = 0; i < size; i++)
    {
        if (tableWidget_graph->item(i,0) == 0)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem( m_graph3DEditorListPtr->at(i).getGraph3DExpression() );
            tableWidget_graph->setItem(i, 0, newItem);

        }
        else
        {
            tableWidget_graph->item(i,0)->setText( m_graph3DEditorListPtr->at(i).getGraph3DExpression()  );
        }

        tableWidget_graph->item(i,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }

}


void Graph3D_Editor_gui::on_pushButton_add_clicked()
{
    if (m_graph3DEditorListPtr == NULL)
        return;


    Graph3D_AddNew_gui newGraph3D_gui;
    newGraph3D_gui.existentGraphs_count = m_graph3DEditorListPtr->size();

    newGraph3D_gui.exec();
    if ( newGraph3D_gui.returnValue == 1 )
    {
        newGraph3D_gui.m_graph3D.setupGraph();
        m_graph3DEditorListPtr->append(newGraph3D_gui.m_graph3D);
        addNewGraph(newGraph3D_gui.m_graph3D.getGraph3DExpression());
        close();
    }

}


void Graph3D_Editor_gui::addNewGraph(const QString &str)
{
    int size = tableWidget_graph->rowCount();
    tableWidget_graph->setRowCount(size+1);

    if (tableWidget_graph->item(size,0) == 0)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(str);
        newItem->setText(str);
        tableWidget_graph->setItem(size,0,newItem);
    }
    else
    {
        tableWidget_graph->item(size,0)->setText(str);
    }

    tableWidget_graph->item(size,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

void Graph3D_Editor_gui::on_pushButton_edit_clicked()
{
    Graph3D_AddNew_gui graph3D_Edit_gui;
    int index = tableWidget_graph->currentRow();

    if (index < 0 || index >= m_graph3DEditorListPtr->size())
        return;


    graph3D_Edit_gui.m_graph3D = m_graph3DEditorListPtr->at(index);

    graph3D_Edit_gui.exec();
    if ( graph3D_Edit_gui.returnValue == 1 )
    {
        graph3D_Edit_gui.m_graph3D.setupGraph();

        m_graph3DEditorListPtr->removeAt(index);
        m_graph3DEditorListPtr->insert(index,graph3D_Edit_gui.m_graph3D);
        //m_graph2DEditorListPtr->indexOf( graph2D_Edit_gui.m_graph2D);
       // addNewGraph(graph2D_Edit_gui.m_graph2D.getGraph2DExpression());
        tableWidget_graph->item(index,0)->setText(graph3D_Edit_gui.m_graph3D.getGraph3DExpression());
        close();
    }
}

void Graph3D_Editor_gui::on_pushButton_delete_clicked()
{
    int index = tableWidget_graph->currentRow();

    //if (index < 0 || index >= m_graph2DEditorListPtr->size())
      //  return;

    if (index >= 0 && index < m_graph3DEditorListPtr->size())
    {
        QString str = "Do you want  to delete the selected 3D graph ?\n" + tableWidget_graph->item(index, 0)->text();

        if ( QMessageBox::warning(this,QObject::tr("3D Graphs"), str, QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel)
             == QMessageBox::Yes)
        {
            m_graph3DEditorListPtr->removeAt(index);
            tableWidget_graph->removeRow(index);
            close();
        }
    }
}
