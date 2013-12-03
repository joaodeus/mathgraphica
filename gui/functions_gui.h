#ifndef FUNCTIONS_GUI_H
#define FUNCTIONS_GUI_H

#include <QWidget>
#include "calculator/myfunction.h"



namespace Ui {
class Functions_gui;
}

class Functions_gui : public QWidget
{
    Q_OBJECT
    
public:
    explicit Functions_gui(QWidget *parent = 0);
    ~Functions_gui();
    
    int valueReturn;
    //myFunction m_function;
    //QList<myFunction>  m_functions_List;
    myFunction *m_function;
    QList<myFunction> *m_functionsListPtr;


    void showEvent(QShowEvent *event);
    void updateFunctions();



private slots:
    void on_pushButton_new_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::Functions_gui *ui;
};

#endif // FUNCTIONS_GUI_H
