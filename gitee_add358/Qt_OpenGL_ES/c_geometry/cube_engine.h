#ifndef CUBE_ENGINE_H
#define CUBE_ENGINE_H

#include "geometry_engine.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class CubeEngine : protected GeometryEngine
{
public:
    explicit CubeEngine(QOpenGLShaderProgram &program);

    void draw();
};

#endif // CUBE_ENGINE_H
