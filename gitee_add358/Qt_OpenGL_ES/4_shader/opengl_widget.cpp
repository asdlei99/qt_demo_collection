#include "opengl_widget.h"
#include "triangle_engine.h"
#include <QTimer>
OpenGLWidget::OpenGLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    m_triangleEngine(NULL)
{
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    if (m_triangleEngine) {
        delete m_triangleEngine;
    }
    doneCurrent();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //指定混合函数
    glEnable(GL_BLEND);

    const GLubyte *version = glGetString(GL_VERSION);
    qDebug("%s(%s)[%d] %s", __FILE__, __func__, __LINE__, version);

    int attributeQty = 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributeQty);
    qDebug("%s(%s)[%d] Max Vertex Attributes: %d", __FILE__, __func__, __LINE__, attributeQty);

    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/vshader.glsl")) {
        qDebug("%s(%s)[%d]", __FILE__, __func__, __LINE__);
        close();
    }

    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/fshader.glsl")) {
        qDebug("%s(%s)[%d]", __FILE__, __func__, __LINE__);
        close();
    }

    if (!m_program.link()) {
        qDebug("%s(%s)[%d]", __FILE__, __func__, __LINE__);
        close();
    }

    if (!m_program.bind()) {
        qDebug("%s(%s)[%d]", __FILE__, __func__, __LINE__);
        close();
    }

    m_triangleEngine = new TriangleEngine(m_program);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // 清除屏幕颜色
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_triangleEngine) {
        m_triangleEngine->draw();
    }
}
