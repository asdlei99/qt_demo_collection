#include "opengl_widget.h"
#include "triangle_engine.h"

#include <QTimer>
#include <QOpenGLTexture>

OpenGLWidget::OpenGLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    m_triangleEngine(NULL),
    m_texture(NULL)
{
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    if (m_triangleEngine) {
        delete m_triangleEngine;
    }
    if (m_texture) {
        delete m_texture;
    }
    doneCurrent();
}

void OpenGLWidget::set_texture(const QString &filename)
{
    if (m_texture) {
        delete m_texture;
    }
    m_texture = create_texture(filename);
    update();
}

void OpenGLWidget::init_program(QOpenGLShaderProgram &program,
                                const QString vshader,
                                const QString fshader)
{
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, vshader)) {
        qDebug("%s(%s)[%d]", __FILE__, __func__, __LINE__);
        close();
    }

    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, fshader)) {
        qDebug("%s(%s)[%d]", __FILE__, __func__, __LINE__);
        close();
    }

    if (!program.link()) {
        qDebug("%s(%s)[%d]", __FILE__, __func__, __LINE__);
        close();
    }

    if (!program.bind()) {
        qDebug("%s(%s)[%d]", __FILE__, __func__, __LINE__);
        close();
    }
}

QOpenGLTexture* OpenGLWidget::create_texture(const QString &filename)
{
    QOpenGLTexture *texture = new QOpenGLTexture(QImage(filename).mirrored());
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
    return texture;
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

    init_program(m_program, ":/vshader.glsl", ":/fshader.glsl");

    m_texture = create_texture("://resource/wall.jpg");
    m_program.setUniformValue("texture", 0);

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

    m_program.bind();
    m_texture->bind(0);
    if (m_triangleEngine) {
        m_triangleEngine->draw();
    }
}
