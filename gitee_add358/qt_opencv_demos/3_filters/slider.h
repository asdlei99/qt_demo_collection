#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>

class QSlider;
class Slider : public QWidget
{
    Q_OBJECT
public:
    Slider(const QString &title, int min, int max, int step, QWidget *parent = nullptr);

    int value() const;

    void setValue(int i);

signals:
    void valueChanged(int);

private:
    QSlider *m_slider;
};

#endif // SLIDER_H
