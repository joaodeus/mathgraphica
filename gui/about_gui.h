#ifndef ABOUT_GUI_H
#define ABOUT_GUI_H

#include <QDialog>

namespace Ui {
class About_gui;
}

class About_gui : public QDialog
{
    Q_OBJECT

public:
    explicit About_gui(QWidget *parent = 0);
    ~About_gui();

private:
    Ui::About_gui *ui;
};

#endif // ABOUT_GUI_H
