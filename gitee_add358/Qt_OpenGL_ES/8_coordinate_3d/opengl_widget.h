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

private:
    QOpenGLShaderProgram m_program;
    QMatrix4x4 m_projection;
    cubeEngine *m_cube;
    QOpenGLTexture *m_texture1;
    QOpenGLTexture *m_texture2;
    int m_activeCube;
    QVector<float> m_angles;
};

#endif // OPENGL_WIDGET_H
