/**
 ** @author:	   浓咖啡
 ** @date:	   2016.7.7
 ** @brief:      对单个程序封装
 */

#ifndef PROCEDURE_H
#define PROCEDURE_H

#include "basebutton.h"
#include <QLocalServer>
#include <QLocalSocket>
#include "desktopcmd.h"

class Procedure : public QObject
{
    Q_OBJECT
public:
    explicit Procedure(const QString &_socketname, const QString &_proName, \
                       const QStringList &_arguments = QStringList());
    bool sendCmd(int cmd);
    bool startProcedure();
    void init();  //执行一些初始化工作
    bool getState() const {return isRun;}
    void setArguments(const QStringList &_arguments){arguments = _arguments;}
    void setArgQWS();  //专门为嵌入式使用的参数列表
    void closeHandler();  //关闭子进程一些处理
    BaseButton *proIcon;  //应用图标

signals:
    void startResult(bool);
    void enterPro();  //信号表示程序从后台转为前台运行
    void recvCmd(uint);  //收到来自APP的命令

protected slots:
    void connectionSlot();
    void startProSlot();
    virtual void proExitHandler(int code, QProcess::ExitStatus status);
    void readSlot();
    void parseCmd();

protected:
    virtual BaseButton *createIcon() = 0;
    bool startSocketServer();

private:
    QLocalServer *server;  //本地socket服务端
    QLocalSocket *client;  //本地socket客户端
    QProcess *process;  //进程
    QString socketName;  //socket监听名称
    QString proName;  //可执行程序名称
    QStringList arguments;  //可执行程序需要参数
    bool isRun;  //程序是否已经运行
    QByteArray procOut;
};

#endif // PROCEDURE_H
