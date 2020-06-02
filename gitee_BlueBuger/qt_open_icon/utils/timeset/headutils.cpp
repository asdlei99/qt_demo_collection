/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.28
 ** @brief:      日期时间专用标题栏，以后可以设计为通用组件
 */

#include "headutils.h"

#define BACK_BUTTON_STYLE "\
QPushButton{\
    color:#000000;\
    font:25px;\
    border:0px;\
    background-color:#FFFFFF;\
}\
QPushButton:pressed{\
    color:#436EEE;\
}\
"
#define TITLE_LABEL_STYLE "\
QLabel{\
    color:#000000;\
    font:15px;\
}\
"

HeadUtils::HeadUtils(const QString &title, QWidget *parent) :
    QWidget(parent)
{
    //整体部件
    setFixedSize(w, h);

    //返回按钮
    back = new BaseButton(TimeFont(), TimeFont::ICON_BACK, 28, 28, BACK_BUTTON_STYLE);
    back->setFocusPolicy(Qt::NoFocus);
    back->adjustSize();

    //中间标题
    picLab = new BaseLabel(TimeFont(), TimeFont::ICON_DATE, 15, 15, TITLE_LABEL_STYLE);
    titleLab = new QLabel(title);
    picLab->adjustSize();
    titleLab->adjustSize();
    QWidget *picWig = new QWidget;
    QHBoxLayout *picLay = new QHBoxLayout(picWig);
    picLay->addWidget(picLab);
    picLay->addWidget(titleLab);
    picLay->setMargin(0);

    QWidget *titleWig = new QWidget;
    titleWig->setFixedSize(325, 30);
    QHBoxLayout *tmpLay = new QHBoxLayout(titleWig);
    tmpLay->addWidget(picWig, 0, Qt::AlignCenter);
    tmpLay->setMargin(0);
    tmpLay->setSpacing(0);

    QHBoxLayout *titleLay = new QHBoxLayout(this);
    titleLay->addWidget(back, 0, Qt::AlignTop);
    titleLay->addWidget(titleWig);
    titleLay->setMargin(0);
    titleLay->setSpacing(0);

    setStyleSheet("background-color:#FFFFFF;");
    connect(back, SIGNAL(btnReleased()), this, SIGNAL(backSignal()));
}

/**
 * @brief 绘制下方线条
 */
void HeadUtils::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(QBrush("#000000"), 3, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(QPoint(28, height()-3), QPoint(width()-28, height()-3));
}
