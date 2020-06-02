#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QLabel>

class BezierFixWgt : public QWidget
{
    Q_OBJECT
public:
    explicit BezierFixWgt(QWidget *parent = nullptr);

    QLabel *startLabel;
    QLabel *ctrlLabel1;
    QLabel *ctrlLabel2;
    QLabel *endLabel;

    QLabel *ctrlLabel3;
    QLabel *ctrlLabel4;
    QLabel *endLabel2;

    QWidget *selectedWidget;

private:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

};

#endif // MYWIDGET_H
