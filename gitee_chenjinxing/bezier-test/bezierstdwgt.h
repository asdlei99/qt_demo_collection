#ifndef BEZIERSTDWGT_H
#define BEZIERSTDWGT_H



#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QVector>
#include <QLabel>
#include <QPoint>

#define POSI_POINT_STYLE  "QLabel{background:white}"
#define LEFT_POINT_STYLE  "QLabel{background:red}"
#define RIGHT_POINT_STYLE "QLabel{background:black}"


struct BezierPoint{
    QLabel *posiPoint;
    QLabel *leftCtrlPoint;
    QLabel *rightCtrlPoint;
};

class BezierStdWgt : public QWidget
{
    Q_OBJECT
public:
    explicit BezierStdWgt(QWidget *parent = nullptr);

signals:

public slots:

//控制节点
private:
    QVector<BezierPoint> ctrlPoints;
    QWidget *selectedPoint;

private:
    //重写函数
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);

    //添加节点
    bool addCtrlPoint(const QPoint &p);
    QLabel *createPoint(const QPoint &p, const QString &style);
    //删除节点
    bool delCtrlPoint();


};

#endif // BEZIERSTDWGT_H
