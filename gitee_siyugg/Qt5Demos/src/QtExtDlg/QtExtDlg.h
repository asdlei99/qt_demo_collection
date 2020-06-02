/*************************************************************************
    > File Name: QtExtDlg.h
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月18日 星期六 10时35分07秒
 ************************************************************************/

#ifndef QTEXTDLG_H
#define QTEXTDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QFrame>
#include <QSlider>

class QtExtDlg : public QDialog
{
	Q_OBJECT
	private:
		QFrame *baseInfoFrame;
		QFrame *detailInfoFrame;
		QLabel *nameLabel;
		QLabel *sexLabel;
		QLabel *ageLabel;
		QLabel *departLabel;
		QLabel *emailLabel;
		QLineEdit *nameLineEdit;
		QComboBox *sexCombox;
		QSlider *ageSlider;
		QComboBox *departCombox;
		QLineEdit *emailLineEdit;
		QPushButton *okBtn;
		QPushButton *detailBtn;
	public:
		QtExtDlg(QWidget *parent = 0);
		~QtExtDlg();
	public slots:
		void slot_okBtnClicked();
		void slot_showDetail();
		void slot_ageChanged(int);
};

#endif //QTEXTDLG_H
