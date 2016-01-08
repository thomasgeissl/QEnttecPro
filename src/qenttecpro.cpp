#include "qenttecpro.h"

QString QEnttecPro::getVersionString()
{
    QString versionS;
    versionS += QString::number(QTGENTTECPRO_MAJOR_VERSION);
    versionS += ".";
    versionS += QString::number(QTGENTTECPRO_MINOR_VERSION);
    versionS += ".";
    versionS += QString::number(QTGENTTECPRO_PATCH_VERSION);
    return versionS;
}

QEnttecPro::QEnttecPro(int updateIntervalMs, QObject *parent):
    QObject(parent),
    _connectedB(false),
    _needsUpdate(false)
{
    _serialPortChooser = new qTGSerialPortChooser();

    _timer = new QTimer();
    _timer->start(updateIntervalMs);
    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(update()));
}

QEnttecPro::~QEnttecPro()
{
    _serial.close();
    _connectedB = false;
}
bool QEnttecPro::autoConnect(){
    _serialPortChooser->refresh();

    if(_serialPortChooser->exec())
    {
        qDebug()<<"executed"<<_serialPortChooser->getSelectedPort();
        connect(_serialPortChooser->getSelectedPort());

    }

    return false;
}
bool QEnttecPro::connect(QString portName, unsigned int channels) {

    if(_serial.isOpen())
    {
        _serial.close();
    }

    _serial.setPortName(portName);
    _serial.setBaudRate(57600);
    _serial.setDataBits(QSerialPort::Data8);
    _serial.setParity(QSerialPort::NoParity);
    _serial.setFlowControl(QSerialPort::NoFlowControl);

    if (!_serial.open(QIODevice::ReadWrite)) {
        //emit error(tr("Can't open %1, error code %2").arg(portName).arg(serial.error()));
        qDebug()<<"not connected to"<<portName<<"error"<<_serial.error();
        return false;
    }
    else
    {
        qDebug()<<"is connected";
    }


    return _serial.isOpen();
}

bool QEnttecPro::isConnected()
{
    return _connectedB;
}

void QEnttecPro::disconnect()
{
    _serial.close();
    _connectedB = false;
}

void QEnttecPro::setChannels(unsigned int channels) {
    if(channels < 24)
    {
        channels = 24;
    }
    else if(channels > 512)
    {
        channels = 512;
    }
    levels.resize(channels);
}

void QEnttecPro::update(bool force) {
    if(_needsUpdate || force) {
        _needsUpdate = false;
		unsigned int dataSize = levels.size() + DMX_START_CODE_SIZE;
		unsigned int packetSize = DMX_PRO_HEADER_SIZE + dataSize + DMX_PRO_END_SIZE;

        QByteArray packet;		
		// header
        packet.append(DMX_PRO_START_MSG);
        packet.append(DMX_PRO_SEND_PACKET);
        packet.append(dataSize & 0xff); // data length lsb
        packet.append((dataSize >> 8) & 0xff); // data length msb
		// data
        packet.append((char)DMX_START_CODE); // first data byte
        for(int i = 0; i < levels.size(); i++)
        {
            packet.append(levels[i]);
        }
		
		// end
        packet.append(DMX_PRO_END_MSG);

		
        _serial.write(packet);
	}
}
void QEnttecPro::setUpdateInterval(int updateIntervalMs)
{
    _timer->setInterval(updateInterval);
}

bool QEnttecPro::badChannel(unsigned int channel) {
	if(channel > levels.size()) {
//		ofLogError() << "Channel " + ofToString(channel) + " is out of bounds. Only " + ofToString(levels.size()) + " channels are available.";
		return true;
	}
	if(channel == 0) {
//		ofLogError() << "Channel 0 does not exist. DMX channels start at 1.";
		return true;
	}
	return false;
}

void QEnttecPro::setLevel(unsigned int channel, unsigned char level) {
	if(badChannel(channel)) {
		return;
	}
	channel--; // convert from 1-initial to 0-initial
	if(level != levels[channel]) {
		levels[channel] = level;
        _needsUpdate = true;
	}
}

void QEnttecPro::clear() {
	for (int i = 0; i < levels.size(); i++) {
		levels[i] = 0;
	}
}

unsigned char QEnttecPro::getLevel(unsigned int channel) {
	if(badChannel(channel)) {
		return 0;
	}
	channel--; // convert from 1-initial to 0-initial
	return levels[channel];
}
