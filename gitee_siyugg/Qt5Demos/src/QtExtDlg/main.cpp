/*************************************************************************
    > File Name: main.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月18日 星期六 11时03分56秒
 ************************************************************************/

#include "QtExtDlg.h"
#include <QApplication>

int main(int argc,char **argv)
{
	QApplication a(argc,argv);

	QtExtDlg qDlg;
	qDlg.show();

	return a.exec();
}
