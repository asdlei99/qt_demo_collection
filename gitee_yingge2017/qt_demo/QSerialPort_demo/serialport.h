#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialPort:public QObject
{
    Q_OBJECT
public:
    SerialPort(QObject*parent=nullptr);
    ~SerialPort();
protected:
    void timerEvent(QTimerEvent *event);
private:
    QSerialPort *m_sp;
private slots:
    void slotReadData();
};

#endif // SERIALPORT_H
