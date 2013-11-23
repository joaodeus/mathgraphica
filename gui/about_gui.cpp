#include "about_gui.h"
#include "ui_about_gui.h"

About_gui::About_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About_gui)
{
    ui->setupUi(this);

    //setStyleSheet("background:transparent;");

   // setAttribute(Qt::WA_TranslucentBackground,true);
    //setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
    //setWindowFlags(Qt::WindowStaysOnTopHint );
   // setWindowOpacity(0.9);


 //   bool t=testAttribute ( Qt::WA_TranslucentBackground);
    //qDebug()<<t;
}

About_gui::~About_gui()
{
    delete ui;
}
