#ifndef RECTANGLE_ENGINE_H
#define RECTANGLE_ENGINE_H

#include "geometry_engine.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class RectangleEngine : protected GeometryEngine
{
public:
    explicit RectangleEngine(QOpenGLShaderProgram &program);
    ~RectangleEngine();

    void draw();

private:
    QOpenGLVertexArrayObject m_vao1;
    QOpenGLBuffer m_vbo1;
    QOpenGLBuffer m_ebo1;
    QOpenGLVertexArrayObject m_vao2;
    QOpenGLBuffer m_vbo2;
};

#endif // RECTANGLE_ENGINE_H
