#include "qqprocedure.h"
//#include "QWSServer"

#define QQSTYLE   QString("background-image: url(:/image/qq.png)")

QQProcedure::QQProcedure(QWidget *parent) :
    QWidget(parent)
{
    //增加qq的截图
    QLabel *label = new QLabel(this);
    label->setStyleSheet(QQSTYLE);
    label->setFixedSize(432, 301);
    //核心部分，建立本地socket和桌面进程通信
    qqsocket = new QLocalSocket(this);
    qqsocket->connectToServer("qq"); //和桌面程序做连接
    connect(qqsocket, SIGNAL(readyRead()), this, SLOT(parseCmd()));
    //    setWindowFlags(Qt::FramelessWindowHint);
    //    QWSServer::setCursorVisible(false);
}

/**
 * @brief 解析来自桌面的命令
 */
void QQProcedure::parseCmd()
{
    QDataStream in(qqsocket);
    QByteArray block;
    in >> block;
    u_int cmd = block.toInt();

    if(cmd == PROCEDURE_HIDE)
    {
        this->hide();
    }

    if(cmd == PROCEDURE_SHOW)
    {
        this->show();
        setWindowState(Qt::WindowMaximized);
    }
}

/**
 * @brief 如果窗口最小化，发送命令给桌面
 * @param event
 */
void QQProcedure::changeEvent(QEvent *event)
{
    if(event->type()!=QEvent::WindowStateChange)
        return;

    if(this->windowState()==Qt::WindowMinimized)
    {
        QString cmdStr = cmdStr.number(PROCEDURE_HIDE);
        QByteArray cmdStream;
        QDataStream out(&cmdStream, QIODevice::WriteOnly);
        out << cmdStr.toLatin1().data();

        qqsocket->write(cmdStream);
    }
}
