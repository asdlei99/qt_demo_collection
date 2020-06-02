/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.29
 ** @brief:      时间日期显示界面
 */

#include "timedisplay.h"

#define LABEL_STYLE "\
QLabel{\
    color:#000000;\
    font:bold;\
}\
"

#define DISP_BUTTON_STYLE "\
QPushButton{\
    color:#0000FF;\
    border:0px;\
}\
QPushButton:pressed{\
    color:#00F5FF;\
}\
"

#define DISABLE_BUTTON_STYLE "\
QPushButton{\
    color:#6E6E6E;\
    border:0px;\
}\
"

TimeDisplay::TimeDisplay(QWidget *parent) :
    QWidget(parent),
    is24Fmt(true),
    isAuto(true),
    isFirst(true)
{
    head = new HeadUtils("时间和日期");
    setFixedSize(355, 200);

    hourFormatLab = new QLabel("24小时制");
    hourFormatLab->setStyleSheet(LABEL_STYLE);
    hourFormatBtn = new CSwitchWidget();
    hourFormatBtn->setFixedSize(80, 25);

    autoTimeLab = new QLabel("自动获取时间");
    autoTimeLab->setStyleSheet(LABEL_STYLE);
    autoTimeBtn = new CSwitchWidget();
    autoTimeBtn->setFixedSize(80, 25);

    zoneLab = new QLabel("时区");
    zoneLab->setStyleSheet(LABEL_STYLE);
    zoneDispBtn = new QPushButton("GMT+8:00 北京");
    zoneDispBtn->setFocusPolicy(Qt::NoFocus);
    zoneDispBtn->setStyleSheet(DISP_BUTTON_STYLE);

    dateTimeLab = new QLabel("日期和时间");
    dateTimeLab->setStyleSheet(LABEL_STYLE);
    dateTimeDispBtn = new QPushButton("2016-5-25 18：21");
    dateTimeDispBtn->setFocusPolicy(Qt::NoFocus);
    dateTimeDispBtn->setStyleSheet(DISP_BUTTON_STYLE);

    QWidget *contentWig = new QWidget;
    contentWig->setFixedSize(355, 165);
    QGridLayout *grid = new QGridLayout(contentWig);
    grid->addWidget(hourFormatLab, 0, 0, Qt::AlignLeft);
    grid->addWidget(hourFormatBtn, 0, 1, Qt::AlignRight);
    grid->addWidget(autoTimeLab, 1, 0, Qt::AlignLeft);
    grid->addWidget(autoTimeBtn, 1, 1, Qt::AlignRight);
    grid->addWidget(zoneLab, 2, 0, Qt::AlignLeft);
    grid->addWidget(zoneDispBtn, 2, 1, Qt::AlignRight);
    grid->addWidget(dateTimeLab, 3, 0, Qt::AlignLeft);
    grid->addWidget(dateTimeDispBtn, 3, 1, Qt::AlignRight);

    grid->setSpacing(10);
    grid->setMargin(10);

    QVBoxLayout *totalLay = new QVBoxLayout(this);
    totalLay->addWidget(head);
    totalLay->addWidget(contentWig);
    totalLay->setSpacing(0);
    totalLay->setMargin(0);
    setStyleSheet("background-color:#FFFFFF;");

    connect(zoneDispBtn, SIGNAL(released()), this, SLOT(showZoneWigSlot()));
    connect(dateTimeDispBtn, SIGNAL(released()), this, SLOT(showTimeSetWigSlot()));
    connect(autoTimeBtn, SIGNAL(StateChanged(int)), this, SLOT(syncTime(int)));
    connect(hourFormatBtn, SIGNAL(StateChanged(int)), this, SLOT(timeFmtChange(int)));

    updateTimer = new QTimer();
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateTime()));

    syncTime(0); //先更新一次时间

}

/**
 * @brief 同步时间
 */
void TimeDisplay::syncTime(int state)
{
    if(state == 0){  //自动获取打开
        isAuto = true;
        zoneDispBtn->setStyleSheet(DISABLE_BUTTON_STYLE);
        dateTimeDispBtn->setStyleSheet(DISABLE_BUTTON_STYLE);
        updateDispTime(QDateTime::currentDateTime());
        if(!isFirst){
            Toast *w = new Toast(this, "时间已更新", 180, 20);
            w->toast();
        }
        isFirst = false;  //以后打开自动更新就会提示了
    }else{  //自动获取关闭
        zoneDispBtn->setStyleSheet(DISP_BUTTON_STYLE);
        dateTimeDispBtn->setStyleSheet(DISP_BUTTON_STYLE);
        isAuto = false;
    }
}

/**
 * @brief 根据24小时制式按钮状态更改时间显示格式
 */
void TimeDisplay::timeFmtChange(int state)
{
    QString str;
    state? is24Fmt=false : is24Fmt=true;
    QDateTime time = QDateTime::currentDateTime();
    if(is24Fmt){  //24小时制
        str = time.toString("yyyy-MM-dd hh:mm"); //设置显示格式
    }else{
        str = time.toString("yyyy-MM-dd hh:mm ap"); //设置显示格式
    }

    dateTimeDispBtn->setText(str);
}

void TimeDisplay::showZoneWigSlot()
{
    if(!isAuto){  //自动获取关闭，可以更改时区
        emit showZoneWig();
    }else{
        Toast *w = new Toast(this, "请先关闭自动获取时间", 180, 20);
        w->toast();
    }
}

void TimeDisplay::showTimeSetWigSlot()
{
    if(!isAuto){
        emit showTimeSetWig();
    }else{
        Toast *w = new Toast(this, "请先关闭自动获取时间", 180, 20);
        w->toast();
    }
}

/**
 * @brief 每60s更新一次时间
 */
void TimeDisplay::updateTime()
{
    curTime = curTime.addSecs(60);
    updateDispTime(curTime);
}

/**
 * @brief 设置新的时间显示
 * @param newTime
 */
void TimeDisplay::updateDispTime(const QDateTime &newTime)
{
    QString str;
    if(is24Fmt){  //24小时制
        str = newTime.toString("yyyy-MM-dd hh:mm"); //设置显示格式
    }else{
        str = newTime.toString("yyyy-MM-dd hh:mm ap"); //设置显示格式
    }
    dateTimeDispBtn->setText(str);
    //时间更新完后由软件自动更新时间
    curTime = newTime;
    updateTimer->start(60000);
}
