#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "opencv2/core/core.hpp"

class Widget;
class Slider;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init_menuBar();

    enum OpType {
        Normal,
        Homogeneous,    // 归一化滤波平滑
        Gaussian,       // 高斯滤波平滑
        Median,         // 中值滤波平滑
        Bilateral,      // 双边滤波平滑
        Noise,          // 噪声
        Erode,          // 腐蚀
        CannyImage      // 边缘检测
    };

protected slots:    
    void open_file();

    void update_image();

    void normal_image();

    void homogeneous_blur();

    void gaussian_blur();

    void median_blur();

    void bilateral_blur();

    void gaussian_noise();

    void erode_image();

    void canny_image();

    void flip_horizontal();

    void flip_vertical();

protected:
    void wheelEvent(QWheelEvent *e);
    void resizeEvent(QResizeEvent *event);
private:
    cv::Mat m_src;
    cv::Mat m_dst;
    Widget *m_imageWidget;
    OpType m_opType;
    QString m_title;
    Slider *m_blurSlider;
    Slider *m_noiseSlider;
    Slider *m_cannyThreshold1Slider;
    Slider *m_cannyThreshold2Slider;
    Slider *m_apertureSlider;
};
#endif // MAINWINDOW_H
