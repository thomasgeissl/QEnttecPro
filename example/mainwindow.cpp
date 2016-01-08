#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

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

    QSplitter *splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(slider_red);
    splitter->addWidget(slider_green);
    splitter->addWidget(slider_blue);
    setCentralWidget(splitter);



    connect(slider_red, SIGNAL(valueChanged(int)), this, SLOT(setRed(int)));
    connect(slider_green, SIGNAL(valueChanged(int)), this, SLOT(setGreen(int)));
    connect(slider_blue, SIGNAL(valueChanged(int)), this, SLOT(setBlue(int)));



    _dmx = new qTGEnttecPro();


    _dmx->autoConnect();
//    _dmx->connect("usbserial-EN160415");
    _dmx->setChannels();
    _dmx->update();


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
