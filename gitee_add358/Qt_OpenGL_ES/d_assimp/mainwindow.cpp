#include "mainwindow.h"

#include "opengl_widget.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QPushButton>
#include <QDoubleSpinBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_textureLineEdit(new QLineEdit(this)),
    m_openglWidget(new OpenGLWidget(this))
{
//    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    setMinimumSize(800, 600);

    m_textureLineEdit->setReadOnly(true);
    QToolButton *textureToolBtn = new QToolButton(this);
    connect(textureToolBtn, SIGNAL(clicked(bool)),
            SLOT(do_toolButton_clicked()));

    QDoubleSpinBox *insideSpinBox = new QDoubleSpinBox(this);
    insideSpinBox->setRange(0.001, 10);
    insideSpinBox->setDecimals(2);
    insideSpinBox->setValue(0.5);
    insideSpinBox->setSingleStep(0.01);
    connect(insideSpinBox, SIGNAL(valueChanged(double)),
            SLOT(do_insideSpinBox_changed(double)));

    QDoubleSpinBox *outsideSpinBox = new QDoubleSpinBox(this);
    outsideSpinBox->setRange(0.001, 10);
    outsideSpinBox->setDecimals(2);
    outsideSpinBox->setValue(1.0);
    outsideSpinBox->setSingleStep(0.01);
    connect(outsideSpinBox, SIGNAL(valueChanged(double)),
            SLOT(do_outsideSpinBox_changed(double)));

    QDoubleSpinBox *lengthSpinBox = new QDoubleSpinBox(this);
    lengthSpinBox->setRange(0.01, 10000);
    lengthSpinBox->setDecimals(2);
    lengthSpinBox->setValue(1.0);
    lengthSpinBox->setSingleStep(0.01);
    connect(lengthSpinBox, SIGNAL(valueChanged(double)),
            SLOT(do_lengthSpinBox_changed(double)));

    QDoubleSpinBox *widthSpinBox = new QDoubleSpinBox(this);
    QDoubleSpinBox *heightSpinBox = new QDoubleSpinBox(this);

    QWidget *w = new QWidget(this);
    setCentralWidget(w);

    QHBoxLayout *h1 = new QHBoxLayout;
    h1->addWidget(new QLabel(tr("Model")));
    h1->addWidget(m_textureLineEdit);
    h1->addWidget(textureToolBtn);

    QHBoxLayout *h2 = new QHBoxLayout;
    h2->addWidget(new QLabel(tr("Inside")));
    h2->addWidget(insideSpinBox);

    QHBoxLayout *h3 = new QHBoxLayout;
    h3->addWidget(new QLabel(tr("Outside")));
    h3->addWidget(outsideSpinBox);

    QHBoxLayout *h4 = new QHBoxLayout;
    h4->addWidget(new QLabel(tr("Length")));
    h4->addWidget(lengthSpinBox);

    QHBoxLayout *h5 = new QHBoxLayout;
    h5->addWidget(new QLabel(tr("width")));
    h5->addWidget(widthSpinBox);

    QHBoxLayout *h6 = new QHBoxLayout;
    h6->addWidget(new QLabel(tr("Height")));
    h6->addWidget(heightSpinBox);

    QVBoxLayout *v = new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(h2);
    v->addLayout(h3);
    v->addLayout(h4);
    v->addLayout(h5);
    v->addLayout(h6);
    v->addSpacerItem(new QSpacerItem(0, 800, QSizePolicy::Ignored, QSizePolicy::Expanding));

    QHBoxLayout *h = new QHBoxLayout(w);
    h->addLayout(v, 2);
    h->addWidget(m_openglWidget, 6);
}

MainWindow::~MainWindow()
{
}

void MainWindow::do_toolButton_clicked()
{
    QString name = QFileDialog::getOpenFileName(this, tr("Choose Picture"), "../../",
                                                tr("Images (*.obj)"));
    m_textureLineEdit->setText(name);

    m_openglWidget->load_model(name);
}

void MainWindow::do_insideSpinBox_changed(double v)
{
//    m_openglWidget->set_inside(v);
}

void MainWindow::do_outsideSpinBox_changed(double v)
{
    //    m_openglWidget->set_outside(v);
}

void MainWindow::do_lengthSpinBox_changed(double v)
{
    m_openglWidget->makeCurrent();
    m_openglWidget->doneCurrent();
}

void MainWindow::do_widthSpibBox_changed(double v)
{

}

void MainWindow::do_heightSpibBox_changed(double v)
{

}
