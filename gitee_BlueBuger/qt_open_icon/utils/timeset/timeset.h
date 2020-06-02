/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.30
 ** @brief:      时间日期设置
 */

#ifndef TIMESET_H
#define TIMESET_H

#include "headutils.h"
#include "stringwheelwidget.h"

class TimeSet : public QWidget
{
    Q_OBJECT
public:
    explicit TimeSet(const QDateTime &curTime);
    void setNewCurrent(int dayIndex, int hourIndex, int miniteIndex);

signals:
    void backDisp();
    void setNewTimeSig(const QDateTime &newTime);

private slots:
    void backSlot();

private:
    void createStringList(const QDateTime &curTime);

    HeadUtils *head;
    StringWheelWidget *dateWheel;
    StringWheelWidget *hourWheel;
    StringWheelWidget *miniteWheel;

    QStringList dateList;  //日期列表
    QStringList hourList; //小时列表
    QStringList miniteList; //分钟列表

    int curYear, curHour, curMinite;
    int todayIndex;
    QDate curDate;
    static const int w = 355;
    static const int h = 200;
    static const int wheelH = 165;
};

#endif // TIMESET_H
