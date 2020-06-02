/*************************************************************************
    > File Name: QtGeometryDlg.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年07月08日 星期五 16时03分57秒
 ************************************************************************/

#include "QtGeometryDlg.h"
#include <QGridLayout>

QtGeometryDlg::QtGeometryDlg(QWidget *parent):QDialog(parent)
{
	xLabel = new QLabel(tr("x():"),this);
	yLabel = new QLabel(tr("y():"),this);
	posLabel = new QLabel(tr("pos():"),this);
	frameLabel = new QLabel(tr("frmae:"),this);
	geometryLabel = new QLabel(tr("geometryLabel():"),this);
	widthLabel = new QLabel(tr("width():"),this);
	heightLabel = new QLabel(tr("height():"),this);
	rectLabel = new QLabel(tr("rect():"),this);
	sizeLabel = new QLabel(tr("size():"),this);

	echo_xLabel = new QLabel(this);
	echo_yLabel = new QLabel(this);
	echo_posLabel = new QLabel(this);
	echo_frameLabel = new QLabel(this);
	echo_geometryLabel = new QLabel(this);
	echo_widthLabel = new QLabel(this);
	echo_heightLabel = new QLabel(this);
	echo_rectLabel = new QLabel(this);
	echo_sizeLabel = new QLabel(this);

	setStyleSheet("background-color:pink");

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(xLabel,0,0);
	mainLayout->addWidget(echo_xLabel,0,1);
	mainLayout->addWidget(yLabel,1,0);
	mainLayout->addWidget(echo_yLabel,1,1);
	mainLayout->addWidget(posLabel,2,0);
	mainLayout->addWidget(echo_posLabel,2,1);
	mainLayout->addWidget(frameLabel,3,0);
	mainLayout->addWidget(echo_frameLabel,3,1);
	mainLayout->addWidget(geometryLabel,4,0);
	mainLayout->addWidget(echo_geometryLabel,4,1);
	mainLayout->addWidget(widthLabel,5,0);
	mainLayout->addWidget(echo_widthLabel,5,1);
	mainLayout->addWidget(heightLabel,6,0);
	mainLayout->addWidget(echo_heightLabel,6,1);
	mainLayout->addWidget(rectLabel,7,0);
	mainLayout->addWidget(echo_rectLabel,7,1);
	mainLayout->addWidget(sizeLabel,8,0);
	mainLayout->addWidget(echo_sizeLabel,8,1);
	this->setLayout(mainLayout);

	update();
}
QtGeometryDlg::~QtGeometryDlg()
{

}
void QtGeometryDlg::update()
{
	QString xStr;
	echo_xLabel->setText(xStr.setNum(x()));
	QString yStr;
	echo_yLabel->setText(yStr.setNum(y()));

	QString tmp;

	QString posStr;
	posStr += tmp.setNum(pos().x());
	posStr += ",";
	posStr += tmp.setNum(pos().y());
	echo_posLabel->setText(posStr);

	QString frameStr;
	frameStr += tmp.setNum(frameGeometry().x());
	frameStr += ",";
	frameStr += tmp.setNum(frameGeometry().y());
	frameStr += ",";
	frameStr += tmp.setNum(frameGeometry().width());
	frameStr += ",";
	frameStr += tmp.setNum(frameGeometry().height());
	echo_frameLabel->setText(frameStr);

	QString geoStr;
	geoStr += tmp.setNum(geometry().x());
	geoStr += ",";
	geoStr += tmp.setNum(geometry().y());
	geoStr += ",";
	geoStr += tmp.setNum(geometry().width());
	geoStr += ",";
	geoStr += tmp.setNum(geometry().height());
	echo_geometryLabel->setText(geoStr);

	QString widthStr;
	echo_widthLabel->setText(widthStr.setNum(width()));

	QString heightStr;
	echo_heightLabel->setText(heightStr.setNum(height()));

	QString rectStr;
	rectStr += tmp.setNum(rect().x());
	rectStr += ",";
	rectStr += tmp.setNum(rect().y());
	rectStr += ",";
	rectStr += tmp.setNum(rect().width());
	rectStr += ",";
	rectStr += tmp.setNum(rect().height());
	echo_rectLabel->setText(rectStr);

	QString sizeStr;
	sizeStr += tmp.setNum(size().width());
	sizeStr += ",";
	sizeStr += tmp.setNum(size().height());
	echo_sizeLabel->setText(sizeStr);
}
void QtGeometryDlg::moveEvent(QMoveEvent *)
{
	update();
}
void QtGeometryDlg::resizeEvent(QResizeEvent *)
{
	update();
}
