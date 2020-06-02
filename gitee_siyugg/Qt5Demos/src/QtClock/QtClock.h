/*************************************************************************
    > File Name: QtClock.h
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月18日 星期六 08时08分39秒
 ************************************************************************/

#ifndef QCLOCK_H
#define QCLOCK_H

#include <QLCDNumber>
#include <QPoint>

//鼠标事件和键盘事件类的前置声明
class QMouseEvent;
class QKeyEvent;

class QtClock : public QLCDNumber
{
	Q_OBJECT
	private :
		QPoint dragPosition;
		bool isShowColon;
	public:
		QtClock(QWidget *parent = 0);
		~QtClock();
		void mousePressEvent(QMouseEvent *);
		void mouseMoveEvent(QMouseEvent *);
		void keyPressEvent(QKeyEvent *);
	public slots:
		void slot_showTime();
};

#endif //QCLOCK_H
