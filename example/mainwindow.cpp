#include "mainwindow.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    _dmx(new QEnttecPro(2)),
    _serialPortWidget(new QTGSerialPortWidget(this))
{
    QWidget *mainWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(mainWidget);

    QSlider *slider_red = new QSlider(this);
    slider_red->setOrientation(Qt::Vertical);
    slider_red->setMinimum(0);
    slider_red->setMaximum(255);

    QSlider *slider_green = new QSlider(this);
    slider_green->setOrientation(Qt::Vertical);
    slider_green->setMinimum(0);
    slider_green->setMaximum(255);
    QSlider *slider_blue = new QSlider(this);
    slider_blue->setOrientation(Qt::Vertical);
    slider_blue->setMinimum(0);
    slider_blue->setMaximum(255);


    mainLayout->addWidget(_serialPortWidget);
    mainLayout->addWidget(slider_red);
    mainLayout->addWidget(slider_green);
    mainLayout->addWidget(slider_blue);

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    connect(_serialPortWidget, SIGNAL(connectionRequest(QString)), _dmx, SLOT(connect(QString)));
    connect(_dmx, SIGNAL(connected(QString)), this, SLOT(connectedToEnttecProDevice(QString)));

    connect(_serialPortWidget, SIGNAL(disconnectionRequest()), _dmx, SLOT(disconnect()));
    connect(_dmx, SIGNAL(disconnected(QString)), _serialPortWidget, SLOT(setDisconnected()));

    connect(slider_red, SIGNAL(valueChanged(int)), this, SLOT(setRed(int)));
    connect(slider_green, SIGNAL(valueChanged(int)), this, SLOT(setGreen(int)));
    connect(slider_blue, SIGNAL(valueChanged(int)), this, SLOT(setBlue(int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::setRed(int value)
{
    _dmx->setLevel(1, value);
}

void MainWindow::setGreen(int value)
{
    _dmx->setLevel(2, value);

}

void MainWindow::setBlue(int value)
{
    _dmx->setLevel(3, value);

}

void MainWindow::connectedToEnttecProDevice(QString portName)
{
    Q_UNUSED(portName);
    _serialPortWidget->setConnected();
}

void MainWindow::disconnectedFromEnttecProDevice(QString portName)
{
    Q_UNUSED(portName);
    _serialPortWidget->setDisconnected();
}
