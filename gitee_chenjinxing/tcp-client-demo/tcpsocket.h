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
    QString _serverIp;//服务器端IP
    QString _serverPort;    //服务器端口号

    quint16 _blockSize;  //消息体的大小
    quint16 _cmdType;    //类型的大小

public:
    bool testConnect(void); //检测是否可以连接
    bool connectToServer(void);//连接服务器

    bool sendMessage(const QByteArray &data);
    QString serverIp() const;
    void setServerIp(const QString &serverIp);

    QString serverPort() const;
    void setServerPort(const QString &serverPort);

private slots:
    void receiveMessage(void);
    void disconnectedMsg();
};

#endif // TCPSOCKET_H
