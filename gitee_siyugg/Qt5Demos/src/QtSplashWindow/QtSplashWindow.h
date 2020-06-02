/*************************************************************************
    > File Name: QtSplashWindow.h
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月18日 星期六 14时02分06秒
 ************************************************************************/

#ifndef QTSPLASHWINDOW_H
#define QTSPLASHWINDOW_H

#include <QSplashScreen>

class QPixmap;

class QtSplashWindow:public QSplashScreen
{
	Q_OBJECT
	private:
		QPixmap *pix;
	public:
		QtSplashWindow(QWidget *parent = 0);
		~QtSplashWindow();
};

#endif //QTSPLASHWINDOW_H
