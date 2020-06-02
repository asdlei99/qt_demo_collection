/**
 ** @author:	   浓咖啡
 ** @date:	   2015.4.18
 ** @brief:     动画演示窗口，注意要把三幅图路径配置好
 */

#include "animationtest.h"

#define BACK_GROUND QString("background-image: url(:/images/resourse/images/animation/")

AnimationTest::AnimationTest(QWidget *parent) :
    QMainWindow(parent)
{
    initMenuBar();
    initToolBar();
    initCenterWidget();
    initStatusBar();
    initConnect();
}

void AnimationTest::initMenuBar()
{
    menuAnimation = new QMenu("动画样式", this);
    actSlide = menuAnimation->addAction("滑动");
    actCover = menuAnimation->addAction("覆盖");
    actCenter = menuAnimation->addAction("中心进入");
    actFly = menuAnimation->addAction("飞入");
    actSharp = menuAnimation->addAction("对角");

    QMenuBar *bar = menuBar();
    bar->addMenu(menuAnimation);
}

void AnimationTest::initToolBar()
{
    toolBar = new QToolBar(this);
    up = new QAction(QString("上一页"), toolBar);
    down = new QAction(QString("下一页"), toolBar);

    toolBar->addAction(up);
    toolBar->addAction(down);
    addToolBar(Qt::TopToolBarArea, toolBar);
}

void AnimationTest::initCenterWidget()
{
    wig1 = new QWidget();
    wig1->setStyleSheet(BACK_GROUND + "1.PNG)");
    wig1->resize(w, h);
    wig2 = new QWidget();
    wig2->setStyleSheet(BACK_GROUND + "2.PNG)");
    wig2->resize(w, h);
    wig3 = new QWidget();
    wig3->setStyleSheet(BACK_GROUND + "3.PNG)");
    wig3->resize(w, h);

    list.append(wig1);
    list.append(wig2);
    list.append(wig3);

    //默认动画是slide
    center = new AnimationWidget(list, "slide");
    center->raise(0);
    curWig = 0;
    center->setFixedSize(w, h);
    setCentralWidget(center);
}

void AnimationTest::initStatusBar()
{
    QStatusBar *bar = statusBar();
    status = new QLabel("slide");
    status->setFrameShadow(QFrame::Sunken);
    status->setFrameShape(QFrame::WinPanel);
    bar->addWidget(status);
}

void AnimationTest::initConnect()
{
    connect(center, SIGNAL(animationFinshed()), this, SLOT(finishSlot()));

    connect(up, SIGNAL(triggered()), this, SLOT(upSlot()));
    connect(down, SIGNAL(triggered()), this, SLOT(downSlot()));

    connect(actSlide, SIGNAL(triggered()), this, SLOT(changeToSlide()));
    connect(actCover, SIGNAL(triggered()), this, SLOT(changeToCover()));
    connect(actCenter, SIGNAL(triggered()), this, SLOT(changeToCenter()));
    connect(actFly, SIGNAL(triggered()), this, SLOT(changeToFly()));
    connect(actSharp, SIGNAL(triggered()), this, SLOT(changeToSharp()));
}

void AnimationTest::upSlot()
{
    if(curWig <= 0){
        return;
    }
    //获取锁，保证动画完成后才进行下次动作
    if(center->getAnimation()->tryLock()){
        curWig--;
        center->animationShow(curWig, AnimationWidget::ANIMATION_LEFT);
    }
}

void AnimationTest::downSlot()
{
    if(curWig >= list.length()-1){
        return;
    }
    if(center->getAnimation()->tryLock()){
        curWig++;
        center->animationShow(curWig, AnimationWidget::ANIMATION_RIGHT);
    }
}

void AnimationTest::finishSlot()
{
    center->getAnimation()->unlock();
}

void AnimationTest::changeToSlide()
{
    center->setNewAnimation("slide");
    status->setText("slide");
}

void AnimationTest::changeToCover()
{
    center->setNewAnimation("cover");
    status->setText("cover");
}

void AnimationTest::changeToCenter()
{
    center->setNewAnimation("center");
    status->setText("center");
}

void AnimationTest::changeToFly()
{
    center->setNewAnimation("fly");
    status->setText("fly");
}


void AnimationTest::changeToSharp()
{
    center->setNewAnimation("sharp");
    status->setText("sharp");
}
