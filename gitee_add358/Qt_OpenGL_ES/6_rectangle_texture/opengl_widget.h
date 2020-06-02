#ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class QOpenGLTexture;
class RectangleEngine;
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = 0);
    virtual ~OpenGLWidget();

    void set_texture(const QString &filename);

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
    RectangleEngine *m_triangleEngine;
    QOpenGLTexture *m_texture1;
    QOpenGLTexture *m_texture2;
};

#endif // OPENGL_WIDGET_H
