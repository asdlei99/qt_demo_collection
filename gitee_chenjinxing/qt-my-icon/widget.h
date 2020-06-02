#ifndef WIDGET_H
#define WIDGET_H

#include <QPixmap>
#include <QWidget>
#include <QToolButton>
#include "selectcontainer.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    QToolButton* addToolButton(const QPixmap&pixmap);
    QToolButton* addToolButtonByAction(SelectContainer *container, const QPixmap&pixmap, const QVariant &data);


};

#endif // WIDGET_H
