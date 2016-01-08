#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include "../qTGEnttecPro.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    qTGEnttecPro *_dmx;

public slots:
    void setRed(int value);
    void setGreen(int value);
    void setBlue(int value);

};

#endif // MAINWINDOW_H
