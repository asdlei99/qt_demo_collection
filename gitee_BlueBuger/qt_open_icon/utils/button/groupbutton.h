#ifndef GROUPBUTTON_H
#define GROUPBUTTON_H

#include "baselabel.h"

class GroupButton : public QPushButton
{
    Q_OBJECT
public:
    explicit GroupButton(const AbstractFont &fontLib, int iconIndex, \
                         int w, int h, const QString &text, const QString &style1, const QString &style2);

signals:

public slots:
private:
    BaseLabel *label1;  //放图形
    QLabel *label2;  //放文字
};

#endif // GROUPBUTTON_H
