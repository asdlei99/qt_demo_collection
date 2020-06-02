#ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "camera.h"

class QOpenGLTexture;
class cubeEngine;
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = 0);
    virtual ~OpenGLWidget();

    void set_texture(const QString &filename);

    void set_active_cube(int i);

protected:
    void init_program(QOpenGLShaderProgram &program,
                      const QString vshader,
                      const QString fshader);
    QOpenGLTexture* create_texture(const QString &filename);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

    void update_camera();

private:
    QOpenGLShaderProgram m_program;
    QMatrix4x4 m_projection;
    cubeEngine *m_cube;
    QOpenGLTexture *m_texture1;
    QOpenGLTexture *m_texture2;
    int m_activeCube;
    QVector<float> m_angles;

    Camera m_camera;
    bool m_moveForward;
    bool m_moveBackward;
    bool m_moveRight;
    bool m_moveLeft;

    bool m_mousePressed;
    QPoint m_lastMousePos;

    double m_yaw;
    double m_pitch;
    double m_fov;
};

#endif // OPENGL_WIDGET_H
