#include "matrix_gui.h"
#include "ui_matrix_gui.h"
#include "globalfunctions.h"
#include "calculator/calculator.h"
#include <QMenu>
#include <QMessageBox>

Matrix_gui::Matrix_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Matrix_gui)
{
    ui->setupUi(this);

    //setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowFlags(Qt::WindowSystemMenuHint); /*Qt::WindowMinMaxButtonsHint | */

    returnValue = -1;

//    ui->pushButton_more_options->setText(">>");
    setMatrixEditable(true);
    //true  <<
    //false >>


    createActions();


    /////////////////////////////
    /*
    headerH = new QHeaderView(Qt::Horizontal,this);
    headerH->setDefaultSectionSize(int(headerH->defaultSectionSize()));
    headerH->setSectionResizeMode(QHeaderView::Interactive);
   // headerH->setResizeMode(QHeaderView::ResizeToContents);

    ui->tableWidget_matrix->setHorizontalHeader(headerH);

    headerV = new QHeaderView(Qt::Vertical,this);
    headerV->setDefaultSectionSize(int(1.5*headerV->defaultSectionSize()));
    ui->tableWidget_matrix->setVerticalHeader(headerV);
*/
}

Matrix_gui::~Matrix_gui()
{
    delete ui;
}

void Matrix_gui::setHeaderInteractive()
{
    headerH->setSectionResizeMode(QHeaderView::Interactive);
}

void Matrix_gui::setHeaderResize()
{
    headerH->setSectionResizeMode(QHeaderView::ResizeToContents);
}


void Matrix_gui::setMatrix(const Matrix &mat_)
{
    mat = mat_;
}


void Matrix_gui::setMatrixCopyPaste(Matrix &matCopyPaste_)
{
    mat_copy_paste = &matCopyPaste_;
}

/*
void Matrix_gui::setMatrix(const int &row, const int &column, const QVector<QString> &matrixList_)
{

    NLine = row;
    NCol = column;
    matrixList<<matrixList_;


    ui->spinBox_columns->setValue(column);
    ui->spinBox_rows->setValue(row);

    ui->tableWidget_matrix->setColumnCount(NCol);
    ui->tableWidget_matrix->setRowCount(NLine);

    int i=0;

    for(int l=0;l<NLine;l++)
    {
        for(int c=0;c<NCol;c++)
        {
            if (ui->tableWidget_matrix->item(l,c) == 0)
            {
                QTableWidgetItem *newItem = new QTableWidgetItem(matrixList.at(i));
                ui->tableWidget_matrix->setItem(l,c, newItem);
                i++;
            }
            else
            {
                ui->tableWidget_matrix->item(l,c)->setText(matrixList.at(i));
                i++;
            }

        }
    } 

}
*/

void Matrix_gui::setMatrixEditable(const bool &bDisplayMatrix)
{
    bMatrixEditable = bDisplayMatrix;
    ui->label_rows->setVisible(bDisplayMatrix);
    ui->label_columns->setVisible(bDisplayMatrix);
    ui->spinBox_rows->setVisible(bDisplayMatrix);
    ui->spinBox_columns->setVisible(bDisplayMatrix);

    ui->pushButton_ones->setVisible(bDisplayMatrix);
    ui->pushButton_random->setVisible(bDisplayMatrix);
    ui->pushButton_zeros->setVisible(bDisplayMatrix);
    ui->pushButton_diagonal->setVisible(bDisplayMatrix);
    ui->pushButton_more_options->setVisible(bDisplayMatrix);

    if (bDisplayMatrix)
        ui->pushButton_more_options->setText("<<");


}


void Matrix_gui::showEvent(QShowEvent *event)
{

    Q_UNUSED(event);

    GetMatrixToTableWidget(mat, *ui->tableWidget_matrix);
    ui->spinBox_rows->setValue(mat.lineCount());
    ui->spinBox_columns->setValue(mat.columnCount());

    //GetMatrixToTableWidget(*mat1, *ui->tableWidget_matrix1);
    //ui->spinBox_rows1->setValue(mat1->lineCount());
    //ui->spinBox_cols1->setValue(mat1->columnCount());

}

void Matrix_gui::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    GetTableWidgetToMatrix(*ui->tableWidget_matrix, mat);
}


