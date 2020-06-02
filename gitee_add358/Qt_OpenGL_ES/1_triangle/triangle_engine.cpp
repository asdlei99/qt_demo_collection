#include "triangle_engine.h"
#include <QOpenGLBuffer>

TriangleEngine::TriangleEngine()
{
    initializeOpenGLFunctions();
    m_buffer.create();
    /* 默认按逆时针方向顺序绘制, 调用glFrontFace(GL_CW)可调用其顺序 */
    GLfloat vertices[] = {0.0f, 0.5f, 0.0f,
                          -0.5f, -0.5f, 0.0f,
                          0.5f, -0.5f, 0.0f};
    m_buffer.bind();
    m_buffer.allocate(vertices, sizeof(vertices));
}

TriangleEngine::~TriangleEngine()
{
    m_buffer.destroy();
}

void TriangleEngine::draw(QOpenGLShaderProgram &program)
{
    // 方式1
//    m_buffer.bind();
//    program.enableAttributeArray("a_position");
//    program.setAttributeBuffer("a_position", GL_FLOAT, 0, 3, 3*sizeof(float));

//    方式2
    m_buffer.bind();
    int pos = program.attributeLocation("a_position");
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(pos);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}
