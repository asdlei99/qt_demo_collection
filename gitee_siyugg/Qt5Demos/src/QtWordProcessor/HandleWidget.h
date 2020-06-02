/*************************************************************************
    > File Name: HandleWidget.h
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月18日 星期六 21时46分19秒
 ************************************************************************/
#ifndef HANDLE_WIDGET_H
#define HANDLE_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>

class HandleWidget:public QWidget
{
	Q_OBJECT
	private:
		QLabel *imageLabel;
		QTextEdit *textEdit;
	public:
		HandleWidget(QWidget *parent = 0);
		~HandleWidget();
		void load_file(QString);
		QTextEdit* text() const
		{
			return textEdit;
		}
		QLabel* image() const
		{
			return imageLabel;
		}
};

#endif//HANDLE_WIDGET_H
