#ifndef MESH_H
#define MESH_H

#include <QVector>
#include <QVector3D>
#include <QVector2D>

#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include <QSharedPointer>
#include <QOpenGLTexture>

struct Vertex
{
    QVector3D position;
    QVector3D normal;
    QVector2D texCoords;
    QVector3D tangent;
    QVector3D bitangent;
};

struct Texture
{
    Texture() : t(NULL) {}
    QOpenGLTexture *t;
    QString type;
    QString path;
};

class Mesh : protected QOpenGLFunctions
{
public:
    Mesh(const QVector<Vertex> &vertices,
         const QVector<unsigned int> &indices,
         const QVector<Texture> &textures,
         QOpenGLShaderProgram &shader);
    ~Mesh();

    void draw();

protected:
    void setup();

private:
    QOpenGLShaderProgram &m_shader;
    QVector<Vertex> m_vertices;
    QVector<unsigned int> m_indices;
    QVector<Texture> m_textures;

    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLBuffer m_ebo;
};

typedef QSharedPointer<Mesh> MeshPointer;

#endif // MESH_H
