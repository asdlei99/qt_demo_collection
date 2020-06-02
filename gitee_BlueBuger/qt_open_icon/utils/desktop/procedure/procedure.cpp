/**
 ** @author:	   浓咖啡
 ** @date:	   2016.10.12
 ** @brief:      应用程序基类
 */

#include "procedure.h"

#define PROCEDURE_BUTTON_STYLE "\
QPushButton{\
    color:#000000;\
    font:100px;\
    border:1px solid #AAAAAA;\
    border-radius:5;\
    background-color:#EEE685;\
}\
QPushButton:pressed{\
    color:#FFFFFF;\
    background-color:#AAAAAA;\
}\
"

#define PROCEDURE_RUN_STYLE "\
QPushButton{\
    color:#000000;\
    font:100px;\
    border:1px solid #AAAAAA;\
    border-radius:5;\
    background-color:#A2CD5A;\
}\
QPushButton:pressed{\
    color:#FFFFFF;\
    background-color:#AAAAAA;\
}\
"

/**
 * @brief 应用程序基类
 * @param _socketname 应用程序名称
 * @param _proName 应用程序可执行文件(包括路径)
 * @param _arguments 应用程序启动参数，针对嵌入式设备
 */
Procedure::Procedure(const QString &_socketname, const QString &_proName, \
                     const QStringList &_arguments):
    socketName(_socketname),
    proName(_proName),
    arguments(_arguments),
    client(NULL),
    proIcon(NULL),
    isRun(false)
{
}

/**
 * @brief 把所有虚函数初始化放到这个里边
 * @return
 */
void Procedure::init()
{
    //初始化图标
    proIcon = createIcon();
    proIcon->setStyleSheet(PROCEDURE_BUTTON_STYLE);
    connect(proIcon, SIGNAL(btnReleased()), this, SLOT(startProSlot()));
}

/**
 * @brief 启动新程序并改变图标状态
 */
void Procedure::startProSlot()
{
    if(isRun){
        qDebug()<<proName<<" has run";
        sendCmd(PROCEDURE_SHOW);
        emit enterPro();
    }else{
        bool startRet = (startSocketServer() && startProcedure());
        if(startRet){
            isRun = true;
            proIcon->setStyleSheet(PROCEDURE_RUN_STYLE);
            emit startResult(true);
        }else{
            emit startResult(false);
        }
    }
}

/**
 * @brief 建立双方的本地通信
 * @return
 */
bool Procedure::startSocketServer()
{
    //初始化服务端
#ifdef Q_OS_LINUX
    //linux下有些特殊，详情参考listen函数帮助文档
    QString socketTmp = QString("/tmp/") + socketName;
    QFile file(socketTmp);
    if(file.exists()){
        file.remove();
    }
#elif defined Q_OS_WIN
#elif defined Q_OS_MAC
#endif
    server = new QLocalServer();
    if (!server->listen(socketName)) {
        qDebug()<<"server listen err";
        return false;
    }else{
        qDebug()<<socketName<<" is listening";
    }
    connect(server, SIGNAL(newConnection()), this, SLOT(connectionSlot()));
    return true;
}


/**
 * @brief 启动外部程序作为新进程
 * @return 成功返回true，失败返回false
 */
bool Procedure::startProcedure()
{
    process = new QProcess;
    process->start(proName, arguments);
    if (!process->waitForStarted())
    {
        qDebug()<<proName<<" process start err";
        return false;
    }else{
        qDebug()<<proName<<" process start success";
        connect(process, SIGNAL(finished(int,QProcess::ExitStatus)),\
                this, SLOT(proExitHandler(int,QProcess::ExitStatus)));

        //这两个信号连接是为了嵌入式设备上能够正常在终端输出子进程的打印信息
        connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readSlot()));
        connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readSlot()));
        return true;
    }
}

void Procedure::readSlot()
{
    procOut = process->readAllStandardError();
    qDebug(procOut);
}

void Procedure::connectionSlot()
{
    qDebug()<<proName<<" socket connect";
    client = server->nextPendingConnection();
    connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
    connect(client, SIGNAL(readyRead()), this, SLOT(parseCmd()));
}

/**
 * @brief 解析来自外部程序命令并通知桌面
 */
void Procedure::parseCmd()
{
    QDataStream in(client);
    QByteArray block;
    in >> block;
    uint cmd = block.toInt();
    emit recvCmd(cmd);
}

/**
 * @brief 桌面发命令给子程序
 * @param cmd
 * @return
 */
bool Procedure::sendCmd(int cmd)
{
    if(client != NULL){
        QString cmdStr = cmdStr.number(cmd);
        QByteArray cmdStream;
        QDataStream out(&cmdStream, QIODevice::WriteOnly);
        out << cmdStr.toLatin1().data();

        if(client->write(cmdStream) == -1){
            return false;
        }else{
            return true;
        }
    }else{
        qDebug()<<socketName<<" client is null";
        return false;
    }
}

/**
 * @brief 程序退出一些处理
 * @param code
 * @param status
 */
void Procedure::proExitHandler(int code, QProcess::ExitStatus status)
{
    qDebug()<<proName<<" exit code = "<<code;
    closeHandler();
}


/**
 * @brief 关闭子进程一些处理
 */
void Procedure::closeHandler()
{
    if(isRun){
        isRun = false;
        process->close();
        server->close();
        delete server;
        server = NULL;
        delete process;
        process = NULL;
        proIcon->setStyleSheet(PROCEDURE_BUTTON_STYLE);
    }
}

/**
 * @brief 针对嵌入式设备提供方法
 */
void Procedure::setArgQWS()
{
    QStringList arg;
    arg<<"-qws";
    setArguments(arg);
}
