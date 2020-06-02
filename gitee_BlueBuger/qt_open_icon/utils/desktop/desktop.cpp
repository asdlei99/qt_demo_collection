/**
 ** @author:	   浓咖啡
 ** @date:	   2016.10.12
 ** @brief:      桌面程序
 */
#include "desktop.h"

#include "toast.h"

Desktop::Desktop(QWidget *parent) :
    QWidget(parent)
{
    //启动按键服务
//    keyDetect = new KeyDetect;
//    keyDetect->start();
//    connect(keyDetect, SIGNAL(submitKeyVal(int)), this, SLOT(keyHandler(int)));

    //总体布局
    QGridLayout *lay = new QGridLayout(this);

    //qq示例程序
    qqProcedure = new QQProcedure;
    qqProcedure->init();
    lay->addWidget(qqProcedure->proIcon, 0, 0);
    connect(qqProcedure, SIGNAL(startResult(bool)), this, SLOT(startSlot(bool)));
    connect(qqProcedure, SIGNAL(enterPro()), this, SLOT(enterProSlot()));
    connect(qqProcedure, SIGNAL(recvCmd(uint)), this, SLOT(handleCmd(uint)));

    setWindowOpacity(0.9);  //透明度设置
    setStyleSheet("background-color:#CDC9C9");
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(800, 480);
}

/**
 * @brief 返回桌面
 */
void Desktop::returnDesktop()
{
    qDebug()<<"returnDesktop";
    //先发出命令让窗口隐藏
    if(qqProcedure->getState()){
        qqProcedure->sendCmd(PROCEDURE_HIDE);
    }
    QTimer::singleShot(100, this, SLOT(laterShowDesk()));
}

void Desktop::laterShowDesk()
{
    this->show();
}

/**
 * @brief 程序启动情况
 * @param ret
 */
void Desktop::startSlot(bool ret)
{
    qDebug()<<"start="<<ret;
    if(ret){  //启动成功
        Toast *w = new Toast(this, "procedure starting, wait...");
        w->toast();
        this->hide();  //启动成功后隐藏桌面
    }else{
        Toast *w = new Toast(this, "start err, please check");
        w->toast();
    }
}

/**
 * @brief 程序从后台转到前台
 */
void Desktop::enterProSlot()
{
    //1.桌面要隐藏
    this->hide();
    //2.子进程界面要显示,这个Procedure里已经处理
}

/**
 * @brief 处理来自APP的命令
 * @param cmd
 */
void Desktop::handleCmd(uint cmd)
{
    switch (cmd) {
    case PROCEDURE_HIDE:  //应用程序最小化或者隐藏了
        returnDesktop();
        break;
    default:
        break;
    }
}

