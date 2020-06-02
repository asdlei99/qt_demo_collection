/*************************************************************************
    > File Name: QtShapeWidget.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月18日 星期六 13时13分30秒
 ************************************************************************/

#include "QtShapeWidget.h"
#include <QBitmap>
#include <QPainter>
#include <QBrush>
#include <QPalette>

QtShapeWidget::QtShapeWidget(QWidget * parent):QDialog(parent),
	dragPositon()
{
	pix = new QPixmap;
	pix->load(":/image/1Whater.png");
	resize(pix->size());
	
/*	QPalette p = this->palette();
	p.setBrush(QPalette::Window,QBrush(pix));
	setPalette(p);*/
	setMask(QBitmap(pix->mask()));
}
QtShapeWidget::~QtShapeWidget()
{

}
void QtShapeWidget::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragPositon = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
	if (event->button() == Qt::RightButton)
		close();
}
void QtShapeWidget::mouseMoveEvent(QMouseEvent * event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		move(event->globalPos() - dragPositon);
		event->accept();
	}
}
void QtShapeWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap(0,0,*pix);
}
