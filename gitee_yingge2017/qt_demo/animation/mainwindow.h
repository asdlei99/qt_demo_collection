#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QPropertyAnimation;
class QGraphicsOpacityEffect;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void  timerEvent(QTimerEvent *e);
private slots:
    void on_pushButton_start_clicked();
    void on_pushButton_opacity_start_clicked();
private:
    void initCommonDemo();
    void initImageRunningHorseLamp();
    void updateImageRunningHorseLamp();
private:
    Ui::MainWindow *ui;

    int m_commonTimerId,m_textTimerId,m_runningHorseImageTimerId;
    QString m_scrollCaptionStr;

    QPropertyAnimation *m_pa;
    QPropertyAnimation *m_opacityPa;
    QGraphicsOpacityEffect *m_opacityGOE;

    QPropertyAnimation *m_leftPa;
    QPropertyAnimation *m_rightPa;
    QPropertyAnimation *m_topPa;
    QPropertyAnimation *m_bottomPa;
//图片跑马灯
    enum EImageState{
        E_LEFT_STATE,    //两张图片都已经移动到左侧
        E_RIGHT_STATE   //两张图片都已经移动到右侧
    };
    EImageState m_eImageState;
    QPropertyAnimation *m_imageLeftPa,*m_imageRightPa;
};

#endif // MAINWINDOW_H
