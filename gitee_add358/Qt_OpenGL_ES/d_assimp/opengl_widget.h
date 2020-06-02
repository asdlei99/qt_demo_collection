#ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "camera.h"

class Model;
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = 0);
    virtual ~OpenGLWidget();

    void load_model(const QString &filename);

protected:
    void init_program(QOpenGLShaderProgram &program,
                      const QString vshader,
                      const QString fshader);

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QOpenGLShaderProgram m_program;
    QMatrix4x4 m_projection;
    Camera m_camera;
    QMatrix4x4 m_matrixModel;

    Model *m_model;

    QVector2D m_lastMousePos;
    QQuaternion m_quaternion;
};

#endif // OPENGL_WIDGET_H
