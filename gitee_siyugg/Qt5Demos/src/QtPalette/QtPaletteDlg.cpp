/*************************************************************************
    > File Name: QtPaletteDlg.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月16日 星期四 13时46分57秒
 ************************************************************************/

#include "QtPaletteDlg.h"
#include <QLayout>
#include <QColor>
#include <QSize>
#include <QStringList>

QtPaletteDlg::QtPaletteDlg(QWidget *parent):QDialog(parent),
	crtlFrame(new QFrame(this)),displayFrame(new QFrame(this)),
	winPaletteLabel(new QLabel("QPalette::Window",this)),
	winTextPaletteLabel(new QLabel("QPalette::WindowText",this)),
	btnPaletteLabel(new QLabel("QPalette::Button",this)),
	btnTextPaletteLabel(new QLabel("QPalette::ButtonText",this)),
	basePaletteLabel(new QLabel("QPalette::Base",this)),
	textPaletteLabel(new QLabel("QPalette::Text",this)),
	winText(new QLabel("Window Text",displayFrame)),
	winPaletteCombox(new QComboBox(this)),
	winTextPaletteCombox(new QComboBox(this)),
	btnPaletteCombox(new QComboBox(this)),
	btnTextPaletteCombox(new QComboBox(this)),
	basePaletteCombox(new QComboBox(this)),
	textPaletteCombox(new QComboBox(this)),
	displayBtn(new QPushButton("BUTTON",this)),
	textEdit(new QLineEdit(this))
{
	this->setWindowTitle("QtPalette");
	this->resize(800,400);

	displayBtn->setAutoFillBackground(true);
	displayBtn->setStyleSheet("QPushButton:hover:enabled{color:white}");
	this->setStyleSheet("QComboBox::drop-down{color:red;background-color:blue}");

	fillComboxColors(winPaletteCombox);
	fillComboxColors(winTextPaletteCombox);
	fillComboxColors(btnPaletteCombox);
	fillComboxColors(btnTextPaletteCombox);
	fillComboxColors(basePaletteCombox);
	fillComboxColors(textPaletteCombox);

	QGridLayout * crtlItemsLayout = new QGridLayout;
	crtlItemsLayout->addWidget(winPaletteLabel,0,0);
	crtlItemsLayout->addWidget(winPaletteCombox,0,1);
	crtlItemsLayout->addWidget(winTextPaletteLabel,1,0);
	crtlItemsLayout->addWidget(winTextPaletteCombox,1,1);
	crtlItemsLayout->addWidget(btnPaletteLabel,2,0);
	crtlItemsLayout->addWidget(btnPaletteCombox,2,1);
	crtlItemsLayout->addWidget(btnTextPaletteLabel,3,0);
	crtlItemsLayout->addWidget(btnTextPaletteCombox,3,1);
	crtlItemsLayout->addWidget(basePaletteLabel,4,0);
	crtlItemsLayout->addWidget(basePaletteCombox,4,1);
	crtlItemsLayout->addWidget(textPaletteLabel,5,0);
	crtlItemsLayout->addWidget(textPaletteCombox,5,1);
	crtlFrame->setLayout(crtlItemsLayout);

	QVBoxLayout *displayLayout = new QVBoxLayout();
	displayLayout->addWidget(displayBtn);
	displayLayout->addWidget(textEdit);

	displayFrame->setFrameStyle(QFrame::Box | QFrame::Raised);
	displayFrame->setAutoFillBackground(true);
	displayLayout->addWidget(displayFrame);

	QHBoxLayout * mainLayout = new QHBoxLayout(this);
	mainLayout->addWidget(crtlFrame,1);
	mainLayout->addLayout(displayLayout,1);

	this->setLayout(mainLayout);

	connect(winPaletteCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_setWinPalette(int)));
	connect(winTextPaletteCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_setWinTextPalette(int)));
	connect(btnPaletteCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_setBtnPalette(int)));
	connect(btnTextPaletteCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_setBtnTextPalette(int)));
	connect(basePaletteCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_setBasePalette(int)));
	connect(textPaletteCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_setTextPalette(int)));
}
QtPaletteDlg::~QtPaletteDlg()
{

}
void QtPaletteDlg::fillComboxColors(QComboBox *combox)
{
	QStringList colorList = QColor::colorNames();
	for (auto & color : colorList)
	{
		QPixmap pix(QSize(combox->width(),combox->height() - 8));
		pix.fill(QColor(color));
		combox->addItem(QIcon(pix),NULL);
		combox->setIconSize(pix.size());
		combox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	}
}
void QtPaletteDlg::slot_setWinPalette(int index)
{
	QPalette p = displayFrame->palette();
	p.setColor(QPalette::Window,QColor(QColor::colorNames()[index]));
	displayFrame->setPalette(p);

}
void QtPaletteDlg::slot_setWinTextPalette(int index)
{
	QPalette p = displayFrame->palette();
	p.setColor(QPalette::WindowText,QColor(QColor::colorNames()[index]));
	displayFrame->setPalette(p);
}
void QtPaletteDlg::slot_setBtnPalette(int index)
{
/*	QPalette p = displayBtn->palette();
	p.setColor(QPalette::Button,QColor(QColor::colorNames()[index]));
	displayBtn->setPalette(p);*/
	displayBtn->setStyleSheet(QString("background:%1").arg(QColor::colorNames()[index]));
}
void QtPaletteDlg::slot_setBtnTextPalette(int index)
{
/*	QPalette p = displayBtn->palette();
	p.setColor(QPalette::ButtonText,QColor(QColor::colorNames()[index]));
	displayBtn->setPalette(p);*/
	displayBtn->setStyleSheet(QString("color:") + QColor::colorNames()[index]);
}
void QtPaletteDlg::slot_setBasePalette(int index)
{
	QPalette p = textEdit->palette();
	p.setColor(QPalette::Base,QColor(QColor::colorNames()[index]));
	textEdit->setPalette(p);
}
void QtPaletteDlg::slot_setTextPalette(int index)
{
	QPalette p = textEdit->palette();
	p.setColor(QPalette::Text,QColor(QColor::colorNames()[index]));
	textEdit->setPalette(p);
}
