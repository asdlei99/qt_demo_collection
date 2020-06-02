#ifndef MYPAINTGLWIDGET_H
#define MYPAINTGLWIDGET_H

#include <QOpenGLWidget>

class MyHelp;

class MyPaintGlWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit MyPaintGlWidget(MyHelp *helper, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    MyHelp *helper;
};

#endif // MYPAINTGLWIDGET_H
