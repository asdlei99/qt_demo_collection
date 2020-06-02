#ifndef FOOTWIDGET_H
#define FOOTWIDGET_H

#include <QWidget>

class FootWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FootWidget(QWidget *parent = nullptr);

signals:

public slots:
protected:
    void paintEvent(QPaintEvent *event);
private:
    void readData();
    void colorParser();
    double getScale();
    QColor getColor(uint num);
private:
    uint m_max;
    uint m_min;
};

#endif // FOOTWIDGET_H
