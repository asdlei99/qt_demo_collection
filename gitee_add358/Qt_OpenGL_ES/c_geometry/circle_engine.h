#ifndef CIRCLE_ENGINE_H
#define CIRCLE_ENGINE_H

#include "geometry_engine.h"

#include <QOpenGLShaderProgram>

class CircleEngine : public GeometryEngine
{
public:
    explicit CircleEngine(QOpenGLShaderProgram &program);

    void draw();

    void translate(const QVector3D &vector);

    void rotate(float angle, float x, float y, float z);

private:
    int m_vertexQty;
};

#endif // CIRCLE_ENGINE_H
