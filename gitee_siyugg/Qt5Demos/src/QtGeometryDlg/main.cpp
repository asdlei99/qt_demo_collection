/*************************************************************************
    > File Name: main.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年07月08日 星期五 16时24分29秒
 ************************************************************************/

#include "QtGeometryDlg.h"
#include <QApplication>

int main(int argc,char **argv)
{
	QApplication a(argc,argv);
	QtGeometryDlg dlg;
	dlg.show();
	return a.exec();
}
