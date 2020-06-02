#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>

class QPaintEvent;

namespace Ui {
class PaintArea;
}

class PaintArea : public QWidget
{
    Q_OBJECT

public:
    explicit PaintArea(QWidget *parent = 0);
    ~PaintArea();

    enum class Shape{None,Line,Rectangle,RoundRect,Ellipse,Polygon,Polyline,Points,
                     Arc,Path,Text,Pixmap};

    void setShape(Shape);
    void setPen(QPen);
    void setBrush(QBrush);
    void setFillRule(Qt::FillRule);

    const QPen retPen() const;//返回PaintArea类型中的pen成员，减少代码量
    void paintEvent(QPaintEvent *);
private:
    Ui::PaintArea *ui;
    Shape shape;
    QPen pen;
    QBrush brush;
    Qt::FillRule fillRule;
};

#endif // PAINTAREA_H
