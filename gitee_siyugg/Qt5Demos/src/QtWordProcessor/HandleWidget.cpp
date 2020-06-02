/*************************************************************************
    > File Name: HandleWidget.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月18日 星期六 21时46分19秒
 ************************************************************************/

#include "HandleWidget.h"
#include <QLayout>
#include <QPixmap>
#include <QPalette>
#include <QBrush>
#include <QFile>
#include <QTextStream>

HandleWidget::HandleWidget(QWidget *parent):QWidget(parent),
	imageLabel(new QLabel(this)),textEdit(new QTextEdit(this))
{
	//QPixmap pix(":/image/beauty.png");
	QPixmap pix;
	/*QPalette p = imageLabel->palette();
	p.setBrush(QPalette::Window,QBrush(pix));
	imageLabel->setPalette(p);
	imageLabel->resize(pix.size());*/
	//imageLabel->setStyleSheet("border-image:url(:/image/beauty.png);border:0px");
	imageLabel->setScaledContents(true);
	imageLabel->setPixmap(pix);
	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addWidget(imageLabel);
	mainLayout->addWidget(textEdit);
	setLayout(mainLayout);
}
HandleWidget::~HandleWidget()
{

}
void HandleWidget::load_file(QString fileName)
{
	QFile file(fileName);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream textStream(&file);
		while(!textStream.atEnd())
		{
			textEdit->append(textStream.readLine());
		}
	}
}
