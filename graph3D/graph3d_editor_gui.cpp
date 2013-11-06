#include "graph3d_editor_gui.h"

//Graph3D_Editor_gui::Graph3D_Editor_gui()
Graph3D_Editor_gui::Graph3D_Editor_gui(Graph2D_Editor_gui *parent) :
    Graph2D_Editor_gui(parent)
{

    setWindowTitle("Graph3D Editor");

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
