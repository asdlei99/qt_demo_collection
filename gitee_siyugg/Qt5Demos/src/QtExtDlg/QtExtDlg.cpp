/*************************************************************************
    > File Name: QtExtDlg.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月18日 星期六 10时35分07秒
 ************************************************************************/

#include "QtExtDlg.h"
#include <QLayout>

QtExtDlg::QtExtDlg(QWidget *parent):QDialog(parent),
	baseInfoFrame(new QFrame(this)),detailInfoFrame(new QFrame(this)),
	nameLabel(new QLabel(tr("Name:"),this)),
	sexLabel(new QLabel(tr("Sex:"),this)),
	ageLabel(new QLabel(tr("Age:"),this)),
	departLabel(new QLabel(tr("Department:"),this)),
	emailLabel(new QLabel(tr("Email:"),this)),
	nameLineEdit(new QLineEdit(this)),
	sexCombox(new QComboBox(this)),
	ageSlider(new QSlider(Qt::Horizontal,this)),
	departCombox(new QComboBox(this)),
	emailLineEdit(new QLineEdit(this)),
	okBtn(new QPushButton("OK",this)),
	detailBtn(new QPushButton("Detail",this))
{
	sexCombox->addItem("Man");
	sexCombox->addItem("Woman");

	QGridLayout *baseInfoLayout = new QGridLayout;
	baseInfoLayout->addWidget(nameLabel,0,0);
	baseInfoLayout->addWidget(nameLineEdit,0,1);
	baseInfoLayout->addWidget(okBtn,0,2);
	baseInfoLayout->addWidget(sexLabel,1,0);
	baseInfoLayout->addWidget(sexCombox,1,1);
	baseInfoLayout->addWidget(detailBtn,1,2);
	baseInfoFrame->setLayout(baseInfoLayout);

	departCombox->addItem("Depart1");
	departCombox->addItem("Depart2");
	departCombox->addItem("Depart3");

	QGridLayout *detailInfoLayout = new QGridLayout;
	detailInfoLayout->addWidget(ageLabel,0,0);
	detailInfoLayout->addWidget(ageSlider,0,1);
	detailInfoLayout->addWidget(departLabel,1,0);
	detailInfoLayout->addWidget(departCombox,1,1);
	detailInfoLayout->addWidget(emailLabel,2,0);
	detailInfoLayout->addWidget(emailLineEdit,2,1);
	detailInfoFrame->setLayout(detailInfoLayout);
	detailInfoFrame->hide();

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(baseInfoFrame);
	mainLayout->addWidget(detailInfoFrame);
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);

	setLayout(mainLayout);

	connect(okBtn,SIGNAL(clicked()),this,SLOT(slot_okBtnClicked()));
	connect(detailBtn,SIGNAL(clicked()),this,SLOT(slot_showDetail()));
	connect(ageSlider,SIGNAL(valueChanged(int)),this,SLOT(slot_ageChanged(int)));
}
QtExtDlg::~QtExtDlg()
{

}
void QtExtDlg::slot_okBtnClicked()
{
	close();
}
void QtExtDlg::slot_showDetail()
{
	if (detailInfoFrame->isHidden())
		detailInfoFrame->show();
	else
		detailInfoFrame->hide();
}
void QtExtDlg::slot_ageChanged(int age)
{
	ageLabel->setText(QString("%1%2").arg("Age:").arg(age));
}
