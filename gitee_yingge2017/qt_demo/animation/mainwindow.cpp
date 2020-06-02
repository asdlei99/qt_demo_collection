#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qpropertyanimation.h>
#include <QGraphicsOpacityEffect>
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initCommonDemo();

    //文字跑马灯
    ui->label_runningHorse->resize(2222,55);
    m_scrollCaptionStr = "寒雨连江夜入吴，平明送客楚山孤。洛阳亲友如相问，一片冰心在玉壶。";
    //图片跑马灯

    initImageRunningHorseLamp();

    //
    m_commonTimerId = startTimer(2000);
    m_textTimerId = startTimer(222);
    m_runningHorseImageTimerId = startTimer(2222);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == m_commonTimerId){
        m_pa->start();
        m_opacityPa->start();

        m_leftPa->start();
        m_rightPa->start();
        m_topPa->start();
        m_bottomPa->start();
    }else if(e->timerId() == m_textTimerId){
        //文字跑马灯
        static int nPos = 0;
        if (nPos > m_scrollCaptionStr.length())
        {
            nPos = 0;
        }
        ui->label_runningHorse->setText(m_scrollCaptionStr.mid(nPos));
        nPos++;
    }else if(e->timerId() == m_runningHorseImageTimerId){
        //图片跑马灯
        updateImageRunningHorseLamp();
        m_imageLeftPa->start();
        m_imageRightPa->start();
    }
}

void MainWindow::on_pushButton_start_clicked()
{
    m_pa->start();
}

void MainWindow::on_pushButton_opacity_start_clicked()
{
    m_opacityPa->start();
}

void MainWindow::initCommonDemo()
{
    //geometry
    QSize size(222,55);
    QPoint startPoint(0,-55);
    QPoint endPoint(0,0);

    ui->pushButton->setGeometry(QRect(startPoint,size));

    m_pa = new QPropertyAnimation(ui->pushButton,"geometry");
    m_pa->setDuration(1500);
    m_pa->setStartValue(QRect(startPoint,size));

    m_pa->setKeyValueAt(0.4,QRect(endPoint,size));
    m_pa->setKeyValueAt(0.5,QRect(endPoint,size));
    m_pa->setKeyValueAt(0.6,QRect(endPoint,size));

    m_pa->setEndValue(QRect(startPoint,size));

    //opacity
#if 0
    m_opacityGOE = new QGraphicsOpacityEffect(this);
    m_opacityGOE->setOpacity(1);
    ui->pushButton_opacity->setGraphicsEffect(m_opacityGOE);
    ui->pushButton_opacity->resize(55,55);

    m_opacityPa = new QPropertyAnimation(m_opacityGOE, "opacity");
    m_opacityPa->setDuration(2000);
    //    m_opacityPa->setStartValue(1);
    m_opacityPa->setStartValue(1);
    m_opacityPa->setKeyValueAt(0.5,0);
    m_opacityPa->setEndValue(1);
#endif

#if 1
    m_opacityGOE = new QGraphicsOpacityEffect(this);
    m_opacityGOE->setOpacity(1);
    ui->label_opacity->setGraphicsEffect(m_opacityGOE);
    ui->label_opacity->resize(99,55);

    m_opacityPa = new QPropertyAnimation(m_opacityGOE, "opacity");
    m_opacityPa->setDuration(4000);
    m_opacityPa->setStartValue(1);
    m_opacityPa->setKeyValueAt(0.5,0);
    m_opacityPa->setEndValue(1);
#endif

    //left
    ui->label_left->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    ui->label_left->resize(99,55);

    QRect leftWdgetRectStart = ui->label_left->geometry();
    QRect leftWdgetRectEnd = leftWdgetRectStart;
    leftWdgetRectEnd.setWidth(0);

    m_leftPa = new QPropertyAnimation(ui->label_left,"geometry");
    m_leftPa->setDuration(2000);
    m_leftPa->setStartValue(leftWdgetRectStart);

    m_leftPa->setEndValue(leftWdgetRectEnd);
    //right
    ui->label_right->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    ui->label_right->resize(99,55);

    QRect rightWdgetRectStart = ui->label_right->geometry();
    QRect rightWdgetRectEnd = rightWdgetRectStart;
    rightWdgetRectEnd.setX(rightWdgetRectStart.x() + rightWdgetRectStart.width());
    rightWdgetRectEnd.setWidth(0);

    m_rightPa = new QPropertyAnimation(ui->label_right,"geometry");
    m_rightPa->setDuration(2000);
    m_rightPa->setStartValue(rightWdgetRectStart);

    m_rightPa->setEndValue(rightWdgetRectEnd);
    //top
    ui->label_top->setAlignment(Qt::AlignCenter);
    ui->label_top->resize(99,55);

    QRect topWdgetRectStart = ui->label_top->geometry();
    QRect topWdgetRectEnd = topWdgetRectStart;
    topWdgetRectEnd.setHeight(0);

    m_topPa = new QPropertyAnimation(ui->label_top,"geometry");
    m_topPa->setDuration(2000);
    m_topPa->setStartValue(topWdgetRectStart);
    m_topPa->setEndValue(topWdgetRectEnd);

    //bottom
    ui->label_bottom->setAlignment(Qt::AlignCenter);
    ui->label_bottom->resize(99,55);

    QRect bottomWdgetRectStart = ui->label_bottom->geometry();
    QRect bottomWdgetRectEnd = bottomWdgetRectStart;
    //    bottomWdgetRectEnd.setX(rightWdgetRectStart.x() + rightWdgetRectStart.width());
    bottomWdgetRectEnd.setY(bottomWdgetRectStart.y() + bottomWdgetRectStart.height());

    m_bottomPa = new QPropertyAnimation(ui->label_bottom,"geometry");
    m_bottomPa->setDuration(2000);
    m_bottomPa->setStartValue(bottomWdgetRectStart);
    m_bottomPa->setEndValue(bottomWdgetRectEnd);

}

