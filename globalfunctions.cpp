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
                QString str = matrix.GetLineColText(l,c);
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
    int NumbeRows = tableWidgetMatrix.rowCount();
    int NumberColumns = tableWidgetMatrix.columnCount();
    Calculator calc;
    Complexo z;
    bool flagTableMatrixError=false;

    matrix.SetLinesCols(NumbeRows,NumberColumns);

    for(int i=0;i<NumbeRows;i++)
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

