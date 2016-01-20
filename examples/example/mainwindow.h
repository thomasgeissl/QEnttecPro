#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include "qenttecpro.h"
#include "qtgserialportwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QEnttecPro *_dmx;
    QTGSerialPortWidget *_serialPortWidget;

private slots:
    void setRed(int value);
    void setGreen(int value);
    void setBlue(int value);

    void connectedToEnttecProDevice(QString port);
    void disconnectedFromEnttecProDevice(QString portName);

};

#endif // MAINWINDOW_H
