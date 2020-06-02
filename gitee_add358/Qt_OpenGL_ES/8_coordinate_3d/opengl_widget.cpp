#include "opengl_widget.h"
#include "cube_engine.h"

#include <QTimer>
#include <QOpenGLTexture>

OpenGLWidget::OpenGLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    m_cube(NULL),
    m_texture1(NULL),
    m_texture2(NULL),
    m_activeCube(0)
{
    m_angles.resize(10);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
            SLOT(update()));
    timer->start(40);
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    if (m_cube) {
        delete m_cube;
    }
    if (m_texture1) {
        delete m_texture1;
    }
    if (m_texture2) {
        delete m_texture2;
    }
    doneCurrent();
}

void OpenGLWidget::set_texture(const QString &filename)
{
    if (m_texture1) {
        m_texture1->release();
        m_texture1->destroy();
        delete m_texture1;
    }
    m_texture1 = create_texture(filename);
    m_texture1->bind(0);
    update();
}

void OpenGLWidget::set_active_cube(int i)
{
    if (i >= m_angles.size()) {
        return;
    }
    m_activeCube = i;
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

    init_program(m_program, ":/resource/shader/vshader.glsl", ":/resource/shader/fshader.glsl");

    m_texture1 = create_texture(":/resource/texture/wall.jpg");
    m_program.setUniformValue("texture1", 0);
    m_texture1->bind(0);

    m_texture2 = create_texture(":/resource/texture/face.png");
    m_program.setUniformValue("texture2", 1);
    m_texture2->bind(1);

    m_cube = new cubeEngine(m_program);

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

    QMatrix4x4 view;
    view.translate(0.0, 0.0, -3.0);
    m_program.setUniformValue("view", view);

    QMatrix4x4 projection;
    projection.perspective(45, 1.0*size().width()/size().height(), 0.1, 100.0);
    m_program.setUniformValue("projection", projection);

    QVector3D cubePositions[] = {
      QVector3D( 0.0f,  0.0f,  0.0f),
      QVector3D( 2.0f,  5.0f, -15.0f),
      QVector3D(-1.5f, -2.2f, -2.5f),
      QVector3D(-3.8f, -2.0f, -12.3f),
      QVector3D( 2.4f, -0.4f, -3.5f),
      QVector3D(-1.7f,  3.0f, -7.5f),
      QVector3D( 1.3f, -2.0f, -2.5f),
      QVector3D( 1.5f,  2.0f, -2.5f),
      QVector3D( 1.5f,  0.2f, -1.5f),
      QVector3D(-1.3f,  1.0f, -1.5f)
    };

    m_texture1->bind(0);
    m_texture2->bind(1);

    for (int i = 0; i < 10; ++i) {
        QMatrix4x4 model;
        model.translate(cubePositions[i]);
        model.rotate(20.0*i+m_angles[i], 1.0, 0.3, 0.5);
        m_program.setUniformValue("model", model);
        m_cube->draw();
    }
    m_angles[m_activeCube] += 1.5;
}
