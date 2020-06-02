#ifndef MYGL2DWIDGET_H
#define MYGL2DWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_2_Compatibility>

class MyGL2DWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit MyGL2DWidget(QWidget *parent = nullptr);

protected:
    //设置渲染环境
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

private:
    QOpenGLFunctions_3_2_Compatibility *f;
};

#endif // MYGL2DWIDGET_H
