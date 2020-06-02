#ifndef MYHELP_H
#define MYHELP_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>


class MyHelp
{
public:
    MyHelp();
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);

private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;

};

#endif // MYHELP_H
