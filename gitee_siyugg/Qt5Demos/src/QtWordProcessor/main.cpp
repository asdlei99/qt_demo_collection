/*************************************************************************
    > File Name: main.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月18日 星期六 15时28分22秒
 ************************************************************************/

#include <QApplication>
#include "QtWordProcessor.h"

int main(int argc,char **argv)
{
	QApplication a(argc,argv);
	
	QtWordProcessor pro;

	return a.exec();
}