void Matrix_gui::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);

    NCol = ui->spinBox_columns->value();
    NLine = ui->spinBox_rows->value();
    matrixList.clear();

    for(int i=0;i<NCol;i++)
    {
        for(int j=0;j<NLine;j++)
        {
            if (ui->tableWidget_matrix->item(j,i) != 0)
            {
                matrixList.append(ui->tableWidget_matrix->item(j,i)->text());
            }
            else
            {
                matrixList.append("0");
            }
        }
    }


}


void Matrix_gui::on_spinBox_rows_valueChanged(int arg1)
{
    ui->tableWidget_matrix->setRowCount(arg1);
}

void Matrix_gui::on_spinBox_columns_valueChanged(int arg1)
{
    ui->tableWidget_matrix->setColumnCount(arg1);
}

void Matrix_gui::on_pushButton_random_clicked()
{
    int NLines = ui->tableWidget_matrix->rowCount();
    int NCols = ui->tableWidget_matrix->columnCount();

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            if (ui->tableWidget_matrix->item(l,c) == 0)
            {
                QTableWidgetItem *newItem = new QTableWidgetItem();
                ui->tableWidget_matrix->setItem(l,c,newItem);
            }
            ui->tableWidget_matrix->item(l,c)->setText(QString("%1").arg(qrand()%100));
        }
    }
}

void Matrix_gui::on_pushButton_zeros_clicked()
{
    int NLines = ui->tableWidget_matrix->rowCount();
    int NCols = ui->tableWidget_matrix->columnCount();

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            if (ui->tableWidget_matrix->item(l,c) == 0)
            {
                QTableWidgetItem *newItem = new QTableWidgetItem();
                ui->tableWidget_matrix->setItem(l,c,newItem);
            }
            ui->tableWidget_matrix->item(l,c)->setText("0");
        }
    }
}

void Matrix_gui::on_pushButton_ones_clicked()
{
    int NLines = ui->tableWidget_matrix->rowCount();
    int NCols = ui->tableWidget_matrix->columnCount();

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            if (ui->tableWidget_matrix->item(l,c) == 0)
            {
                QTableWidgetItem *newItem = new QTableWidgetItem();
                ui->tableWidget_matrix->setItem(l,c,newItem);
            }
            ui->tableWidget_matrix->item(l,c)->setText("1");

        }
    }
}

void Matrix_gui::on_pushButton_diagonal_clicked()
{
    int NLines = ui->tableWidget_matrix->rowCount();
    int NCols = ui->tableWidget_matrix->columnCount();

    for(int l=0;l<NLines;l++)
    {
        for(int c=0;c<NCols;c++)
        {
            if (ui->tableWidget_matrix->item(l,c) == 0)
            {
                QTableWidgetItem *newItem = new QTableWidgetItem();
                ui->tableWidget_matrix->setItem(l,c,newItem);
            }
            if (l == c)
                ui->tableWidget_matrix->item(l,c)->setText("1");
            else
                ui->tableWidget_matrix->item(l,c)->setText("0");

        }
    }
}

void Matrix_gui::on_pushButton_ok_clicked()
{
    returnValue = 1;
    close();
}

void Matrix_gui::on_pushButton_cancel_clicked()
{
    returnValue = 0;
    close();
}

void Matrix_gui::on_pushButton_more_options_clicked()
{
    if (ui->pushButton_ones->isVisible())
    {
        ui->pushButton_ones->hide();
        ui->pushButton_random->hide();
        ui->pushButton_zeros->hide();
        ui->pushButton_diagonal->hide();
        ui->pushButton_more_options->setText(">>");
    }
    else
    {
        ui->pushButton_ones->show();
        ui->pushButton_random->show();
        ui->pushButton_zeros->show();
        ui->pushButton_diagonal->show();
        ui->pushButton_more_options->setText("<<");
    }
}

