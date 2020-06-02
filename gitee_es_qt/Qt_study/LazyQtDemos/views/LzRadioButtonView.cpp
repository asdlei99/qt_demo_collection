#include "LzRadioButtonView.h"

#include <QVBoxLayout>

LzRadioButtonView::LzRadioButtonView(QWidget *parent) : QDialog(parent)
{
//    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    setWindowTitle(tr("QRadioButtonTest"));
    setFixedSize(600, 400);

    /* ******* 普通RadioButton ******* */
    autoBtn = new QRadioButton(tr("Auto"));
    manualBtn = new QRadioButton(tr("Manual"));
    manualFullSpeedBtn = new QRadioButton(tr("Manual Full Speed"));

    operatingModeGroup = new QButtonGroup(this);
    operatingModeGroup->addButton(autoBtn, OM_Auto);
    operatingModeGroup->addButton(manualBtn, OM_Manual);
    operatingModeGroup->addButton(manualFullSpeedBtn, OM_ManualFullSpeed);
    autoBtn->setChecked(true);  // 为operatingModeGroup组设置初选项

    /* ******* 添加Icon的RadioButton ******* */
    powerOnBtn = new QRadioButton(tr("Power ON"));
    powerOnBtn->setIcon(QIcon(":/images/power_on.png"));
    powerOffBtn = new QRadioButton(tr("Power OFF"));
    powerOffBtn->setIcon(QIcon(":/images/power_off.png"));

    powerGroup = new QButtonGroup(this);
    powerGroup->addButton(powerOnBtn);
    powerGroup->addButton(powerOffBtn);
    powerOffBtn->setChecked(true);  // 为powerGroup组设置初选项

    // 创建布局
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(autoBtn);
    mainLayout->addWidget(manualBtn);
    mainLayout->addWidget(manualFullSpeedBtn);
    mainLayout->addStretch();
    mainLayout->addWidget(powerOnBtn);
    mainLayout->addWidget(powerOffBtn);
    mainLayout->addStretch();
//    mainLayout->addWidget(curAnimalLabel);
//    mainLayout->addLayout(customBtnBarLayout);
    setLayout(mainLayout);

    // 连接信号
    connect(operatingModeGroup, SIGNAL(buttonToggled(int,bool)), this, SLOT(operatingModeButtonsToggled(int,bool)));
    connect(operatingModeGroup, SIGNAL(buttonClicked(int)), this, SLOT(operatingModeButtonsClicked(int)));
//    connect(customGroup, SIGNAL(buttonClicked(int)), this, SLOT(customButtonsClicked(int)));
//    connect(customGroup, SIGNAL(buttonToggled(int,bool)), this, SLOT(customButtonsToggled(int,bool)));
}

LzRadioButtonView::~LzRadioButtonView()
{

}

void LzRadioButtonView::operatingModeButtonsToggled(int id, bool status)
{
    int tmp = operatingModeGroup->checkedId();
    QString str = operatingModeGroup->checkedButton()->text();
    QByteArray byteArray = str.toLocal8Bit();
    qDebug("flag = %d, status = %d, tmp = %d, checked = %s", id, status, tmp, byteArray.data());
}

void LzRadioButtonView::operatingModeButtonsClicked(int id)
{
    qDebug("Clicked: %d", id);
}

//void LzRadioButtonView::customButtonsToggled(int id, bool state)
//{
//    if(state == false)
//    {   // 修改被unchecked按钮的样式
//        customGroup->button(id)->setStyleSheet(toolBtnUncheckedStyleSheet);
//    }else
//    {   // 修改被checked按钮的样式
//        customGroup->checkedButton()->setStyleSheet(toolBtnCheckedStyleSheet);
//    }
//}

//void LzRadioButtonView::customButtonsClicked(int id)
//{
//    curAnimalLabel->setText(QString(tr("当前选择："))+animalStrList.at(id));
//}
