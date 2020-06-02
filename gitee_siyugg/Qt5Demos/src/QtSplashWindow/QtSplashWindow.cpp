/*************************************************************************
    > File Name: QtSplashWindow.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月18日 星期六 14时05分19秒
 ************************************************************************/

#include "QtSplashWindow.h"
#include <QPixmap>
#include <QMatrix>
#include <QStyle>
#include <QIcon>

QtSplashWindow::QtSplashWindow(QWidget *parent):QSplashScreen(parent),
	pix(new QPixmap(":/image/power_003.png"))
{
//	setPixmap(*pix);
	QMatrix matrix;
	matrix.rotate(15);
	setPixmap(pix->transformed(matrix));
}
QtSplashWindow::~QtSplashWindow()
{
	delete pix;
}

