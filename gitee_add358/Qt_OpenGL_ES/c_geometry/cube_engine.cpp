#include "cube_engine.h"
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

CubeEngine::CubeEngine(QOpenGLShaderProgram &program) :
    GeometryEngine(program)
{
    /* 默认按逆时针方向顺序绘制, 调用glFrontFace(GL_CW)可调用其顺序 */
    GLfloat vertices[] = {
        // Position         texcoords
        /* face 1 */
        -0.5, 0.5, 0.5, 0.0, 1.0,
        -0.5,-0.5, 0.5, 0.0, 0.0,
         0.5,-0.5, 0.5, 1.0, 0.0,
        -0.5, 0.5, 0.5, 0.0, 1.0,
         0.5,-0.5, 0.5, 1.0, 0.0,
         0.5, 0.5, 0.5, 1.0, 1.0,
        /* face 2 */
         0.5, 0.5, 0.5, 0.0, 1.0,
         0.5,-0.5, 0.5, 0.0, 0.0,
         0.5,-0.5,-0.5, 1.0, 0.0,
         0.5, 0.5, 0.5, 0.0, 1.0,
         0.5,-0.5,-0.5, 1.0, 0.0,
         0.5, 0.5,-0.5, 1.0, 1.0,
        /* face 3 */
         0.5, 0.5,-0.5, 0.0, 1.0,
         0.5,-0.5,-0.5, 0.0, 0.0,
        -0.5,-0.5,-0.5, 1.0, 0.0,
         0.5, 0.5,-0.5, 0.0, 1.0,
        -0.5,-0.5,-0.5, 1.0, 0.0,
        -0.5, 0.5,-0.5, 1.0, 1.0,
        /* face 4 */
        -0.5, 0.5,-0.5, 0.0, 1.0,
        -0.5,-0.5,-0.5, 0.0, 0.0,
        -0.5,-0.5, 0.5, 1.0, 0.0,
        -0.5, 0.5,-0.5, 0.0, 1.0,
        -0.5,-0.5, 0.5, 1.0, 0.0,
        -0.5, 0.5, 0.5, 1.0, 1.0,
        /* face 5 */
        -0.5, 0.5,-0.5, 0.0, 1.0,
        -0.5, 0.5, 0.5, 0.0, 0.0,
         0.5, 0.5, 0.5, 1.0, 0.0,
        -0.5, 0.5,-0.5, 0.0, 1.0,
         0.5, 0.5, 0.5, 1.0, 0.0,
         0.5, 0.5,-0.5, 1.0, 1.0,
        /* face 6 */
        -0.5,-0.5, 0.5, 0.0, 1.0,
        -0.5,-0.5,-0.5, 0.0, 0.0,
         0.5,-0.5,-0.5, 1.0, 0.0,
        -0.5,-0.5, 0.5, 0.0, 1.0,
         0.5,-0.5,-0.5, 1.0, 0.0,
         0.5,-0.5, 0.5, 1.0, 1.0,
    };

    QOpenGLVertexArrayObject::Binder vaoBind(&m_vao);
    m_vbo.bind();
    m_vbo.allocate(vertices, sizeof(vertices));
    int pos = program.attributeLocation("a_position");
    program.setAttributeBuffer(pos, GL_FLOAT, 0, 3, 5*sizeof(float));
    program.enableAttributeArray(pos);
    pos = program.attributeLocation("a_texcoord");
    program.setAttributeBuffer(pos, GL_FLOAT, 3*sizeof(float), 2, 5*sizeof(float));
    program.enableAttributeArray(pos);
    m_vbo.release();
}

void CubeEngine::draw()
{
    QOpenGLVertexArrayObject::Binder vaoBind(&m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
