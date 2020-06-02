#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include     <qtcpsocket.h>

class QTcpServer;
class QTcpSocket;

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);

signals:

public slots:
private slots:
    void slotNewConnection();
    void slotRead();
    void slotDisconnected();
    void slotError(QAbstractSocket::SocketError socketError);
private:
    void sendData();
    QTcpServer *m_pServer;
    QTcpSocket *m_pClientSocket;
};

#endif // TCPSERVER_H
