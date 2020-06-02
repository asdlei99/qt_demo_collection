#include "circle_engine.h"
#include <qmath.h>

CircleEngine::CircleEngine(QOpenGLShaderProgram &program) :
    GeometryEngine(program),
    m_vertexQty(0)
{
    Vertice v;
    QVector<Vertice> vertices;
    v.position = Position(0.0f, 0.0f, 0.0f);
    v.texcoord = Texcoord(0.5, 0.5);
    vertices.append(v);
    for (float i = 360.00f; i >= 0.00; i -= 5.00) {
        v.position.x = qSin(qDegreesToRadians(i));
        v.position.y = qCos(qDegreesToRadians(i));
        v.texcoord.x = (v.position.x+1)/2;
        v.texcoord.y = (v.position.y+1)/2;
        vertices.append(v);
    }

    m_vertexQty = vertices.count();
    QOpenGLVertexArrayObject::Binder vaoBind(&m_vao);
    m_vbo.bind();
    m_vbo.allocate(vertices.data(), vertices.size()*sizeof(Vertice));
    int pos = program.attributeLocation("a_position");
    program.setAttributeBuffer(pos, GL_FLOAT, 0, 3, sizeof(Vertice));
    program.enableAttributeArray(pos);
    pos = program.attributeLocation("a_texcoord");
    program.setAttributeBuffer(pos, GL_FLOAT, sizeof(Position), 2, sizeof(Vertice));
    program.enableAttributeArray(pos);
    m_vbo.release();
}

void CircleEngine::draw()
{
    m_program.setUniformValue("model", m_model);
    QOpenGLVertexArrayObject::Binder vaoBind(&m_vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertexQty);
}

void CircleEngine::translate(const QVector3D &vector)
{
    m_model.translate(vector);
}

void CircleEngine::rotate(float angle, float x, float y, float z)
{
    m_model.rotate(angle, x, y, z);
}
