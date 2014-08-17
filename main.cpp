#include "mainwindow.h"
#include <QApplication>
#include "calculator/equation.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
  /*  Calculator calc;

    // solve simple expression
    qDebug()<<calc.SolveExpression("2+5*3").numberReal();


    // solve one variable expression
    calc.addVariableValue("x","5");
    qDebug()<<calc.SolveExpression_fx("2*x+3").numberReal();

    //solve 2 variables expressions
    calc.addVariableValue("x","5");
    calc.addVariableValue("y","3");
    qDebug()<<calc.SolveExpression_fx("2+x+y").numberReal();


    //solve 3 variables expressions
    calc.addVariableValue("x","1.5");
    calc.addVariableValue("y","2");
    calc.addVariableValue("z","3");
    qDebug()<<calc.SolveExpression_fx("z+x+y").numberReal();
*/
   // Parser p;
   // Equation teste(&p);
   // teste.teste();


    return a.exec();
}
