#include "mainwindow.h"
#include "widget.h"
#include "convert.h"
#include "slider.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QWheelEvent>
#include <QTime>
#include <QFileDialog>
#include <QLabel>
#include <QSpinBox>

static const int MAX_KERNEL_LENGTH = 31;

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_src(imread("/tmp/lena.jpg", IMREAD_COLOR)),
      m_dst(m_src.clone()),
      m_imageWidget(new Widget(this)),
      m_opType(Normal),
      m_title(tr("Hello Lena")),
      m_blurSlider(new Slider(tr("Blur"), 1, MAX_KERNEL_LENGTH, 2, this)),
      m_noiseSlider(new Slider(tr("Noise"), 1, MAX_KERNEL_LENGTH, 1,  this)),
      m_cannyThreshold1Slider(new Slider(tr("Threshold1"), 3, 9, 1, this)),
      m_cannyThreshold2Slider(new Slider(tr("Threshold2"), 3, 9, 1, this)),
      m_apertureSlider(new Slider(tr("Aperture"), 3, 7, 2, this))
{
    setWindowIcon(QIcon(":/resource/lena.jpg"));
    setMinimumSize(710, 570);
    init_menuBar();

    /* blur slider */
    connect(m_blurSlider, SIGNAL(valueChanged(int)), SLOT(update_image()));

    /* noise slider */
    connect(m_noiseSlider, SIGNAL(valueChanged(int)), SLOT(update_image()));

    /* canny slider */
    connect(m_cannyThreshold1Slider, SIGNAL(valueChanged(int)), SLOT(update_image()));
    connect(m_cannyThreshold2Slider, SIGNAL(valueChanged(int)), SLOT(update_image()));
    connect(m_apertureSlider, SIGNAL(valueChanged(int)), SLOT(update_image()));

    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);
    QHBoxLayout *h = new QHBoxLayout(widget);
    h->addWidget(m_imageWidget, 9);

    QVBoxLayout *v1 = new QVBoxLayout;
    v1->addWidget(m_blurSlider);
    v1->addWidget(m_noiseSlider);
    v1->addWidget(m_cannyThreshold1Slider);
    v1->addWidget(m_cannyThreshold2Slider);
    v1->addWidget(m_apertureSlider);
    v1->addSpacerItem(new QSpacerItem(0, 200, QSizePolicy::Ignored, QSizePolicy::Expanding));

    h->addLayout(v1, 3);

    update_image();
}

MainWindow::~MainWindow()
{
}

void MainWindow::init_menuBar()
{
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QAction *act = nullptr;

    /* file menu */
    QMenu *fileMenu = menuBar->addMenu(tr("File"));
    fileMenu->addAction(tr("Open"), this, SLOT(open_file()), QKeySequence(Qt::CTRL+Qt::Key_O));
    fileMenu->addAction(tr("Quit"), this, SLOT(close()), QKeySequence(Qt::CTRL+Qt::Key_Q));

    /* image menu */
    QMenu *imageMenu = menuBar->addMenu(tr("Image"));
    imageMenu->addSection(tr("Tranform"));
    imageMenu->addAction(tr("Flip Horizontal"), this, SLOT(flip_horizontal()));
    imageMenu->addAction(tr("Flip Vertical"), this, SLOT(flip_vertical()));

    /* operator menu */
    QMenu *filtersMenu = menuBar->addMenu(tr("Filters"));
    QActionGroup *actGroup = new QActionGroup(this);

    act = filtersMenu->addAction(tr("Normal"), this, SLOT(normal_image()));
    actGroup->addAction(act);
    act->setCheckable(true);
    act->setChecked(true);

    filtersMenu->addSection(tr("Blur"));
    act = filtersMenu->addAction(tr("Homogeneous"), this, SLOT(homogeneous_blur()));
    actGroup->addAction(act);
    act->setCheckable(true);

    act = filtersMenu->addAction(tr("Gaussian"), this, SLOT(gaussian_blur()));
    act->setCheckable(true);
    actGroup->addAction(act);

    act = filtersMenu->addAction(tr("Median"), this, SLOT(median_blur()));
    act->setCheckable(true);
    actGroup->addAction(act);

    act = filtersMenu->addAction(tr("Bilateral"), this, SLOT(bilateral_blur()));
    act->setCheckable(true);
    actGroup->addAction(act);

    filtersMenu->addSection(tr("Noise"));

    act = filtersMenu->addAction(tr("Gaussian"), this, SLOT(gaussian_noise()));
    actGroup->addAction(act);
    act->setCheckable(true);

    filtersMenu->addSeparator();
    act = filtersMenu->addAction(tr("Erode"), this, SLOT(erode_image()));
    actGroup->addAction(act);
    act->setCheckable(true);

    filtersMenu->addSeparator();
    act = filtersMenu->addAction(tr("Canny"), this, SLOT(canny_image()));
    actGroup->addAction(act);
    act->setCheckable(true);

    filtersMenu->addSeparator();
    act = filtersMenu->addAction(tr("Mirror"), this, SLOT(flip_horizontal()));
    actGroup->addAction(act);
    act->setCheckable(true);
}

