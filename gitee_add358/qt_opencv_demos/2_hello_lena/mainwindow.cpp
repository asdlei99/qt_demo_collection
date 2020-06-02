#include "mainwindow.h"
#include "widget.h"
#include "convert.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QPushButton>
#include <QHBoxLayout>

#define w 400

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Widget *lenaWidget = new Widget(this);

    /* load jpg file */
    Mat src = imread("resource/lena.jpg", IMREAD_COLOR);
    putText(src, "Hello Lena",
            Point(0, 25),
            FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));

    lenaWidget->set_image(cvMat2QImage(src));

    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);
    QHBoxLayout *h = new QHBoxLayout(widget);
    h->addWidget(lenaWidget);
}

MainWindow::~MainWindow()
{
}
