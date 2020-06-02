#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSignalMapper>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QSignalMapper * signalMapper =new QSignalMapper(this);

    selectedColor.setRgb(0,0,0);
    //设置画板
    pix=QPixmap(this->size());
    pix.fill(Qt::white);
    //设置工具栏

    straightLineAction =new QAction(QIcon(":/image/painttools/painttools/04.ICO"),QString::fromLocal8Bit("直线"));
    curveLineAction =new QAction(QIcon(":/image/painttools/painttools/06.ICO"),QString::fromLocal8Bit("曲线"));
    circleLineAction=new QAction(QIcon(":/image/painttools/painttools/06.ICO"),QString::fromLocal8Bit("圆"));
    rectLineAction =new QAction(QIcon(":/image/painttools/painttools/06.ICO"),QString::fromLocal8Bit("矩形"));
    paintPotAction =new QAction(QIcon(":/image/color_box/color_box/11.ICO"),QString::fromLocal8Bit("油漆桶"));

    interruptedLineAction =new QAction(QIcon(":/image/painttools/painttools/07.ICO"),QString::fromLocal8Bit("虚线"));
    fullLineAction =new QAction(QIcon(":/image/painttools/painttools/09.ICO"),QString::fromLocal8Bit("实线"));
    colorAction =new QAction(QIcon(":/image/color_box/color_box/11.ICO"),QString::fromLocal8Bit("调色框"));

    connect(straightLineAction,SIGNAL(triggered()),this,SLOT(straightLineActionSlot()));
    connect(curveLineAction,SIGNAL(triggered()),this,SLOT(curveLineActionSlot()));
    connect(circleLineAction,SIGNAL(triggered()),this,SLOT(circleLineActionSlot()));
    connect(rectLineAction,SIGNAL(triggered()),this,SLOT(rectLineActionSlot()));
    connect(paintPotAction,SIGNAL(triggered()),this,SLOT(paintPotActionSlot()));

    connect(interruptedLineAction,SIGNAL(triggered()),this,SLOT(interruptedLineActionSlot()));
    connect(fullLineAction,SIGNAL(triggered()),this,SLOT(fullLineActionSlot()));
    connect(colorAction,SIGNAL(triggered()),this,SLOT(colorActionSlot()));

    interruptedLineAction->setShortcut(QKeySequence("Ctrl+i"));
    fullLineAction->setShortcut(QKeySequence("Ctrl+b"));
    //使用组合框选择线宽
    penWidthCom =new QComboBox();
    penWidthCom->setEditable(true);
    for(int i=2;i< 40;i+=2){
        penWidthCom->addItem(QString::number(i));
    }
    connect(penWidthCom,SIGNAL(editTextChanged(const QString &)),this,SLOT(penWidthComSelected(const QString &)));

    //笔刷
    brushCom =new QComboBox();
    connect(brushCom,SIGNAL(currentIndexChanged(int)),this,SLOT(brushSelectSlot(int)));

    this->ui->mainToolBar->addAction(straightLineAction);
    this->ui->mainToolBar->addAction(curveLineAction);
    this->ui->mainToolBar->addAction(circleLineAction);
    this->ui->mainToolBar->addAction(rectLineAction);
    this->ui->mainToolBar->addAction(paintPotAction);
    this->ui->mainToolBar->addSeparator();

    this->ui->mainToolBar->addAction(interruptedLineAction);
    this->ui->mainToolBar->addAction(fullLineAction);
    this->ui->mainToolBar->addSeparator();

    this->ui->mainToolBar->addAction(colorAction);

    this->ui->mainToolBar->addWidget(penWidthCom);
    this->ui->mainToolBar->addWidget(brushCom);

    this->initPainter();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//初始化绘制状态
