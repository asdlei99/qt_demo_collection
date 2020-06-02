#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);

    void set_image(const QImage &image);
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *e);

private:
    QImage m_image;
};

#endif // WIDGET_H
