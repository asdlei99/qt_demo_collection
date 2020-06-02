/*************************************************************************
    >
	File Name: QtPaletteDlg.h
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月16日 星期四 13时39分18秒
 ************************************************************************/

#ifndef QTPALETTEDLG_H
#define QTPALETTEDLG_H

#include <QFrame>
#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>

class QtPaletteDlg : public QDialog
{
	Q_OBJECT
	private:
		QFrame *crtlFrame;
		QFrame *displayFrame;
		QLabel *winPaletteLabel;
		QLabel *winTextPaletteLabel;
		QLabel *btnPaletteLabel;
		QLabel *btnTextPaletteLabel;
		QLabel *basePaletteLabel;
		QLabel *textPaletteLabel;
		QLabel *winText;
		QComboBox *winPaletteCombox;
		QComboBox *winTextPaletteCombox;
		QComboBox *btnPaletteCombox;
		QComboBox *btnTextPaletteCombox;
		QComboBox *basePaletteCombox;
		QComboBox *textPaletteCombox;
		QPushButton *displayBtn;
		QLineEdit *textEdit;
	public:
		QtPaletteDlg(QWidget *parent = 0);
		QtPaletteDlg(const QtPaletteDlg&) = delete;
		QtPaletteDlg& operator= (const QtPaletteDlg&) = delete;
		~QtPaletteDlg();

		void fillComboxColors(QComboBox *);
	public slots:
		void slot_setWinPalette(int);
		void slot_setWinTextPalette(int);
		void slot_setBtnPalette(int);
		void slot_setBtnTextPalette(int);
		void slot_setBasePalette(int);
		void slot_setTextPalette(int);
};
#endif //QTPALETTEDLG_H
