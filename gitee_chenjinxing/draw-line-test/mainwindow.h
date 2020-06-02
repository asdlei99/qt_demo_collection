#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QIcon>
#include <QPoint>
#include <QPointF>
#include <QColorDialog>
#include <QColor>
#include <QPen>
#include <QBrush>

#include <QAction>
#include <QComboBox>

enum LINE_CONTENT{
    Full_Line, //实线
    Interrupted_Line, //虚线
};

enum LINE_SHAPE{
    Straight_Line,     //直线
    Curve_Line,        //曲线
    Circle_Line,       //圆
    Rectangle_Line,    //矩形
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QPixmap pix;
    QPoint lastPoint;
    QPoint endPoint;

    LINE_CONTENT lineContext;
    LINE_SHAPE lineShape;

    QColor selectedColor; //当前颜色
    int selectedWidth;   //选择线宽
    QBrush brush;
    //工具栏控件
    QAction *straightLineAction;  //直线
    QAction *curveLineAction;     //曲线
    QAction *circleLineAction;    //圆
    QAction *rectLineAction;      //矩形

    QAction *interruptedLineAction; //虚线
    QAction *fullLineAction;//实线
    QComboBox* penWidthCom;//线宽选择框

    QAction *colorAction;   //调色框

    QAction *paintPotAction;   //油漆桶

    QComboBox *brushCom; //笔刷

    bool leftBtnPress =false;
    bool isDrawStatus =false;

public:
    void initPainter();
//函数声明
protected:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);


    void paintByPainter(QPaintEvent *, QPainter &pp, QPoint &ePoint);


public slots:
    void straightLineActionSlot();
    void curveLineActionSlot();
    void circleLineActionSlot();
    void rectLineActionSlot();
    void paintPotActionSlot();

    void interruptedLineActionSlot();
    void fullLineActionSlot();
    void colorActionSlot();


    void brushSelectSlot(int index);
    void penWidthComSelected(const QString &);
};

#endif // MAINWINDOW_H
