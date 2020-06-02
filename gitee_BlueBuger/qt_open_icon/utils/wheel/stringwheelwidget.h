#ifndef STRINGWHEELWIDGET_H
#define STRINGWHEELWIDGET_H
#include "wheelwidget.h"

class StringWheelWidget : public AbstractWheelWidget {
    Q_OBJECT

public:
    StringWheelWidget(bool touch = false);

    QStringList items() const;
    void setItems( const QStringList &items );

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    void paintItem(QPainter* painter, int index, const QRect &rect);

    int itemHeight() const;
    int itemCount() const;

    QString currentContent() const;

private:
    QStringList m_items;
};
#endif // STRINGWHEELWIDGET_H
