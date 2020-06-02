#ifndef MYGLWINDOW_H
#define MYGLWINDOW_H

#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QWidget>

class MyGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    MyGLWindow(QWidget *parent = nullptr);
    ~MyGLWindow();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
//    QOpenGLVertexArrayObject m_vao;
    QMatrix4x4 m_projection;
};


#endif // MYGLWINDOW_H
