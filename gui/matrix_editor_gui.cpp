#include "matrix_editor_gui.h"
#include "ui_matrix_editor_gui.h"

#include <QMessageBox>
#include <QMenu>
#include "calculator/calculator.h"
#include "globalfunctions.h"

Matrix_editor_gui::Matrix_editor_gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Matrix_editor_gui)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose, true);

    ui->spinBox_rows1->setValue(2);
    ui->spinBox_cols1->setValue(2);
    ui->spinBox_rows2->setValue(2);
    ui->spinBox_cols2->setValue(2);

    ui->tableWidget_matrix1->setRowCount(2);
    ui->tableWidget_matrix1->setColumnCount(2);
    ui->tableWidget_matrix2->setRowCount(2);
    ui->tableWidget_matrix2->setColumnCount(2);
    ui->tableWidget_matrix3->setRowCount(2);
    ui->tableWidget_matrix3->setColumnCount(2);

    tableWidget_mat = NULL;
    mat1            = NULL;
    mat2            = NULL;
    mat3            = NULL;
    mat             = NULL;
    mat_copy_paste  = NULL;

    createActions();

}

Matrix_editor_gui::~Matrix_editor_gui()
{
    delete ui;
}

void Matrix_editor_gui::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    GetMatrixToTableWidget(*mat1, *ui->tableWidget_matrix1);
    ui->spinBox_rows1->setValue(mat1->lineCount());
    ui->spinBox_cols1->setValue(mat1->columnCount());

    GetMatrixToTableWidget(*mat2, *ui->tableWidget_matrix2);
    ui->spinBox_rows2->setValue(mat2->lineCount());
    ui->spinBox_cols2->setValue(mat2->columnCount());

    GetMatrixToTableWidget(*mat3, *ui->tableWidget_matrix3);

}

void Matrix_editor_gui::on_spinBox_rows1_valueChanged(int arg1)
{
    ui->tableWidget_matrix1->setRowCount(arg1);
}

void Matrix_editor_gui::on_spinBox_cols1_valueChanged(int arg1)
{
    ui->tableWidget_matrix1->setColumnCount(arg1);
}


void Matrix_editor_gui::on_spinBox_rows2_valueChanged(int arg1)
{
    ui->tableWidget_matrix2->setRowCount(arg1);
}

void Matrix_editor_gui::on_spinBox_cols2_valueChanged(int arg1)
{
    ui->tableWidget_matrix2->setColumnCount(arg1);
}

void Matrix_editor_gui::updateSpinBoxes()
{
    if (mat == mat1)
    {
        ui->spinBox_cols1->setValue(mat->columnCount());
        ui->spinBox_rows1->setValue(mat->lineCount());
    }

    if (mat == mat2)
    {
        ui->spinBox_cols2->setValue(mat->columnCount());
        ui->spinBox_rows2->setValue(mat->lineCount());
    }
}

void Matrix_editor_gui::on_tableWidget_matrix1_customContextMenuRequested(const QPoint &pos)
{    
    mat = mat1;
    tableWidget_mat = ui->tableWidget_matrix1;
    GetTableWidgetToMatrix(*tableWidget_mat, *mat);
    ContextMenu(pos);
}

void Matrix_editor_gui::on_tableWidget_matrix2_customContextMenuRequested(const QPoint &pos)
{
    mat = mat2;
    tableWidget_mat = ui->tableWidget_matrix2;
    GetTableWidgetToMatrix(*tableWidget_mat, *mat);
    ContextMenu(pos);
}

void Matrix_editor_gui::on_tableWidget_matrix3_customContextMenuRequested(const QPoint &pos)
{
    mat = mat3;
    tableWidget_mat = ui->tableWidget_matrix3;
    GetTableWidgetToMatrix(*tableWidget_mat, *mat);
    ContextMenu(pos);
}



void Matrix_editor_gui::matrixRandom()
{
    mat->SetMatrixRandom(tableWidget_mat->rowCount(),tableWidget_mat->columnCount());
    GetMatrixToTableWidget(*mat,*tableWidget_mat);
}

