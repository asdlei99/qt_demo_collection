/*************************************************************************
    > File Name: QtClock.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月18日 星期六 08时17分55秒
 ************************************************************************/

#include "QtClock.h"
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <QKeyEvent>

QtClock::QtClock(QWidget *parent):QLCDNumber(parent),
	dragPosition(),isShowColon(true)
{
	this->setStyleSheet("color:blue;background-color:rgba(0,0,0,255)");
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowOpacity(0.5);
	this->setToolTip("点击右键或按ESC键退出");

	QTimer *timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(slot_showTime()));
	timer->start(1000);
	slot_showTime();
	resize(150,60);
}
QtClock::~QtClock()
{

}
void QtClock::slot_showTime()
{
	QTime time = QTime::currentTime();
	QString text = time.toString("hh:mm");
	if (isShowColon)
	{
		text[2] = ':';
		isShowColon = false;
	}
	else 
	{
		text[2] = ' ';
		isShowColon = true;
	}
	display(text);
}
void QtClock::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		dragPosition = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
	if (event->buttons() == Qt::RightButton)
		close();
}
void QtClock::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		move(event->globalPos() - dragPosition);
		event->accept();
	}
}
void QtClock::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
		close();
}
