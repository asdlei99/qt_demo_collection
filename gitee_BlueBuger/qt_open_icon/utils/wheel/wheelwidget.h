/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.29
 ** @brief:      滚动列表基础组件,修改自QT官方示例
 */

#ifndef WHEELWIDGET_H
#define WHEELWIDGET_H

#include "platformhead.h"

class AbstractWheelWidget : public QWidget {
    Q_OBJECT

public:
    AbstractWheelWidget(bool touch, QWidget *parent = 0);
    virtual ~AbstractWheelWidget();

    int currentIndex() const;
    void setCurrentIndex(int index);

    bool event(QEvent*);
    void paintEvent(QPaintEvent *e);
    virtual void paintItem(QPainter* painter, int index, const QRect &rect) = 0;

    virtual int itemHeight() const = 0;
    virtual int itemCount() const = 0;

public slots:
    void scrollTo(int index);

signals:
    void stopped(int index);

protected:
    int m_currentItem;
    int m_itemOffset; // 0-itemHeight()
    qreal m_lastY;
};

#endif // WHEELWIDGET_H
