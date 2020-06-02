/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.30
 ** @brief:      动画承载界面
 */

#ifndef TIMETOTAL_H
#define TIMETOTAL_H

#include "timedisplay.h"
#include "timeset.h"
#include "zoneset.h"
#include "animationwidget.h"

class TimeTotal : public QWidget
{
    Q_OBJECT
public:
    explicit TimeTotal(QWidget *parent = 0);

signals:

public slots:
    void showZoneWigSlot();
    void showTimeSetWigSlot();
    void backSlot();

private slots:
    void setNewTimeSlot(const QDateTime &);

private:
    AnimationWidget *total;
    QList<QWidget *> list;
    TimeDisplay *timeDisplay;
    TimeSet *timeSet;
    ZoneSet *zoneSet;
    int curWig;
    static const int w=355;
    static const int h=200;
};

#endif // TIMETOTAL_H
