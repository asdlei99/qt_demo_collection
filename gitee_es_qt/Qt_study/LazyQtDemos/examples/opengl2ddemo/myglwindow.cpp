#include "myglwindow.h"

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QPainter>

MyGLWindow::MyGLWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
//    format.setVersion(3, 2);
//    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    QSurfaceFormat::setDefaultFormat(format);
}

MyGLWindow::~MyGLWindow()
{

}

void MyGLWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 0.8f);
}


void MyGLWindow::resizeGL(int w, int h)
{
    // Update projection matrix and other size related settings:
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);

}

void MyGLWindow::paintGL()
{
    QPainter painter(this);
    // painter->setViewport(50,50,100,100);
//    painter.beginNativePainting();
    QOpenGLShaderProgram  program;
    program.addShaderFromSourceCode(QOpenGLShader::Vertex,
        "attribute highp vec4 vertex;\n"
        "uniform highp mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "   gl_Position = matrix * vertex;\n"
        "}");
    program.addShaderFromSourceCode(QOpenGLShader::Fragment,
        "uniform mediump vec4 color;\n"
        "void main(void)\n"
        "{\n"
        "   gl_FragColor = color;\n"
        "}");
    program.link();
    program.bind();

    int vertexLocation = program.attributeLocation("vertex");
    int matrixLocation = program.uniformLocation("matrix");
    int colorLocation = program.uniformLocation("color");

    static GLfloat const triangleVertices[] = {
        60.0f,  10.0f,  0.0f,
        110.0f, 110.0f, 0.0f,
        10.0f,  110.0f, 0.0f
    };
//    static const GLfloat triangleVertices[] =
//    {
//        0.0f,1.0f,-1.0f,1.0f,
//        1.0f,1.0f,-1.0f,1.0f,
//        1.0f,0.0f,-1.0f,1.0f,
//    };

    QColor color(0, 255, 0, 255);

    QMatrix4x4 pmvMatrix;
    pmvMatrix.ortho(rect());

    program.enableAttributeArray(vertexLocation);    // enable -->
    program.setAttributeArray(vertexLocation, triangleVertices, 3);
    program.setUniformValue(matrixLocation, pmvMatrix);
    program.setUniformValue(colorLocation, color);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    program.disableAttributeArray(vertexLocation);    // disable -->


//    painter.endNativePainting();

    painter.drawText(50,100,"Look This!");
}
