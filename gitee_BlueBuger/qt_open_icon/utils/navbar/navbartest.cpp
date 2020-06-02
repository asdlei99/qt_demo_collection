#include "navbartest.h"

#define LEFT_STYLE "\
QPushButton{\
    color:#3A5FCD;\
    font:25px;\
    border:0px;\
    border-radius:0;\
    background-color:#E3E3E3;\
}\
QPushButton:pressed{\
    color:#79CDCD;\
    background-color:#E3E3E3;\
}\
"

#define CENTER_STYLE "\
QLabel{\
    color:#000000;\
    background-color:#E3E3E3;\
}\
"

#define RIGHT_STYLE "\
QPushButton{\
    color:#3A5FCD;\
    font:20px;\
    border:0px;\
    border-radius:0;\
    background-color:#E3E3E3;\
}\
QPushButton:pressed{\
    color:#79CDCD;\
    background-color:#E3E3E3;\
}\
"

#define TMP_STYLE "\
QPushButton{\
    color:#3A5FCD;\
    border:0px;\
    border-radius:0;\
    background-color:#E3E3E3;\
}\
QPushButton:pressed{\
    color:#79CDCD;\
    background-color:#E3E3E3;\
}\
"

NavBarTest::NavBarTest(QWidget *parent) :
    QWidget(parent)
{
    QLabel *centerLab1 = new QLabel("仅标题");
    centerLab1->setStyleSheet(CENTER_STYLE);
    Navbar *bar1 = new Navbar(300, 30, NULL, centerLab1, NULL);

    QLabel *centerLab2 = new QLabel("加返回按钮");
    centerLab2->setStyleSheet(CENTER_STYLE);
    BaseButton *lbtn1 = new BaseButton(TimeFont(), TimeFont::ICON_BACK, 30, 30, LEFT_STYLE);
    connect(lbtn1, SIGNAL(btnReleased()), this, SLOT(lReleased()));
    Navbar *bar2 = new Navbar(300, 30, lbtn1, centerLab2, NULL);

    BaseButton *btn = new BaseButton();
    btn->setText("编辑");
    btn->setStyleSheet(TMP_STYLE);
    QLabel *centerLab3 = new QLabel("加功能按钮");
    centerLab3->setStyleSheet(CENTER_STYLE);
    Navbar *bar3 = new Navbar(300, 30, NULL, centerLab3, btn);

    QLabel *centerLab4 = new QLabel("完全展示");
    centerLab4->setStyleSheet(CENTER_STYLE);
    BaseButton *lbtn4 = new BaseButton(TimeFont(), TimeFont::ICON_BACK, 30, 30, LEFT_STYLE);
    connect(lbtn4, SIGNAL(btnReleased()), this, SLOT(lReleased()));
    BaseButton *rbtn4 = new BaseButton(TimeFont(), TimeFont::ICON_DATE, 30, 30, RIGHT_STYLE);
    connect(lbtn4, SIGNAL(btnReleased()), this, SLOT(rReleased()));
    Navbar *bar4 = new Navbar(300, 30, lbtn4, centerLab4, rbtn4);

    QVBoxLayout *lay = new QVBoxLayout(this);

    lay->addWidget(bar1);
    lay->addWidget(bar2);
    lay->addWidget(bar3);
    lay->addWidget(bar4);
}

void NavBarTest::lReleased()
{
    qDebug()<<"lReleased";
}

void NavBarTest::rReleased()
{
    qDebug()<<"rReleased";
}
