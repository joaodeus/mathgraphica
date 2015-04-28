#-------------------------------------------------
#
# Project created by QtCreator 2015-04-24T23:41:06
#
#-------------------------------------------------

QT       += core gui widgets

#QT       -= gui

CONFIG += c++11

TARGET = mathgraphicaUnitTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += mainUnitTest.cpp \
    calculator/calculator.cpp \
    calculator/complexo.cpp \
    calculator/equation.cpp \
    calculator/formatresult.cpp \
    calculator/formulas.cpp \
    calculator/integral.cpp \
    calculator/integraldouble.cpp \
    calculator/matrix.cpp \
#   calculator/matrix_gui.cpp \
    calculator/myfunction.cpp \
    calculator/mynumber.cpp \
    calculator/mynumber_functions.cpp \
    calculator/parser.cpp \
    calculator/error.cpp

HEADERS += \
    calculator/calculator.h \
    calculator/complexo.h \
    calculator/equation.h \
    calculator/formatresult.h \
    calculator/formulas.h \
    calculator/integral.h \
    calculator/integraldouble.h \
    calculator/matrix.h \
 #  calculator/matrix_gui.h \
    calculator/myfunction.h \
    calculator/mynumber.h \
    calculator/mynumber_functions.h \
    calculator/parser.h \
    calculator/error.h
