#ifndef TRIANGLE_ENGINE_H
#define TRIANGLE_ENGINE_H

#include "geometry_engine.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class TriangleEngine : protected GeometryEngine
{
public:
    explicit TriangleEngine(QOpenGLShaderProgram &program);
    ~TriangleEngine();

    void draw();

private:
    QOpenGLVertexArrayObject m_vao1;
    QOpenGLBuffer m_vbo1;
    QOpenGLVertexArrayObject m_vao2;
    QOpenGLBuffer m_vbo2;
};

#endif // TRIANGLE_ENGINE_H
