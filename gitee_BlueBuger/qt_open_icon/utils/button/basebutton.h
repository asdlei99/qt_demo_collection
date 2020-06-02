/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.4
 ** @brief:      按钮基类
 */

#ifndef BASEBUTTON_H
#define BASEBUTTON_H

#include <iconhelper.h>

class BaseButton : public QPushButton
{
    Q_OBJECT
public:
    explicit BaseButton(QWidget *parent=0);
    explicit BaseButton(const AbstractFont &fontLib, int iconIndex, \
                        int w, int h, const QString &style = QString());

protected slots:
    virtual void pressSlot(){}  //按下后需要扩展的功能
    virtual void releaseSlot(){}  //松开后需要扩展的功能

signals:
    void btnReleased();  //这个信号只有在松开时光标仍在按钮时候才会发送
    //按钮原先pressed和released信号不受影响，可继续使用

protected:
    virtual void mouseReleaseEvent(QMouseEvent *e);
    void restoreFont();  //恢复字体库，防止别的组件更改字体库
    QString fontName;  //存储字体库名称
};

#endif // BASEBUTTON_H
