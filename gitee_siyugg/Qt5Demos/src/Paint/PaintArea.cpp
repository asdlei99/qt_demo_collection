#include <QPainter>
#include "PaintArea.h"
#include "ui_PaintArea.h"

PaintArea::PaintArea(QWidget *parent) :QWidget(parent),
    ui(new Ui::PaintArea)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    setMinimumSize(400,400);
}

PaintArea::~PaintArea()
{
    delete ui;
}
void PaintArea::setShape(Shape s)
{
    shape = s;
    update();
}
void PaintArea::setPen(QPen p)
{
    pen = p;
    update();
}
void PaintArea::setFillRule(Qt::FillRule rule)
{
    fillRule = rule;
    update();
}
void PaintArea::setBrush(QBrush b)
{
    brush = b;
    update();
}
const QPen PaintArea::retPen() const
{
    return pen;
}
void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(pen);
    p.setBrush(brush);

    QRect rect(50,100,300,200);

    static const QPoint points[4] =
    {
        QPoint(150,100),QPoint(300,150),QPoint(350,250),QPoint(100,300)
    };
    int startAngle = 30 * 16;
    int spanAngle = 120 *16;

    QPainterPath path;
    path.addRect(150,150,100,100);
    path.moveTo(100,100);
    path.cubicTo(300,100,200,200,300,300);
    path.cubicTo(100,300,200,200,100,100);
    path.setFillRule(fillRule);
    switch (shape)
    {
    case (Shape::Line):
        p.drawLine(rect.topLeft(),rect.bottomRight());break;
    case (Shape::Rectangle):
        p.drawRect(rect);break;
    case (Shape::RoundRect):
        p.drawRoundRect(rect);break;
    case (Shape::Ellipse):
        p.drawEllipse(rect);break;
    case (Shape::Polygon):
        p.drawPolygon(points,4);break;
    case (Shape::Polyline):
        p.drawPolyline(points,4);break;
    case (Shape::Points):
        p.drawPoints(points,4);break;
    case (Shape::Arc):
        p.drawArc(rect,startAngle,spanAngle);break;
    case (Shape::Path):
        p.drawPath(path);break;
    case (Shape::Text):
        p.drawText(rect,Qt::AlignCenter,tr("Hello Qt"));break;
    case (Shape::Pixmap):
        p.drawPixmap(150,150,QPixmap(":/image/image/Xbox.png"));break;
    default:
        break;
    }
}
