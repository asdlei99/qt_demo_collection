#ifndef GEOMETRY_ENGINE_H
#define GEOMETRY_ENGINE_H

#include <QOpenGLFunctions>

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
};

#endif // GEOMETRY_ENGINE_H