void MainWindow::initImageRunningHorseLamp()
{
    m_eImageState = E_RIGHT_STATE;
    QRect rectLeft = ui->widget_left->geometry();
    //    ui->widget_right->move(rectLeft.x() + rectLeft.width(),rectLeft.y());
    //    ui->widget_right->setVisible(false);
    QRect rectRight = rectLeft;
    rectRight.setX(rectRight.x() + rectRight.width());
    ui->widget_right->setGeometry(rectRight);

    m_imageLeftPa = new QPropertyAnimation(ui->widget_left,"geometry");
    m_imageLeftPa->setEasingCurve(QEasingCurve::InOutQuad);
    m_imageLeftPa->setDuration(1111);

    m_imageRightPa = new QPropertyAnimation(ui->widget_right,"geometry");
    m_imageRightPa->setEasingCurve(QEasingCurve::InOutQuad);
    m_imageRightPa->setDuration(1111);

}

void MainWindow::updateImageRunningHorseLamp()
{
    static QRect originRect = ui->widget_left->geometry();

    if(m_eImageState == E_RIGHT_STATE){
       qDebug()<<"E_RIGHT_STATE";
        //两张图片都已经移动到右侧
        QRect rectLeftStart = originRect;

        QRect rectLeftEnd = rectLeftStart;
        rectLeftEnd.setX(rectLeftEnd.x() - rectLeftEnd.width());
        rectLeftEnd.setWidth(originRect.width());

        QRect rectRightStart = originRect;
        rectRightStart.setX(rectRightStart.x() + rectRightStart.width());
        rectRightStart.setWidth(originRect.width());
        QRect rectRightEnd = originRect;
        //
        m_imageLeftPa->setStartValue(rectLeftStart);
        m_imageLeftPa->setEndValue(rectLeftEnd);

        m_imageRightPa->setStartValue(rectRightStart);
        m_imageRightPa->setEndValue(rectRightEnd);
    }else if(m_eImageState == E_LEFT_STATE){
        qDebug()<<"E_LEFT_STATE";
        //两张图片都已经移动到左侧
        QRect rectRightStart = originRect;
        QRect rectRightEnd = rectRightStart;
        rectRightEnd.setX(rectRightStart.x() + rectRightStart.width());
        rectRightEnd.setWidth(originRect.width());

        QRect rectLeftStart = rectRightStart;
        rectLeftStart.setX(rectRightStart.x() - rectRightStart.width());
        rectLeftStart.setWidth(originRect.width());
        QRect rectLeftEnd = rectRightStart;

        m_imageLeftPa->setStartValue(rectLeftStart);
        m_imageLeftPa->setEndValue(rectLeftEnd);

        m_imageRightPa->setStartValue(rectRightStart);
        m_imageRightPa->setEndValue(rectRightEnd);
    }

    if(m_eImageState == E_LEFT_STATE){
        m_eImageState = E_RIGHT_STATE;
    }else{
        m_eImageState = E_LEFT_STATE;
    }
}
