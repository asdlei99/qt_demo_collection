/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.30
 ** @brief:      动画承载界面
 */

#include "timetotal.h"

#define BACK_GROUND QString("background-image: url(:/images/resourse/images/animation/")

TimeTotal::TimeTotal(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(w, h);

    timeDisplay = new TimeDisplay;
    timeSet = new TimeSet(timeDisplay->getCurTime());
    zoneSet = new ZoneSet;

    list.append(timeDisplay);
    list.append(zoneSet);
    list.append(timeSet);

    total = new AnimationWidget(list, "cover", 200, QEasingCurve::OutQuad);
    total->setParent(this);
    total->raise(0);

    connect(timeDisplay, SIGNAL(showZoneWig()), this, SLOT(showZoneWigSlot()));
    connect(timeDisplay, SIGNAL(showTimeSetWig()), this, SLOT(showTimeSetWigSlot()));
    connect(timeSet, SIGNAL(backDisp()), this, SLOT(backSlot()));
    connect(timeSet, SIGNAL(setNewTimeSig(const QDateTime &)),\
            this, SLOT(setNewTimeSlot(const QDateTime &)));
    connect(zoneSet, SIGNAL(backDisp()), this, SLOT(backSlot()));

    setStyleSheet("background-color:#FFFFFF;");
}

void TimeTotal::showZoneWigSlot()
{
    total->animationShow(1, AnimationWidget::ANIMATION_LEFT);
}

void TimeTotal::showTimeSetWigSlot()
{
    //显示之前先把当前时间更新到设置界面
    QDateTime curTime = timeDisplay->getCurTime();
    //计算下当前日期到当前年1月1日的天数
    QDate d(curTime.date().year(), 1, 1);
    timeSet->setNewCurrent(d.daysTo(curTime.date()), \
                           curTime.time().hour(), curTime.time().minute());

    total->animationShow(2, AnimationWidget::ANIMATION_LEFT);
}

void TimeTotal::backSlot()
{
    total->animationShow(0, AnimationWidget::ANIMATION_RIGHT);
}

void TimeTotal::setNewTimeSlot(const QDateTime &newTime)
{
    timeDisplay->updateDispTime(newTime);
    Toast *w = new Toast(this, "修改时间成功", 160, 20);
    w->toast();
}
