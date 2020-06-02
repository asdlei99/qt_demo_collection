#ifndef BEZIERWGT_H
#define BEZIERWGT_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QVector>
#include <QLabel>
#include <QPoint>

class BezierWgt : public QWidget
{
    Q_OBJECT
public:
    explicit BezierWgt(QWidget *parent = nullptr);


signals:
public slots:

//控制节点
private:
    QVector<QLabel*> ctrlPoints;
    QWidget *selectedPoint;

private:
    //重写函数
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);

    //添加节点
    bool addCtrlPoint(const QPoint &p);
    //删除节点
    bool delCtrlPoint();

};

#endif // BEZIERWGT_H
