/*************************************************************************
    > File Name: main.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月18日 星期六 14时11分15秒
 ************************************************************************/

#include <QMainWindow>
#include <QApplication>
#include "QtSplashWindow.h"

int main(int argc,char **argv)
{
	QApplication a(argc,argv);

	QtSplashWindow qsWin;
	qsWin.show();
	a.processEvents();

	//QMainWindow win;
	//win.show();
	//qsWin.finish(&win);

	return a.exec();
}
