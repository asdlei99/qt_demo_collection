#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QColor>
#include <QPoint>

class QMouseEvent;
class QPaintEvent;
class QResizeEvent;
class QPen;
class QPixmap;

class DrawArea : public QWidget
{
    Q_OBJECT
public:
    explicit DrawArea(QWidget *parent = 0);
    ~DrawArea();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    QPen *pen;
    QPixmap *pix;
    QColor penColor;
    int penWidth;
    Qt::PenStyle penStyle;
    QPoint startPoint,endPoint;

signals:

public slots:
    void setPenStyle(int);
    void setPenWidth(int);
    void setPenColor(QColor);
    void clear();
};

#endif // DRAWAREA_H
