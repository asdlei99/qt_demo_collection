#include <QApplication>
#include <QtMath>

#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsPathItem>

#include <QPropertyAnimation>

#include <QGraphicsItemAnimation>
#include <QTimeLine>

#include "mygraphicscene.h"
#include "mygraphicsitem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyGraphicScene *scene =new MyGraphicScene();

    //简单文本
    QGraphicsSimpleTextItem *simpleTextItem =new QGraphicsSimpleTextItem();
    simpleTextItem->setText("simple");
    simpleTextItem->setPos(20,20);
    //格式化文本
    QGraphicsTextItem *textItem =new QGraphicsTextItem();
    textItem->setPlainText("format text");
    textItem->setTextInteractionFlags(Qt::TextEditorInteraction);

    //矩形
    QGraphicsRectItem *rectItem =new QGraphicsRectItem();
    rectItem->setRect(10,10,20,30);
    //直线
    QGraphicsLineItem *lineItem =new QGraphicsLineItem();
    lineItem->setLine(10,10,30,40);
    //椭圆
    QGraphicsEllipseItem *ellipseItem =new QGraphicsEllipseItem();
    ellipseItem->setRect(10,10,30,40);
    //多边形
    QGraphicsPolygonItem *polygonItem =new QGraphicsPolygonItem();
    QPolygonF polygon;
    polygon << QPointF(200.0, 120.0) << QPointF(230.0, 130.0)
        << QPointF(260.0, 180.0) << QPointF(200.0, 200.0);
    polygonItem->setPolygon(polygon);

    //动画测试
    QGraphicsItemAnimation *itemAnimation =new QGraphicsItemAnimation();
    itemAnimation->setItem(rectItem);
    QTimeLine *timeLine =new QTimeLine();
    timeLine->setCurveShape(QTimeLine::SineCurve);
    timeLine->setLoopCount(0);
    itemAnimation->setTimeLine(timeLine);
    int y =(qrand()%400) -200;
    for(int i =0;i <400;i++){
        itemAnimation->setPosAt(i/400.0,QPointF(i-200,y));
    }
    timeLine->start();

    //图形
    QPixmap pixmap(":/rec/test.png");
    pixmap =pixmap.scaled(20,20);
    QGraphicsPixmapItem * pixmapItem =new QGraphicsPixmapItem();
    pixmapItem->setPixmap(pixmap);

    //路径
    QGraphicsPathItem *pathItem =new QGraphicsPathItem();
    QPainterPath starPath;
    starPath.moveTo(90, 50);
    float Pi=3.14159f;
    for (int i = 1; i < 5; ++i) {
        starPath.lineTo(50 + 40 * qCos(0.8 * i * Pi), 50 + 40 * qSin(0.8 * i * Pi));
    }
    starPath.closeSubpath();
    pathItem->setPath(starPath);

    scene->addItem(pixmapItem);
    scene->addItem(simpleTextItem);
    scene->addItem(textItem);
    scene->addItem(rectItem);
    scene->addItem(lineItem);
    scene->addItem(ellipseItem);
    scene->addItem(polygonItem);
    scene->addItem(pathItem);

    QGraphicsView view;
    view.setScene(scene);
    view.show();

    return a.exec();
}
