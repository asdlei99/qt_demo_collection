#include <QLineEdit>
#include <QSlider>
#include <QPushButton>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "movieview.h"

//start id="slider"

MovieView::MovieView() {
    resize(200, 200);
    
    slider = new QSlider(Qt::Vertical);
    slider->setRange(1,500);
    slider->setTickInterval(10);
    slider->setValue(100);
    slider->setToolTip("How fast is it spinning?");
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setDelay(int)));
    QDockWidget *qdw = new QDockWidget("Delay");
    qdw->setWidget(slider);
    addDockWidget(Qt::LeftDockWidgetArea, qdw);
    label = new QLabel("Movie");
    setCentralWidget(label);
    
}
//end
//start id="slots"
void MovieView::showPix(const QPixmap* pic) {
    label->setPixmap(*pic);
}


void MovieView::setDelay(int newValue) {
    QString str;
    str = QString("%1ms delay between frames").arg(newValue);
    slider->setToolTip(str);
    emit intervalChanged(newValue);
}

//end
