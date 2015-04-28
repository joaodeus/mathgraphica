#include <QCoreApplication>

#include "calculator/calculator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    Calculator calc;
    calc.unitTest();

    return a.exec();
}
