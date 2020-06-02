/*************************************************************************
    > File Name: main.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年07月08日 星期五 23时09分04秒
 ************************************************************************/

#include "QtImageView.h"
#include <QApplication>

int main(int argc,char **argv)
{
	QApplication a(argc,argv);

	QtImageView view;
	view.show();
	return a.exec();
}