void MainWindow::initPainter()
{
    this->lineContext =LINE_CONTENT::Full_Line;
    this->lineShape   =LINE_SHAPE::Straight_Line;

}
//先绘制到pixmap中，再在widget中显示出来
void MainWindow::paintByPainter(QPaintEvent *, QPainter& pp,QPoint &ePoint)
{
    //偏移量
    QPoint drawLastPoint =lastPoint - ePoint;
    QPoint drawEndPoint  =endPoint  - ePoint;
    //如果是绘制曲线 则不断更新lastPoint  如果是直线就不用更新lastPoint
    if(this->lineShape==LINE_SHAPE::Curve_Line){
        pp.drawLine(drawLastPoint,drawEndPoint);
        lastPoint=endPoint;
    }else if(this->lineShape==LINE_SHAPE::Straight_Line){
        pp.drawLine(drawLastPoint,drawEndPoint);
    }//绘制椭圆
    else if(this->lineShape==LINE_SHAPE::Circle_Line){
        pp.drawEllipse(drawLastPoint,drawEndPoint.x()-drawLastPoint.x(),drawEndPoint.y()-drawLastPoint.y());
    }//绘制矩形
    else if(this->lineShape==LINE_SHAPE::Rectangle_Line){
        pp.drawRect(drawLastPoint.x(),drawLastPoint.y(),drawEndPoint.x()-drawLastPoint.x(),drawEndPoint.y()-drawLastPoint.y());
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPen pen;
    pen.setColor(this->selectedColor);
    pen.setWidth(this->selectedWidth);

    //设置pen是虚线还是实线
    if(this->lineContext ==LINE_CONTENT::Interrupted_Line){
//        QVector<qreal> dashes;
//        qreal space =3;
//        dashes<<5<<space<<5<<space;
//        this->pen.setDashPattern(dashes);
        pen.setStyle(Qt::DashDotLine);
    }else{
        pen.setStyle(Qt::SolidLine);
    }

    QPoint ePoint1(0,0);
    QPoint ePoint0(0,ui->mainToolBar->height());
    //开始绘制
    //左键抬起 先绘制到pixmap中，再显示到widget中   如果是绘制线段，也要先绘制到pixmap中，因为线段需要实时保存
    if(!this->leftBtnPress || this->lineShape==LINE_SHAPE::Curve_Line){
        //是绘制状态才去绘制
        if(this->isDrawStatus && this->lineShape!=LINE_SHAPE::Curve_Line){
            QPainter pp(&pix);
            pp.setPen(pen);
            this->paintByPainter(e,pp,ePoint0);
            this->isDrawStatus =false;
        }else if(this->leftBtnPress && this->lineShape==LINE_SHAPE::Curve_Line){
            QPainter pp(&pix);
            pp.setPen(pen);
            this->paintByPainter(e,pp,ePoint0);
        }
        //显示图片
        QPainter painter(this);
        painter.drawPixmap(0,ui->mainToolBar->height(),pix);

        return;
    }
    //左键是按下状态 先显示pixmap，再临时绘制到widget中,如果
    QPainter painter(this);
    painter.setPen(pen);
    //painter.drawPixmap(0,0,pix);
    painter.drawPixmap(0,ui->mainToolBar->height(),pix);
    this->paintByPainter(e,painter,ePoint1);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton&&this->leftBtnPress)
    {
        this->leftBtnPress =false;
        endPoint=event->pos();
        update();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint leftTopDraw(0,ui->mainToolBar->height());
    QPoint rightBottomDraw(this->pix.width(),this->pix.height()+ui->mainToolBar->height());

    QPointF localPos =event->localPos();

    //检查是否是可绘制区域
    if( localPos.x()<leftTopDraw.x() ||
        localPos.x()>rightBottomDraw.x() ||
        localPos.y()<leftTopDraw.y() ||
        localPos.y()>rightBottomDraw.y())
        return;
    if(event->button()==Qt::LeftButton){//鼠标左键按下
        lastPoint=event->pos();
        this->leftBtnPress =true;
        this->isDrawStatus =true;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        endPoint=event->pos();
        update();//进行绘制
    }
}



void MainWindow::straightLineActionSlot()
{
    this->lineShape =LINE_SHAPE::Straight_Line;
}

void MainWindow::curveLineActionSlot()
{
    this->lineShape =LINE_SHAPE::Curve_Line;
}

void MainWindow::circleLineActionSlot()
{
    this->lineShape =LINE_SHAPE::Circle_Line;
}

void MainWindow::rectLineActionSlot()
{
    this->lineShape =LINE_SHAPE::Rectangle_Line;
}

void MainWindow::paintPotActionSlot()
{

}

void MainWindow::interruptedLineActionSlot()
{
    this->lineContext =LINE_CONTENT::Interrupted_Line;
}

void MainWindow::fullLineActionSlot()
{
    this->lineContext =LINE_CONTENT::Full_Line;
}

void MainWindow::colorActionSlot()
{
    QColorDialog cDlg;
    this->selectedColor =cDlg.getColor(this->selectedColor,this,"选择颜色");
}

void MainWindow::brushSelectSlot(int index)
{

}

void MainWindow::penWidthComSelected(const QString &)
{
    this->selectedWidth =this->penWidthCom->currentText().toInt();
}


