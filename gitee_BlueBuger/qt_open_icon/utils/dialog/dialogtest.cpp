/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.23
 ** @brief:      消息对话框
 */
#include "dialogtest.h"

DialogTest::DialogTest()
{
    QVBoxLayout *lay = new QVBoxLayout(this);

    QPushButton *toastBtn = new QPushButton("toast");
    QPushButton *waningBtn = new QPushButton("确认消息框");
    QPushButton *messageBtn = new QPushButton("提示框");

    lay->addWidget(toastBtn);
    lay->addWidget(waningBtn);
    lay->addWidget(messageBtn);

    connect(toastBtn,SIGNAL(released()),this,SLOT(toastSlot()));
    connect(waningBtn,SIGNAL(released()),this,SLOT(warningSlot()));
    connect(messageBtn,SIGNAL(released()),this,SLOT(messageSlot()));

    setFixedSize(300, 300);
}


void DialogTest::toastSlot()
{
    Toast *w = new Toast(this, "这是一个好的组件库");
    w->toast();
}

void DialogTest::warningSlot()
{
    Toast *toast;
    QString qss = utilscommon::readFile(":/qss/resourse/qss/dialog/default.qss");
    BaseLabel *labIcon = new BaseLabel(FontawesomeWebfont(), FontawesomeWebfont::ICON_WAINING, 20, 20);
    BaseMessageBox *w = new BaseMessageBox(labIcon, "警告", "确定删除？", qss);
    switch (w->exec()) {
    case BaseMessageBox::OK:
        toast = new Toast(this, "选择了确定");
        toast->toast();
        break;
    default:
        toast = new Toast(this, "选择了取消");
        toast->toast();
        break;
    }
}

void DialogTest::messageSlot()
{
    QString qss = utilscommon::readFile(":/qss/resourse/qss/dialog/default.qss");
    BaseLabel *labIcon = new BaseLabel(FontawesomeWebfont(), FontawesomeWebfont::ICON_INFO, 20, 20);
    BaseMessageBox *w = new BaseMessageBox(labIcon, "提示", "这是个好的组件库", qss, false);
    w->show();
}
