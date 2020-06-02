#include "cylinder_engine.h"
#include "circle_engine.h"
#include <qmath.h>
CylinderEngine::CylinderEngine(QOpenGLShaderProgram &program) :
    GeometryEngine(program),
    m_ebo(QOpenGLBuffer::IndexBuffer),
    m_triangleQty(0)
{
    Vertice v;
    QVector<Vertice> vertices;

    float step = 5.0;
    float ratio = 1.0 / 360.0;
    for (float i = 0;  i <= 360.00; i += step) {
        v.position.x = qSin(qDegreesToRadians(i));
        v.position.y = qCos(qDegreesToRadians(i));
        v.position.z = 0;
        v.texcoord.x = 0;
        v.texcoord.y = ratio * i;
        vertices.append(v);
        v.position.z = -2;
        v.texcoord.x = 1;
        vertices.append(v);
    }

    m_triangleQty = vertices.count() - 2;
    unsigned int indices[m_triangleQty*3] = {0};
    for (int i = 0; i < m_triangleQty; ++i) {
        indices[i*3] = i;
        indices[i*3+1] = i+1+i%2;
        indices[i*3+2] = i+2-i%2;
    }

    m_ebo.create();

    QOpenGLVertexArrayObject::Binder bind(&m_vao);
    m_vbo.bind();
    m_vbo.allocate(vertices.data(), vertices.size()*sizeof(Vertice));
    int pos = program.attributeLocation("a_position");
    program.setAttributeBuffer(pos, GL_FLOAT, 0, 3, sizeof(Vertice));
    program.enableAttributeArray(pos);
    pos = program.attributeLocation("a_texcoord");
    program.setAttributeBuffer(pos, GL_FLOAT, sizeof(Position), 2, sizeof(Vertice));
    program.enableAttributeArray(pos);
    m_vbo.release();

    m_ebo.bind();
    m_ebo.allocate(indices, sizeof(indices));
}

CylinderEngine::~CylinderEngine()
{
    m_ebo.destroy();
}

void CylinderEngine::draw()
{
    m_program.setUniformValue("model", m_model);
    QOpenGLVertexArrayObject::Binder bind(&m_vao);
    glDrawElements(GL_TRIANGLES, m_triangleQty*3, GL_UNSIGNED_INT, 0);
}
