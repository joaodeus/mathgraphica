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
    gui/calculator_gui.cpp \
    gui/equation_gui.cpp \
    calculator/myfunction.cpp \
    gui/systemeq_gui.cpp \
    globalfunctions.cpp \
    gui/integral_gui.cpp \
    calculator/integraldouble.cpp \
    gui/integraldouble_gui.cpp \
    gui/formulas_gui.cpp \
    calculator/formulas.cpp \
    graph2D/graph2d.cpp \
    graph2D/graph2d_opengl.cpp \
    gui/matrix_editor_gui.cpp \
    calculator/matrix_gui.cpp \
    graph2D/graph2d_container_gui.cpp \
    graph2D/graph2d_editor_gui.cpp \
    graph2D/graph2d_addnew_gui.cpp \
    graph/graph_container_gui.cpp \
    graph/graph_editor_gui.cpp \
    graph3D/graph3d_container_gui.cpp \
    graph3D/graph3d_editor_gui.cpp \
    gui/functions_gui.cpp \
    graph3D/graph3d_addnew_gui.cpp \
    gui/formatresult_gui.cpp \
    gui/about_gui.cpp \
    gui/variables_gui.cpp \
    graph3DParametric/graph3dparametric_addnew_gui.cpp \
    graph3DParametric/graph3dparametric.cpp \
<<<<<<< HEAD
    graph3DParametric/graph3dparametric_opengl.cpp \
    gui/baseconverter_gui.cpp
=======
    graph3DParametric/graph3dparametric_opengl.cpp
>>>>>>> 9c6971fcf5f3e7c086af781097185f74a470dfea

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
    gui/calculator_gui.h \
    gui/equation_gui.h \
    calculator/myfunction.h \
    gui/systemeq_gui.h \
    globalfunctions.h \
    gui/integral_gui.h \
    calculator/integraldouble.h \
    gui/integraldouble_gui.h \
    gui/formulas_gui.h \
    calculator/formulas.h \
    graph2D/graph2d.h \
    graph2D/graph2d_opengl.h \
    gui/matrix_editor_gui.h \
    calculator/matrix_gui.h \
    graph2D/graph2d_container_gui.h \
    graph2D/graph2d_editor_gui.h \
    graph2D/graph2d_addnew_gui.h \
    graph/graph.h \
    graph/graph_container_gui.h \
    graph/graph_editor_gui.h \
    graph3D/graph3d_container_gui.h \
    graph3D/graph3d_editor_gui.h \
    gui/functions_gui.h \
    graph3D/graph3d_addnew_gui.h \
    gui/formatresult_gui.h \
    gui/about_gui.h \
    gui/variables_gui.h \
    graph3DParametric/graph3dparametric_addnew_gui.h \
    graph3DParametric/graph3dparametric.h \
    graph3DParametric/graph3dparametric_opengl.h \
<<<<<<< HEAD
    calculator/math_functions_list.h \
    gui/baseconverter_gui.h
=======
    calculator/math_functions_list.h
>>>>>>> 9c6971fcf5f3e7c086af781097185f74a470dfea

FORMS    += mainwindow.ui \
    gui/calculator_gui.ui \
    gui/equation_gui.ui \
    gui/systemeq_gui.ui \
    gui/integral_gui.ui \
    gui/integraldouble_gui.ui \
    gui/formulas_gui.ui \
    gui/matrix_editor_gui.ui \
    calculator/matrix_gui.ui \
    graph2D/graph2d_container_gui.ui \
    graph2D/graph2d_editor_gui.ui \
    graph2D/graph2d_addnew_gui.ui \
    graph/graph_container_gui.ui \
    graph/graph_editor_gui.ui \
    gui/functions_gui.ui \
    graph3D/graph3d_addnew_gui.ui \
    gui/formatresult_gui.ui \
    gui/about_gui.ui \
    gui/variables_gui.ui \
    graph3DParametric/graph3dparametric_addnew_gui.ui \
    gui/baseconverter_gui.ui

RESOURCES += \
    mathgraphica.qrc

OTHER_FILES += \
    shaders/fragmentShaderES2.fsh \
    shaders/vertexShaderES2.vsh \
    shaders/fragShader3D.fsh \
    shaders/vertShader3D.vsh
