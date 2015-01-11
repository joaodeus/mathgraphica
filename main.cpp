#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(0));

    if ( !QGLFormat::hasOpenGL() )
    {
         qWarning( "This system has no OpenGL support. Graph's will not be available." );
    }

    QTranslator appTranslator;
    QString qmPath = a.applicationDirPath()+"/translations";
    if (!appTranslator.load("MathGraphica_" + QLocale::system().name(), qmPath))
    {
        qWarning("Translation file not found");
    }
    a.installTranslator(&appTranslator);

    MainWindow w;
    w.show();

    //Todo: create a separate project for unit testing
    Calculator calc;
    calc.unitTest();
    
    return a.exec();
}
