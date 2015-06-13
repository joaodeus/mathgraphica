#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("MathGraphica");
    QCoreApplication::setOrganizationName("João de Deus");

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    /*if ( !QGLFormat::hasOpenGL() )
    {
         qWarning( "This system has no OpenGL support. Graphs will not be available." );
    }*/

    QTranslator appTranslator;
    QString qmPath = a.applicationDirPath()+"/translations";
    if (!appTranslator.load("MathGraphica_" + QLocale::system().name(), qmPath))
    {
        qWarning("Translation file not found");
    }
    a.installTranslator(&appTranslator);

    MainWindow w;
    w.show();
    
    return a.exec();
}
