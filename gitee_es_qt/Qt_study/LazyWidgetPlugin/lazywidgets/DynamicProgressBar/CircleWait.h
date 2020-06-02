#ifndef CIRCLEWAIT_H
#define CIRCLEWAIT_H

#include <QWidget>

class CircleWait : public QWidget
{
    Q_OBJECT
public:
    explicit CircleWait(QWidget *parent = nullptr);

    QColor getColor() const { return m_color; }
    void setColor(QColor color);
    bool getClockwiseRotate() const { return m_clockwiseRotate; }
    int getRotateDelta() const { return m_rotateDelta; }

public slots:
    void setClockwiseRotate(bool clockwise);
    void setRotateDelta(int delta);

protected:
    void paintEvent(QPaintEvent *);
    void drawCircleWait(QPainter& painter);//圆形等待
    QSize sizeHint() const { return QSize(100, 100); }

private:
    QColor m_color;
    bool m_clockwiseRotate;//顺时针旋转
    int m_rotateDelta;//旋转步进角度

    int m_rotateAngle;//旋转角度
    QTimer* m_timer;
};

#endif // CIRCLEWAIT_H
