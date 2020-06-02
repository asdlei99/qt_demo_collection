#ifndef GEOMETRY_ENGINE_H
#define GEOMETRY_ENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

struct Position
{
    Position(GLfloat x, GLfloat y, GLfloat z) :
        x(x), y(y), z(z)
    {}
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct Texcoord
{
    Texcoord(GLfloat x, GLfloat y) :
        x(x), y(y)
    {}
    GLfloat x;
    GLfloat y;
};

struct Vertice
{
    Vertice() :
        position(0.0, 0.0, 0.0),
        texcoord(0.0, 0.0)
    {}
    Position position;
    Texcoord texcoord;
};

class GeometryEngine : protected QOpenGLFunctions
{
public:
    explicit GeometryEngine(QOpenGLShaderProgram &program);
    virtual ~GeometryEngine();

    virtual void draw() = 0;

protected:
    QOpenGLShaderProgram &m_program;
    QMatrix4x4 m_model;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
};

#endif // GEOMETRY_ENGINE_H
