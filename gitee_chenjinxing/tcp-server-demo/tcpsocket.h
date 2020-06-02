#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>
#include <QDataStream>
class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSocket(QObject *parent = 0);
signals:
public slots:

private:
    quint16 _blockSize;  //消息体的大小
    quint16 _cmdType;    //类型的大小

public:
    void sendMessage(const QByteArray &data);
private slots:
    void receiveMessage(void);
};

#endif // TCPSOCKET_H
