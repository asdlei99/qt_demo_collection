/*************************************************************************
    > File Name: main.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月18日 星期六 08时29分40秒
 ************************************************************************/

#include "QtClock.h"
#include <QApplication>

int main(int argc,char **argv)
{
	QApplication a(argc,argv);

	QtClock qClock;
	qClock.show();

	return a.exec();
}
