#-------------------------------------------------
#
# Project created by QtCreator 2015-01-25T18:13:22
#
#-------------------------------------------------

QT += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h
include($$PWD/../QEnttecPro.pri)
include($$PWD/libs/QTGUtils/QTGUtils.pri)

