#include "rectangle_engine.h"
#include <QOpenGLBuffer>

RectangleEngine::RectangleEngine(QOpenGLShaderProgram &program) :
    m_ebo(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();
    m_vbo.create();
    m_ebo.create();

    /* 默认按逆时针方向顺序绘制, 调用glFrontFace(GL_CW)可调用其顺序 */
    GLfloat vertices[] = {
        -0.5, 0.5, 0.0,
        -0.5, -0.5, 0.0,
        0.5, -0.5, 0.0,
        0.5, 0.5, 0.0,
    };
    m_vbo.bind();
    m_vbo.allocate(vertices, sizeof(vertices));
    int pos = program.attributeLocation("a_position");
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(pos);

    unsigned int indices[] = {
        0, 1, 3,
        3, 1, 2
    };
    m_ebo.bind();
    m_ebo.allocate(indices, sizeof(indices));
}

RectangleEngine::~RectangleEngine()
{
    m_vbo.destroy();
}

void RectangleEngine::draw()
{
    m_ebo.bind();
    m_vbo.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
