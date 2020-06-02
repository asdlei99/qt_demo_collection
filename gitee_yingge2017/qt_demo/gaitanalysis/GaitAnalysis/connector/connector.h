#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QObject>
#include "libusb.h"

class Connector : public QObject
{
    Q_OBJECT
public:
    explicit Connector(QObject *parent = nullptr);
    ~Connector();
protected:
    void timerEvent(QTimerEvent *event);
signals:

public slots:
private:
    void open();
    void write();
    void read();

    void printError(const int num);
    void reset();

    void printUsbDev();

    void printdev(libusb_device *dev); //prototype of the function
    int  str2hex(char *hex);
    void hex2str(uchar *pbDest, uchar *pbSrc, ushort nLen);
    void HexToAscii(unsigned char * pHex, unsigned char * pAscii, int nLen);

    void dataParser();
private:
    int m_readId;
    int m_writeId;
    libusb_device_handle *m_dev_handle;
    uint32_t m_revFrameSize;
};

#endif // CONNECTOR_H
