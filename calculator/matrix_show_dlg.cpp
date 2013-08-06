#include "matrix_show_dlg.h"
#include "ui_matrix_show_dlg.h"

Matrix_show_dlg::Matrix_show_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Matrix_show_dlg)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowFlags(Qt::WindowSystemMenuHint); /*Qt::WindowMinMaxButtonsHint | */

    returnValue = -1;

    ui->pushButton_more_options->setText(">>");
    setMatrixDisplayOnly(false);
    //true  <<
    //false >>




    /////////////////////////////
    headerH = new QHeaderView(Qt::Horizontal,this);
    headerH->setDefaultSectionSize(int(headerH->defaultSectionSize()));
    headerH->setSectionResizeMode(QHeaderView::Interactive);
   // headerH->setResizeMode(QHeaderView::ResizeToContents);

    ui->tableWidget_matrix->setHorizontalHeader(headerH);

    headerV = new QHeaderView(Qt::Vertical,this);
    headerV->setDefaultSectionSize(int(1.5*headerV->defaultSectionSize()));
    ui->tableWidget_matrix->setVerticalHeader(headerV);

}

Matrix_show_dlg::~Matrix_show_dlg()
{
    delete ui;
}

void Matrix_show_dlg::setHeaderInteractive()
{
    headerH->setSectionResizeMode(QHeaderView::Interactive);
}

void Matrix_show_dlg::setHeaderResize()
{
    headerH->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void Matrix_show_dlg::setMatrix(const int &row, const int &column, const QVector<QString> &matrixList_)
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

void Matrix_show_dlg::setMatrixDisplayOnly(const bool &bDisplayMatrix)
{

    ui->pushButton_ones->setVisible(bDisplayMatrix);
    ui->pushButton_random->setVisible(bDisplayMatrix);
    ui->pushButton_zeros->setVisible(bDisplayMatrix);
    ui->pushButton_diagonal->setVisible(bDisplayMatrix);
    ui->pushButton_more_options->setVisible(bDisplayMatrix);

}

void Matrix_show_dlg::hideEvent(QHideEvent *event)
{

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


void Matrix_show_dlg::on_spinBox_rows_valueChanged(int arg1)
{
    ui->tableWidget_matrix->setRowCount(arg1);
}

void Matrix_show_dlg::on_spinBox_columns_valueChanged(int arg1)
{
    ui->tableWidget_matrix->setColumnCount(arg1);
}

void Matrix_show_dlg::on_pushButton_random_clicked()
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

void Matrix_show_dlg::on_pushButton_zeros_clicked()
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

void Matrix_show_dlg::on_pushButton_ones_clicked()
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

void Matrix_show_dlg::on_pushButton_diagonal_clicked()
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

void Matrix_show_dlg::on_pushButton_ok_clicked()
{
    returnValue = 1;
    close();
}

void Matrix_show_dlg::on_pushButton_cancel_clicked()
{
    returnValue = 0;
    close();
}

void Matrix_show_dlg::on_pushButton_more_options_clicked()
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
