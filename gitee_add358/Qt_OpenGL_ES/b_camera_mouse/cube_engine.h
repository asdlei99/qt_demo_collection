#ifndef CUBE_ENGINE_H
#define CUBE_ENGINE_H

#include "geometry_engine.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class cubeEngine : protected GeometryEngine
{
public:
    explicit cubeEngine(QOpenGLShaderProgram &program);
    ~cubeEngine();

    void draw();

private:
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
};

#endif // CUBE_ENGINE_H
