#include "globalfunctions.h"

#include "calculator/calculator.h"

void GetMatrixToTableWidget(Matrix &matrix, QTableWidget &tableWidgetMatrix)
{
    int NumberRows = matrix.lineCount();
    int NumberColumns = matrix.columnCount();


    tableWidgetMatrix.setRowCount(NumberRows);
    tableWidgetMatrix.setColumnCount(NumberColumns);


    for (int l=0;l<NumberRows;l++)
    {
        for(int c=0;c<NumberColumns;c++)
        {
            if (tableWidgetMatrix.item(l,c) == 0)
            {
                QTableWidgetItem *newItem = new QTableWidgetItem(matrix.GetLineColText(l,c));
                //QString str = matrix.GetLineColText(l,c);
                tableWidgetMatrix.setItem(l,c, newItem);
            }
            else
            {
                tableWidgetMatrix.item(l, c)->setText(matrix.GetLineColText(l,c));
            }
        }
    }
}



bool GetTableWidgetToMatrix(QTableWidget &tableWidgetMatrix, Matrix &matrix)
{
    int NumberRows = tableWidgetMatrix.rowCount();
    int NumberColumns = tableWidgetMatrix.columnCount();
    Calculator calc;
    Complexo z;
    bool flagTableMatrixError=false;

    matrix.SetLinesCols(NumberRows,NumberColumns);

    for(int i=0;i<NumberRows;i++)
    {
        for(int l=0;l<NumberColumns;l++)
        {
            if (tableWidgetMatrix.item(i,l) == 0)
            {
                flagTableMatrixError = true;
                return flagTableMatrixError;
            }
            matrix.SetLineColText(i,l,tableWidgetMatrix.item(i,l)->text());
        }
    }

    return flagTableMatrixError;
}


void QStringListToTableWidget(QStringList &list, QTableWidget &tableWidget)
{

    tableWidget.setRowCount(list.size());

    for(int i = 0; i < list.size(); i++)
    {
        if (tableWidget.item(i,0) == 0)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem(list.at(i));
            tableWidget.setItem(i,0, newItem);
        }
        else
        {
            tableWidget.item(i,0)->setText(list.at(i));
        }
    }
}



int min(const int &a, const int &b)
{
    if (a <= b)
        return a;
    else
        return b;
}

int max(const int &a, const int &b)
{
    if (a >= b)
        return a;
    else
        return b;
}

