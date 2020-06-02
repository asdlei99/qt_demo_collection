/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.30
 ** @brief:      时间日期设置
 */

#include "timeset.h"

/**
 * @brief 首次初始化为当前时间
 */
TimeSet::TimeSet(const QDateTime &curTime)
{
    //标题栏
    head = new HeadUtils("时间设置");
    connect(head, SIGNAL(backSignal()), this, SLOT(backSlot()));

    createStringList(curTime);

    //日期选择栏
    dateWheel = new StringWheelWidget();
    dateWheel->setFixedSize(115, wheelH);
    dateWheel->setItems(dateList);

    //小时
    hourWheel = new StringWheelWidget();
    hourWheel->setFixedSize(30, wheelH);
    hourWheel->setItems(hourList);

    //分钟
    miniteWheel = new StringWheelWidget();
    miniteWheel->setFixedSize(35, wheelH);
    miniteWheel->setItems(miniteList);

    //中间界面
    QWidget *centerWig = new QWidget();
    QHBoxLayout *centerLay = new QHBoxLayout(centerWig);
    centerLay->setMargin(0);
    centerLay->setSpacing(0);
    centerLay->addWidget(dateWheel);
    centerLay->addWidget(hourWheel);
    centerLay->addWidget(miniteWheel);
    centerWig->setFixedSize(180, wheelH);

    //更改窗口字体大小
    QFont f = centerWig->font();
    f.setPointSize(f.pointSize() * 1.5);
    dateWheel->setFont(f);
    hourWheel->setFont(f);
    miniteWheel->setFont(f);

    //中间界面过渡界面
    QWidget *centerTmpWig = new QWidget();
    centerTmpWig->setFixedSize(w, wheelH);
    QHBoxLayout *tmpLay = new QHBoxLayout(centerTmpWig);
    tmpLay->addWidget(centerWig, 0, Qt::AlignCenter);
    tmpLay->setMargin(0);
    tmpLay->setSpacing(0);

    //整体布局
    QVBoxLayout *totalLay = new QVBoxLayout(this);
    totalLay->addWidget(head);
    totalLay->addWidget(centerTmpWig);
    totalLay->setMargin(0);
    totalLay->setSpacing(0);

    setStyleSheet("background-color:#FFFFFF;");
    setFixedSize(w, h);
}

/**
 * @brief 生成当年的各个显示链表
 */
void TimeSet::createStringList(const QDateTime &curTime)
{
    curHour = curTime.time().hour();
    curMinite = curTime.time().minute();
    //日期链表
    QDate nextDay, preDay;
    curDate = curTime.date();
    dateList.append(curDate.toString("MM-dd dddd"));
    nextDay = curDate.addDays(1);
    preDay = curDate.addDays(-1);
    curYear = curDate.year();
    while(curYear == nextDay.year()){
        dateList.append(nextDay.toString("MM-dd dddd"));
        nextDay = nextDay.addDays(1);
    }

    todayIndex=0;
    while(curYear == preDay.year()){
        dateList.prepend(preDay.toString("MM-dd dddd"));
        preDay = preDay.addDays(-1);
        todayIndex++;
    }


    //小时链表
    QString str;
    for(int i=0; i<24; i++){
        hourList.append(str.number(i));
    }

    //分钟链表
    miniteList << "00" <<"01" <<"02" <<"03" <<"04" <<"05" <<"06" <<"07" <<"08" <<"09";
    for(int i=10; i<=59; i++){
        miniteList.append(str.number(i));
    }
}

/**
 * @brief 返回就表示设置新时间
 */
void TimeSet::backSlot()
{
    QString str;
    QDate newDate = QDate::fromString(str.number(curYear), "yyyy").\
            addDays(dateWheel->currentIndex());
    int gapSec = hourWheel->currentIndex()*3600 \
            + miniteWheel->currentIndex()*60;
    QDateTime newTime = QDateTime(newDate).addSecs(gapSec);

    emit setNewTimeSig(newTime);
    emit backDisp();
}

/**
 * @brief 更新中央当前时间
 * @param datIndex 一年第几天
 * @param hourIndex 时
 * @param miniteIndex 分
 */
void TimeSet::setNewCurrent(int dayIndex, int hourIndex, int miniteIndex)
{
    dateWheel->setCurrentIndex(dayIndex);
    hourWheel->setCurrentIndex(hourIndex);
    miniteWheel->setCurrentIndex(miniteIndex);
}
