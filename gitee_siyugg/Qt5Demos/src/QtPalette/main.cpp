/*************************************************************************
    > File Name: main.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月16日 星期四 18时04分03秒
 ************************************************************************/

#include <QApplication>
#include "QtPaletteDlg.h"
int main(int argc,char **argv)
{
	QApplication a(argc,argv);
	
	QtPaletteDlg palDlg;
	palDlg.show();

	return a.exec();
}
