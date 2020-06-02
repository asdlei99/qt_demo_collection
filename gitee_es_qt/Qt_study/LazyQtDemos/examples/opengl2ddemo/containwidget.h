#ifndef CONTAINWIDGET_H
#define CONTAINWIDGET_H

#include "myhelp.h"

#include <QWidget>

class ContainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContainWidget(QWidget *parent = nullptr);

private:
    MyHelp helper;

};

#endif // CONTAINWIDGET_H
