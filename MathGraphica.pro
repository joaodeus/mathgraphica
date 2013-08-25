#-------------------------------------------------
#
# Project created by QtCreator 2013-07-24T22:31:03
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MathGraphica
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    graph3D/graph3d.cpp \
    graph3D/graph3d_opengl.cpp \
    calculator/calculator.cpp \
    calculator/parser.cpp \
    calculator/complexo.cpp \
    calculator/mynumber.cpp \
    calculator/mynumber_functions.cpp \
    calculator/formatresult.cpp \
    calculator/equation.cpp \
    calculator/integral.cpp \
    calculator/matrix.cpp \
    calculator/matrix_show_dlg.cpp \
    gui/calculator_gui.cpp \
    gui/equation_gui.cpp \
    calculator/myfunction.cpp \
    gui/systemeq_gui.cpp \
    globalfunctions.cpp \
    gui/integral_gui.cpp

HEADERS  += mainwindow.h \
    graph3D/graph3d.h \
    graph3D/graph3d_opengl.h \
    calculator/calculator.h \
    calculator/parser.h \
    calculator/complexo.h \
    calculator/mynumber.h \
    calculator/mynumber_functions.h \
    calculator/formatresult.h \
    calculator/equation.h \
    calculator/integral.h \
    calculator/matrix.h \
    calculator/matrix_show_dlg.h \
    gui/calculator_gui.h \
    gui/equation_gui.h \
    calculator/myfunction.h \
    gui/systemeq_gui.h \
    globalfunctions.h \
    gui/integral_gui.h

FORMS    += mainwindow.ui \
    calculator/matrix_show_dlg.ui \
    gui/calculator_gui.ui \
    gui/equation_gui.ui \
    gui/systemeq_gui.ui \
    gui/integral_gui.ui

RESOURCES += \
    mathgraphica.qrc

OTHER_FILES += \
    shaders/fragmentShaderES2.fsh \
    shaders/vertexShaderES2.vsh
