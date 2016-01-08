#pragma once
#include <QtCore>

#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QDebug>

#include "qenttecprodefines.h"

#include "qtgserialportchooser.h"
class QEnttecPro :
        public QObject
{
    Q_OBJECT
public:
    static QString getVersionString();
    explicit QEnttecPro(int updateIntervalMs = 100, QObject *parent = 0);
    virtual ~QEnttecPro();
	
	// connect to the serial port. valid number of channels is 24-512. performance
	// is directly related to the number of channels, so use the minimum required.
    bool autoConnect();
    bool connect(QString device, unsigned int channels = 24);
	void disconnect();
	
	void setLevel(unsigned int channel, unsigned char level);
	void clear();
	unsigned char getLevel(unsigned int channel);	
	
	void setChannels(unsigned int channels = 24); // change the number of channels
	bool isConnected();
	
private:	
    qTGSerialPortChooser *_serialPortChooser;

    QTimer *_timer;
    bool _connectedB;
    QByteArray _levels;
    QVector<unsigned char> levels;
    QSerialPort _serial;

    bool _needsUpdate;
	
	bool badChannel(unsigned int channel);
public slots:
    void update(bool force = false); // send a packet to the dmx controller
    void setUpdateInterval(int updateIntervalMs);
};
