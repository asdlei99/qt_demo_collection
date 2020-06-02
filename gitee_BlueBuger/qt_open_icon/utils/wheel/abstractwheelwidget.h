#ifndef ABSTRACTWHEELWIDGET_H
#define ABSTRACTWHEELWIDGET_H

#include <QWidget>
#include <QStringList>

//QT_BEGIN_NAMESPACE
//class QPainter;
//class QRect;
//QT_END_NAMESPACE

class AbstractWheelWidget : public QWidget {
    Q_OBJECT

public:
    AbstractWheelWidget(bool touch, QWidget *parent = 0);
//    virtual ~AbstractWheelWidget();

//    int currentIndex() const;
//    void setCurrentIndex(int index);

//    bool event(QEvent*);
//    void paintEvent(QPaintEvent *e);
//    virtual void paintItem(QPainter* painter, int index, const QRect &rect) = 0;

//    virtual int itemHeight() const = 0;
//    virtual int itemCount() const = 0;

//public slots:
//    void scrollTo(int index);

//signals:
//    void stopped(int index);

//protected:
//    int m_currentItem;
//    int m_itemOffset; // 0-itemHeight()
//    qreal m_lastY;
#endif // ABSTRACTWHEELWIDGET_H
