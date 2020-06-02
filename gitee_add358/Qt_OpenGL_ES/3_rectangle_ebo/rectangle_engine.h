#ifndef TRIANGLE_ENGINE_H
#define TRIANGLE_ENGINE_H

#include "geometry_engine.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class RectangleEngine : protected GeometryEngine
{
public:
    explicit RectangleEngine(QOpenGLShaderProgram &program);
    ~RectangleEngine();

    void draw();

private:
    QOpenGLBuffer m_vbo;
    QOpenGLBuffer m_ebo;
};

#endif // TRIANGLE_ENGINE_H
