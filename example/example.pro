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
        mainwindow.cpp \
    ../qTGEnttecPro.cpp \
    ../../qTGUtils/qTGSerialPortChooser/qtgserialportchooser.cpp

HEADERS  += mainwindow.h \
    ../qTGEnttecPro.h \
    ../../qTGUtils/qTGUtils.h \
    ../../qTGUtils/qTGSerialPortChooser/qtgserialportchooser.h
