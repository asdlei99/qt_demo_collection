/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.28
 ** @brief:      日期时间专用标题栏，以后可以设计为通用组件
 */

#ifndef HEADUTILS_H
#define HEADUTILS_H

#include "baselabel.h"
#include "basebutton.h"

class HeadUtils : public QWidget
{
    Q_OBJECT
public:
    explicit HeadUtils(const QString &title, QWidget *parent = 0);

signals:
    void backSignal();

private:
    void paintEvent(QPaintEvent *);
    QHBoxLayout *hBoxLayout;
    BaseButton *back;
    BaseLabel *picLab;
    QLabel *titleLab;

    static const int w = 355;
    static const int h = 35;
};

#endif // HEADUTILS_H
