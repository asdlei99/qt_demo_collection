#ifndef MYPAINTWIDGET_H
#define MYPAINTWIDGET_H

#include <QWidget>

class MyHelp;

class MyPaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyPaintWidget(MyHelp *helper, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    MyHelp *helper;
};

#endif // MYPAINTWIDGET_H
