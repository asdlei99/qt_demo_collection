/*************************************************************************
    > File Name: QtImageView.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年07月08日 星期五 22时32分36秒
 ************************************************************************/

#include <QWidget>
#include "QtImageView.h"
#include <QIcon>
#include <QMenuBar>
#include <QFileDialog>
#include <QPixmap>
#include <QSize>
#include <QPoint>
#include <QRect>
#include <QMatrix>
#include <QDebug>

QtImageView::QtImageView(QWidget *parent):QMainWindow(parent),zoomTimes(0),rotateTimes(0),matrix()
{
	img = new QImage;
	matrix = matrix.scale(1,1);
	qDebug()<<matrix;

	setAutoFillBackground(true);
	imageArea = new QScrollArea(this);
	imageDisLabel = new QLabel(this);
    imageDisLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	imageArea->setWidget(imageDisLabel);
	imageArea->setWidgetResizable(true);
	imageArea->setAutoFillBackground(true);

	createActions();
	createMenus();
	createToolBars();

    setCentralWidget(imageArea);
	resize(800,600);

	connect(openImgAction,SIGNAL(triggered()),this,SLOT(slot_open()));
	connect(saveImgAction,SIGNAL(triggered()),this,SLOT(slot_save()));
	connect(saveAsImgAction,SIGNAL(triggered()),this,SLOT(slot_saveAs()));
	connect(quitAction,SIGNAL(triggered()),this,SLOT(close()));
connect(zoomOutAction,SIGNAL(triggered()),this,SLOT(slot_zoomIn()));
	connect(zoomInAction,SIGNAL(triggered()),this,SLOT(slot_zoomOut()));
	connect(rotateLeftAction,SIGNAL(triggered()),this,SLOT(slot_rotateLeft()));
	connect(rotateRightAction,SIGNAL(triggered()),this,SLOT(slot_rotateRight()));
}
QtImageView::~QtImageView()
{

}

void QtImageView::createActions()
{
	openImgAction = new QAction(QIcon(":/icon/open.png"),tr("打开"),this);
	saveImgAction = new QAction(QIcon(":/icon/save.png"),tr("保存"),this);
	saveAsImgAction = new QAction(QIcon(":/icon/save-as.png"),tr("另存为"),this);

	quitAction = new QAction(QIcon(":/icon/quit.svg"),tr("退出"),this);
	zoomInAction = new QAction(QIcon(":/icon/zoom-in.png"),tr("缩小"),this);
	zoomOutAction = new QAction(QIcon(":/icon/zoom-out.png"),tr("放大"),this);
	rotateLeftAction = new QAction(QIcon(":/icon/rotate-left.png"),tr("向左旋转"),this);
	rotateRightAction = new QAction(QIcon(":/icon/rotate-right.png"),tr("向右旋转"),this);
}
void QtImageView::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("文件"));
	fileMenu->addAction(openImgAction);
	fileMenu->addAction(saveImgAction);
	fileMenu->addAction(saveAsImgAction);
	fileMenu->addSeparator();
	fileMenu->addAction(quitAction);

	editMenu = menuBar()->addMenu(tr("编辑"));
	editMenu->addAction(zoomInAction);
	editMenu->addAction(zoomOutAction);
	editMenu->addAction(rotateLeftAction);
	editMenu->addAction(rotateRightAction);
}
void QtImageView::createToolBars()
{
	fileToolBar = addToolBar(tr("文件"));
	fileToolBar->addAction(openImgAction);
	fileToolBar->addAction(saveImgAction);
	fileToolBar->addAction(saveAsImgAction);

	editToolBar = addToolBar(tr("编辑"));
	editToolBar->addAction(zoomInAction);
	editToolBar->addAction(zoomOutAction);
	editToolBar->addAction(rotateLeftAction);
	editToolBar->addAction(rotateRightAction);
}
void QtImageView::slot_open()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("打开文件"),"/home",tr("图片(*.jpg *.png *.jpeg *.bmp);;所有文件(*)"));

	img->load(fileName);
	imageDisLabel->setPixmap(QPixmap::fromImage(*img));
	imageArea->resize(img->size());
}
void QtImageView::slot_save()
{
	QString saveFile = QFileDialog::getSaveFileName(this,tr("保存文件"),".",tr("图片(*.jpg *.png *.bmp *.jpeg)"));
	imageDisLabel->pixmap()->save(saveFile);
}
void QtImageView::slot_saveAs()
{
	QString saveAsFile = QFileDialog::getSaveFileName(this,tr("文件另存为"),".",tr("图片(*.jpg *.png *.bmp *.jpeg)"));
	imageDisLabel->pixmap()->save(saveAsFile);
}
void QtImageView::slot_zoomIn()
{
	if (img->isNull())
		return;
	if (zoomTimes > 4)
		return;
	++zoomTimes;
	float tmpWidth = imageDisLabel->pixmap()->width() * 4.0 / 5.0;
	float tmpHeight = imageDisLabel->pixmap()->height() * 4.0 / 5.0;
	imageDisLabel->setPixmap(QPixmap::fromImage(img->scaled(tmpWidth,tmpHeight)));
	/*此处使用记录原始图像数据的变量img而不是直接对QLabel中显示的图像数据进行处理是为了在缩小和放大过程中出现失真,下面类似*/
}
void QtImageView::slot_zoomOut()
{
	if (img->isNull())
		return;
	if (zoomTimes < -4)
		return;
	--zoomTimes;
	int tmpWidth = imageDisLabel->pixmap()->width() * 5.0 / 4.0;
	int tmpHeight = imageDisLabel->pixmap()->height() * 5.0 / 4.0;
	imageDisLabel->setPixmap(QPixmap::fromImage(img->scaled(tmpWidth,tmpHeight)));
}
void QtImageView::slot_rotateLeft()
{
	if (img->isNull())
		return;
	++rotateTimes;//向左旋转90度，计数加一，向右减一
	QMatrix matrix;
	matrix.rotate((rotateTimes % 4) * 90);
	*img = img->transformed(matrix);
	imageDisLabel->setPixmap(QPixmap::fromImage(img->scaled(imageDisLabel->pixmap()->width(),imageDisLabel->pixmap()->height())));
}
void QtImageView::slot_rotateRight()
{
	if (img->isNull())
		return;
	--rotateTimes;
	QMatrix matrix;
	matrix.rotate((rotateTimes % 4) * 90);
	*img = img->transformed(matrix);
	imageDisLabel->setPixmap(QPixmap::fromImage(img->scaled(imageDisLabel->pixmap()->width(),imageDisLabel->pixmap()->height())));
}
