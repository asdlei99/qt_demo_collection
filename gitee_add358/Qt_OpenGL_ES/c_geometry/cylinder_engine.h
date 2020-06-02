#ifndef CYLINDER_ENGINE_H
#define CYLINDER_ENGINE_H

#include "geometry_engine.h"
#include <QOpenGLShaderProgram>

class CircleEngine;
class CylinderEngine : protected GeometryEngine
{
public:
    explicit CylinderEngine(QOpenGLShaderProgram &program);
    ~CylinderEngine();

    void draw();

private:
    QOpenGLBuffer m_ebo;
    int m_triangleQty;
};

#endif // CYLINDER_ENGINE_H