void MainWindow::open_file()
{
    QString name = QFileDialog::getOpenFileName(this, tr("Open File"), ".", QString("*.jpg"));
    if (name.isEmpty()) {
        return;
    }
    m_src = imread(name.toStdString(), IMREAD_COLOR);
    normal_image();
}

void MainWindow::update_image()
{
    QTime t;
    t.start();
    int blurRatio = ((m_blurSlider->value()>>1)<<1)+1;
    if (m_opType == Homogeneous) {
        blur(m_src, m_dst, Size(blurRatio, blurRatio));
    } else if (m_opType == Gaussian) {
        GaussianBlur(m_src, m_dst, Size(blurRatio, blurRatio), 0, 0);
    } else if (m_opType == Median) {
        medianBlur(m_src, m_dst, blurRatio);
    } else if (m_opType == Bilateral) {
        bilateralFilter(m_src, m_dst, blurRatio, blurRatio*2.0, blurRatio/2.0);
    } else if (m_opType == Noise) {
        int ratio = m_noiseSlider->value();
        Mat noise = Mat::zeros(m_src.size(), m_src.type());
        randn(noise, ratio, ratio<<1);
        add(m_src, noise, m_dst);
    } else if (m_opType == Erode){
        Mat element = getStructuringElement(MORPH_RECT, Size(blurRatio, blurRatio));
        erode(m_src, m_dst, element);
    } else if (m_opType == CannyImage) {
        int threshold1 = m_cannyThreshold1Slider->value();
        int threshold2 = m_cannyThreshold2Slider->value();
        int aperture = m_apertureSlider->value();
        Mat grayImage;
        cvtColor(m_src, grayImage, COLOR_BGR2GRAY);
        blur(grayImage, m_dst, Size(blurRatio, blurRatio));
        Canny(m_dst, m_dst, threshold1, threshold2, aperture);
    } else {
        m_dst = m_src.clone();
    }

    qDebug("%s Times: %d (ms)",m_title.toUtf8().data(), t.elapsed());
    putText(m_dst, m_title.toStdString(),
            Point(0, 25),
            FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));

    t.restart();
    m_imageWidget->set_image(cvMat2QImage(m_dst));
    qDebug("Convert Times: %d (ms)", t.elapsed());
}

void MainWindow::normal_image()
{
    m_opType = Normal;
    m_blurSlider->setValue(1);
    m_dst = m_src.clone();
    m_title = tr("Normal");

    update_image();
}

void MainWindow::homogeneous_blur()
{
    m_opType = Homogeneous;
    m_title = tr("Homogeneous Blur");

    update_image();
}

void MainWindow::gaussian_blur()
{
    m_opType = Gaussian;
    m_title = tr("Gauusian Blur");
    update_image();
}

void MainWindow::median_blur()
{
    m_opType = Median;
    m_title = tr("Median Blur");
    update_image();
}

void MainWindow::bilateral_blur()
{
    m_opType = Bilateral;
    m_title = tr("Bilateral Blur");
    update_image();
}

void MainWindow::gaussian_noise()
{
    m_opType = Noise;
    m_title = tr("Gaussian Noise");
    update_image();
}

void MainWindow::erode_image()
{
    m_opType = Erode;
    m_title = tr("Erode");
    update_image();
}

void MainWindow::canny_image()
{
    m_opType = CannyImage;
    m_title = tr("Canny");
    update_image();
}

void MainWindow::flip_horizontal()
{
    flip(m_src, m_src, 1);
    update_image();
}

void MainWindow::flip_vertical()
{
    flip(m_src, m_src, 0);
    update_image();
}

void MainWindow::wheelEvent(QWheelEvent *e)
{
    if (e->delta() < 0) {
        m_blurSlider->setValue(m_blurSlider->value()+2);
    } else {
        m_blurSlider->setValue(m_blurSlider->value()-2);
    }
    QMainWindow::wheelEvent(e);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    qDebug("%d, %d", event->size().width(), event->size().height());
    QMainWindow::resizeEvent(event);
}
