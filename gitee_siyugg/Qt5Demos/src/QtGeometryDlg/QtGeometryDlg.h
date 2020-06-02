/*************************************************************************
    > File Name: QtGeometryDlg.h
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年07月08日 星期五 16时03分57秒
 ************************************************************************/
#ifndef QTGEOMETRYDLG_H
#define QTGEOMETRYDLG_H

#include <QDialog>
#include <QLabel>
#include <QMoveEvent>
#include <QResizeEvent>

class QtGeometryDlg : public QDialog
{
	Q_OBJECT
	private:
		QLabel *xLabel;
		QLabel *yLabel;
		QLabel *posLabel;
		QLabel *frameLabel;
		QLabel *geometryLabel;
		QLabel *widthLabel;
		QLabel *heightLabel;
		QLabel *rectLabel;
		QLabel *sizeLabel;
		
		QLabel *echo_xLabel;
		QLabel *echo_yLabel;
		QLabel *echo_posLabel;
		QLabel *echo_frameLabel;
		QLabel *echo_geometryLabel;
		QLabel *echo_widthLabel;
		QLabel *echo_heightLabel;
		QLabel *echo_rectLabel;
		QLabel *echo_sizeLabel;
	public:
		QtGeometryDlg(QWidget *parent = NULL);
		~QtGeometryDlg();

		void update();
		void moveEvent(QMoveEvent*);
		void resizeEvent(QResizeEvent*);
};

#endif
