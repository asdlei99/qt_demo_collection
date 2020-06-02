#ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

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

    void update_cameraPos();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QOpenGLShaderProgram m_program;
    QMatrix4x4 m_projection;
    cubeEngine *m_cube;
    QOpenGLTexture *m_texture1;
    QOpenGLTexture *m_texture2;
    QVector3D m_cameraPos;
    QVector3D m_cameraFront;
    QVector3D m_cameraUp;
    int m_activeCube;
    QVector<float> m_angles;
    bool m_moveUp;
    bool m_moveDown;
    bool m_moveRight;
    bool m_moveLeft;
};

#endif // OPENGL_WIDGET_H
