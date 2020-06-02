#ifndef TRIANGLE_ENGINE_H
#define TRIANGLE_ENGINE_H

#include "geometry_engine.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class TriangleEngine : protected GeometryEngine
{
public:
    explicit TriangleEngine();
    ~TriangleEngine();

    void draw(QOpenGLShaderProgram &program);

private:
    QOpenGLBuffer m_buffer;
};

#endif // TRIANGLE_ENGINE_H
