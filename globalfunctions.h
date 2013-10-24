#ifndef GLOBALFUNCTIONS_H
#define GLOBALFUNCTIONS_H


#include <QTableWidget>
#include "calculator/matrix.h"


bool GetTableWidgetToMatrix(QTableWidget &tableWidgetMatrix, Matrix &matrix);
void GetMatrixToTableWidget(Matrix &matrix, QTableWidget &tableWidgetMatrix);

void QStringListToTableWidget(QStringList &list, QTableWidget &tableWidget);


int min(const int &a, const int &b);
int max(const int &a, const int &b);

#endif // GLOBALFUNCTIONS_H
