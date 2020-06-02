#include "triangle_engine.h"
#include <QOpenGLBuffer>

TriangleEngine::TriangleEngine(QOpenGLShaderProgram &program)
{
    initializeOpenGLFunctions();
    m_vbo1.create();
    m_vbo2.create();
    /* 默认按逆时针方向顺序绘制, 调用glFrontFace(GL_CW)可调用其顺序 */
    GLfloat vertices[] = {
        // position          color
        0.0f,  0.5f,  0.0f,  1.0, 0.0, 0.0,
       -0.5f, -0.5f,  0.0f,  0.0, 1.0, 0.0,
        0.5f, -0.5f,  0.0f,  0.0, 0.0, 1.0
    };

    m_vao1.create();
    QOpenGLVertexArrayObject::Binder vaoBind(&m_vao1);

    m_vbo1.bind();
    m_vbo1.allocate(vertices, sizeof(vertices));
    int pos = program.attributeLocation("a_position");
    program.setAttributeBuffer(pos,GL_FLOAT, 0, 3, 6*sizeof(float));
    program.enableAttributeArray(pos);
    pos = program.attributeLocation("a_color");
    program.setAttributeBuffer(pos, GL_FLOAT, 3*sizeof(float), 3, 6*sizeof(float));
    program.enableAttributeArray(pos);

    m_vbo1.release();

    GLfloat vertices2[] = {-1.0, 0.5, 0.0,
                           -0.75, 0, 0.0,
                           -0.5, 0.5, 0.0};
    m_vao2.create();
    QOpenGLVertexArrayObject::Binder vaoBind2(&m_vao2);
    m_vbo2.bind();
    m_vbo2.allocate(vertices2, sizeof(vertices2));
    pos = program.attributeLocation("a_position");
    program.setAttributeBuffer(pos, GL_FLOAT, 0, 3, 3*sizeof(float));
    program.enableAttributeArray(pos);
    pos = program.attributeLocation("a_color");
    program.setAttributeBuffer(pos, GL_FLOAT, 0, 3, 3*sizeof(float));
    program.enableAttributeArray(pos);

    m_vbo2.release();
}

TriangleEngine::~TriangleEngine()
{
    m_vbo1.destroy();
    m_vbo2.destroy();
    m_vao1.destroy();
}

void TriangleEngine::draw()
{
    QOpenGLVertexArrayObject::Binder vaoBind(&m_vao1);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    QOpenGLVertexArrayObject::Binder vaoBind2(&m_vao2);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
