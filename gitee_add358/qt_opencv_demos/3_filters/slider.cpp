#include "slider.h"

#include <QSlider>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

Slider::Slider(const QString &title, int min, int max, int step, QWidget *parent)
    : QWidget(parent),
      m_slider(new QSlider(Qt::Horizontal, this))
{
    QSpinBox *spinBox = new QSpinBox(this);
    m_slider->setRange(min, max);
    spinBox->setRange(min, max);
    m_slider->setSingleStep(step);
    spinBox->setSingleStep(step);
    QHBoxLayout *h = new QHBoxLayout;
    h->addWidget(new QLabel(title, this), 1);
    h->addWidget(spinBox, 5);
    QVBoxLayout *v = new QVBoxLayout(this);
    v->addLayout(h);
    v->addWidget(m_slider);

    connect(m_slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
    connect(spinBox, SIGNAL(valueChanged(int)), m_slider, SLOT(setValue(int)));

    connect(m_slider, SIGNAL(valueChanged(int)), SIGNAL(valueChanged(int)));
}

int Slider::value() const
{
    return m_slider->value();
}

void Slider::setValue(int i)
{
    m_slider->setValue(i);
}
