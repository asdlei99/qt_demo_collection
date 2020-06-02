/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.23
 ** @brief:      自动消失提示框
 */
#include "toast.h"
#include "utilscommon.h"

/**
 * @brief 自动消失提示框
 * @param parent 指名父窗口
 * @param message 所要提示的消息
 * @param w 宽
 * @param h 高
 * @param style 提示框样式：注意字体大小和宽高效果要配合好
 */
Toast::Toast(QWidget *parent, const QString &message,\
             int w, int h, const QString &style):
    QLabel(parent)
{
    setText(message);
    //adjustSize();
    setFixedSize(w, h);
    setAlignment(Qt::AlignCenter);
    startx = (parent->width()-width()) / 2;
    starty = parent->height();
    endy = parent->height()*3/4;
    setStyleSheet(style);
    utilscommon::setShadow(this);
}

/**
 * @brief 弹出提示
 */
void Toast::toast()
{
    QPropertyAnimation *animal= new QPropertyAnimation(this,"pos");
    animal->setDuration(500);
    animal->setStartValue(QPoint(startx,starty));
    animal->setEndValue(QPoint(startx,endy));
    animal->setEasingCurve(QEasingCurve::OutCubic);
    connect(animal, SIGNAL(finished()), this, SLOT(animationFinished()));
    this->show();
    animal->start();
}

/**
 * @brief 提示框弹出动画结束后，释放内存，这是必须的，否则造成内存泄露
 */
void Toast::animationFinished()
{
    QTimer::singleShot(400, this, SLOT(delSelf()));
}

void Toast::delSelf()
{
    delete this;
}
