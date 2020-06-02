/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.8
 ** @brief:      适用于多个图标切换的按钮
 */

#ifndef LOOPBUTTON_H
#define LOOPBUTTON_H

#include "basebutton.h"

class LoopButton : public BaseButton
{
    Q_OBJECT
public:
    explicit LoopButton(const AbstractFont &fontLib, int iconIndex,\
                        int w, int h, const QString &style = QString());
signals:

protected slots:

protected:
    void switchIndex(int index);
    QList<int> iconList;
    int curIndex;  //表示当前显示哪个图标
};

#endif // LOOPBUTTON_H