void Matrix_gui::createActions()
{

    matrixRandomAct = new QAction(tr("Random Matrix"), this);
    //newFormulaAct->setShortcuts(QKeySequence::New);
  //  newFormulaAct->setStatusTip(tr("Add a new formula to the list"));
    connect(matrixRandomAct, SIGNAL(triggered()), this, SLOT(matrixRandom()));


    matrixZerosAct = new QAction(tr("Zeros Matrix"), this);
    connect(matrixZerosAct, SIGNAL(triggered()), this, SLOT(matrixZeros()));

    matrixOnesAct = new QAction(tr("Ones Matrix"), this);
    connect(matrixOnesAct, SIGNAL(triggered()), this, SLOT(matrixOnes()));

    matrixDiagonalAct = new QAction(tr("Diagonal Matrix"), this);
    connect(matrixDiagonalAct, SIGNAL(triggered()), this, SLOT(matrixDiagonal()));

    matrixInverseAct = new QAction(tr("Inverse Matrix"), this);
    connect(matrixInverseAct, SIGNAL(triggered()), this, SLOT(matrixInverse()));

    matrixTransposeAct = new QAction(tr("Transpose Matrix"), this);
    connect(matrixTransposeAct, SIGNAL(triggered()), this, SLOT(matrixTranspose()));

    matrixDeterminantAct = new QAction(tr("Matrix Determinant"), this);
    connect(matrixDeterminantAct, SIGNAL(triggered()), this, SLOT(matrixDeterminant()));

    matrixCopyAct = new QAction(tr("Copy Matrix"), this);
    connect(matrixCopyAct, SIGNAL(triggered()), this, SLOT(matrixCopy()));

    matrixPasteAct = new QAction(tr("Paste Matrix"), this);
    connect(matrixPasteAct, SIGNAL(triggered()), this, SLOT(matrixPaste()));


    //matrixShowAct = new QAction(tr("Show Matrix"), this);
    //connect(matrixShowAct, SIGNAL(triggered()), this, SLOT(showMatrix()));

}

void Matrix_gui::on_tableWidget_matrix_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu menu;

    if (isMatrixEditable() == false)
    {
        menu.addAction(matrixDeterminantAct);
        menu.addAction(matrixCopyAct);
        menu.exec(QCursor::pos());
        return;
    }


    menu.addAction(matrixRandomAct);
    menu.addAction(matrixOnesAct);
    menu.addAction(matrixZerosAct);
    menu.addAction(matrixDiagonalAct);
    menu.addAction(matrixInverseAct);
    menu.addAction(matrixTransposeAct);
    menu.addAction(matrixDeterminantAct);
    menu.addAction(matrixCopyAct);
    menu.addAction(matrixPasteAct);

    menu.exec(QCursor::pos());
}


//////////////////////////////////////////////
// Context menu


void Matrix_gui::matrixRandom()
{
    mat.SetMatrixRandom(ui->tableWidget_matrix->rowCount(), ui->tableWidget_matrix->columnCount());
    GetMatrixToTableWidget(mat,*ui->tableWidget_matrix);
}

void Matrix_gui::matrixZeros()
{
    mat.SetMatrixZeros(ui->tableWidget_matrix->rowCount(), ui->tableWidget_matrix->columnCount());
    GetMatrixToTableWidget(mat,*ui->tableWidget_matrix);
}

void Matrix_gui::matrixOnes()
{
    mat.SetMatrixOnes(ui->tableWidget_matrix->rowCount(), ui->tableWidget_matrix->columnCount());
    GetMatrixToTableWidget(mat,*ui->tableWidget_matrix);
}

void Matrix_gui::matrixDiagonal()
{
    mat.SetMatrixDiagonal(ui->tableWidget_matrix->rowCount(), ui->tableWidget_matrix->columnCount());
    GetMatrixToTableWidget(mat, *ui->tableWidget_matrix);
}

void Matrix_gui::matrixInverse()
{
    mat = mat.inverse();
    GetMatrixToTableWidget(mat, *ui->tableWidget_matrix);
}

void Matrix_gui::matrixTranspose()
{
    mat = mat.transpose();
    GetMatrixToTableWidget(mat, *ui->tableWidget_matrix);
}

void Matrix_gui::matrixDeterminant()
{
    Calculator calc;
    GetTableWidgetToMatrix(*ui->tableWidget_matrix,mat);
    Complexo det = mat.Determinant();
    if (mat.ERRO == false)
        QMessageBox::about(0,"Matrix Determinant",calc.formatResult( det) );
}


void Matrix_gui::matrixCopy()
{
    GetTableWidgetToMatrix(*ui->tableWidget_matrix,*mat_copy_paste);
}



void Matrix_gui::matrixPaste()
{
    //mat.SetMatrixRandom(ui->tableWidget_matrix->rowCount(), ui->tableWidget_matrix->columnCount());
    mat = *mat_copy_paste;
    GetMatrixToTableWidget(mat,*ui->tableWidget_matrix);
    ui->spinBox_rows->setValue(mat.lineCount());
    ui->spinBox_columns->setValue(mat.columnCount());
}
