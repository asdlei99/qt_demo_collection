/*************************************************************************
    > File Name: QtImageView.h
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年07月08日 星期五 22时32分36秒
 ************************************************************************/

#ifndef QIMAGEVIEW_H
#define QIMAGEVIEW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>
#include <QAction>
#include <QToolBar>
#include <QMenu>
#include <QImage>
#include <QMatrix>

class QtImageView:public QMainWindow
{
	Q_OBJECT
	private:
		QImage *img;
		int zoomTimes;//控制放大倍数，以免出现内存问题
		int rotateTimes;//记录旋转次数
		QMatrix matrix;

		QScrollArea *imageArea;
		QLabel *imageDisLabel;

		QMenu *fileMenu;
		QMenu *editMenu;

		QToolBar *fileToolBar;
		QToolBar *editToolBar;

		QAction *openImgAction;
		QAction *saveImgAction;
		QAction *saveAsImgAction;

		QAction *quitAction;

		QAction *zoomInAction;
		QAction *zoomOutAction;
		QAction *rotateLeftAction;
		QAction *rotateRightAction;

	public:
		QtImageView(QWidget *parent = NULL);
		~QtImageView();

		void createActions();
		void createMenus();
		void createToolBars();
	public slots:
		void slot_open();
		void slot_save();
		void slot_saveAs();
		void slot_zoomIn();
		void slot_zoomOut();
		void slot_rotateLeft();
		void slot_rotateRight();
};

#endif