void Matrix_editor_gui::matrixZeros()
{

    mat->SetMatrixZeros(tableWidget_mat->rowCount(),tableWidget_mat->columnCount());
    GetMatrixToTableWidget(*mat,*tableWidget_mat);

}

void Matrix_editor_gui::matrixOnes()
{
    mat->SetMatrixOnes(tableWidget_mat->rowCount(),tableWidget_mat->columnCount());
    GetMatrixToTableWidget(*mat,*tableWidget_mat);

}

void Matrix_editor_gui::matrixDiagonal()
{
    mat->SetMatrixDiagonal(tableWidget_mat->rowCount(),tableWidget_mat->columnCount());
    GetMatrixToTableWidget(*mat,*tableWidget_mat);

}

void Matrix_editor_gui::matrixInverse()
{
    //*mat3 = mat->inverse();
    //GetMatrixToTableWidget(*mat3,*ui->tableWidget_matrix3);

    *mat = mat->inverse();
    GetMatrixToTableWidget(*mat,*tableWidget_mat);

}

void Matrix_editor_gui::matrixTranspose()
{
    *mat = mat->transpose();
    GetMatrixToTableWidget(*mat,*tableWidget_mat);
}

void Matrix_editor_gui::matrixDeterminant()
{
    Calculator calc;
    Complexo det = mat->Determinant();
    if (mat->ERRO == false)
        QMessageBox::about(0,"Matrix Determinant",calc.formatResult( det) );
}


void Matrix_editor_gui::matrixCopy()
{
    *mat_copy_paste = *mat;
}

void Matrix_editor_gui::matrixPaste()
{
    *mat = *mat_copy_paste;
    GetMatrixToTableWidget(*mat_copy_paste,*tableWidget_mat);
    updateSpinBoxes();
}


void Matrix_editor_gui::showMatrix()
{
    mat->Show();

   // GetMatrixToTableWidget(*mat, *tableWidget_mat);
}

/////////////////////////////////////////////////////////////////////

void Matrix_editor_gui::ContextMenu(QPoint pos)
{
    Q_UNUSED(pos);
    QMenu menu;

    menu.addAction(matrixRandomAct);
    menu.addAction(matrixOnesAct);
    menu.addAction(matrixZerosAct);
    menu.addAction(matrixDiagonalAct);
    menu.addAction(matrixInverseAct);
    menu.addAction(matrixTransposeAct);
    menu.addAction(matrixDeterminantAct);
    menu.addAction(matrixCopyAct);
    menu.addAction(matrixPasteAct);
   // menu.addAction(matrixShowAct);

    menu.exec(QCursor::pos());

}

void Matrix_editor_gui::createActions()
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


    matrixShowAct = new QAction(tr("Show Matrix"), this);
    connect(matrixShowAct, SIGNAL(triggered()), this, SLOT(showMatrix()));

}

void Matrix_editor_gui::on_pushButton_calculate_clicked()
{
    GetTableWidgetToMatrix(*ui->tableWidget_matrix1, *mat1);
    GetTableWidgetToMatrix(*ui->tableWidget_matrix2, *mat2);

    switch (ui->comboBox_matrix_operation->currentIndex()) {
    case 0: {
        //mat = mat3;
        *mat3 = *mat1 + *mat2;
        if (mat3->ERRO == false)
            GetMatrixToTableWidget(*mat3,*ui->tableWidget_matrix3);
        break;
    }
    case 1: {
        *mat3 = *mat1 - *mat2;
        if (mat3->ERRO == false)
            GetMatrixToTableWidget(*mat3,*ui->tableWidget_matrix3);
        break;
    }
    case 2: {
        *mat3 = (*mat1) * (*mat2);
        if (mat3->ERRO == false)
            GetMatrixToTableWidget(*mat3,*ui->tableWidget_matrix3);
        break;
    }
    default:
        break;
    }
}


void Matrix_editor_gui::on_pushButton_Close_clicked()
{
    close();
}
