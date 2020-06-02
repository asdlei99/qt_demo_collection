#include "opengl_widget.h"

#include "model.h"

#include <QTimer>
#include <QDateTime>
#include <QOpenGLTexture>
#include <QKeyEvent>

OpenGLWidget::OpenGLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    m_model(NULL)
{
    setFocusPolicy(Qt::WheelFocus);
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    delete m_model;
    doneCurrent();
}

void OpenGLWidget::load_model(const QString &filename)
{
    makeCurrent();
    if (m_model) {
        delete m_model;
    }
    m_model = new Model(m_program, filename);
    update();
    doneCurrent();
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

void OpenGLWidget::mousePressEvent(QMouseEvent *e)
{
    m_lastMousePos = QVector2D(e->localPos());
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - m_lastMousePos;
    m_lastMousePos = QVector2D(e->localPos());

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal angularSpeed = diff.length() / 3;

    // Update rotation
    m_quaternion = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * m_quaternion;
    m_matrixModel.setToIdentity();
    m_matrixModel.rotate(m_quaternion);
    m_matrixModel.translate(0.0, -1.75, 0.0);
    m_matrixModel.scale(0.2, 0.2, 0.2);
    update();
}

void OpenGLWidget::wheelEvent(QWheelEvent *e)
{
    if (e->delta() < 0) {
        m_camera.backward();
    } else {
        m_camera.forward();
    }

    update();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);    //启用深度测试。
//    glEnable(GL_BLEND);         // 启用颜色混合。用于实现半透明效果
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //指定混合函数
    glFrontFace(GL_CW);         //默认按逆时针方向(GL_CCW)顺序绘制
//    glEnable(GL_CULL_FACE);   // 启用多边形背面消除特性
#if (QT_VERSION > QT_VERSION_CHECK(5, 5, 0))
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);    //使用OpenGL的硬件加速来生成所需要的纹理
#endif

    const GLubyte *version = glGetString(GL_VERSION);
    qDebug("%s(%s)[%d] %s", __FILE__, __func__, __LINE__, version);

    int attributeQty = 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributeQty);
    qDebug("%s(%s)[%d] Max Vertex Attributes: %d", __FILE__, __func__, __LINE__, attributeQty);

    init_program(m_program, ":/resource/shader/vshader.glsl", ":/resource/shader/fshader.glsl");

    load_model("./nanosuit/nanosuit.obj");
//    m_model = new Model(m_program, "/home/jake/workspace/SimulatorOld/resource/nanosuit/nanosuit.obj");
//    m_model = new Model("/home/jake/Downloads/untitled.obj");

}

void OpenGLWidget::resizeGL(int w, int h)
{
//    glViewport(0, 0, w, h);
    m_projection.setToIdentity();

    const qreal zNear = 0.1;
    const qreal zFar = 100.0;
    const qreal fov = 45.0;
    const qreal aspect = qreal(w) / qreal(h? h : 1);
    m_projection.perspective(fov, aspect, zNear, zFar);
}

void OpenGLWidget::paintGL()
{
    glClearColor(0.05, 0.05, 0.05, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program.bind();

    m_program.setUniformValue("projection", m_projection);
    m_program.setUniformValue("view", m_camera.lookAt());

//    m_matrixModel.setToIdentity();
    m_program.setUniformValue("model", m_matrixModel);

    if (m_model) {
        m_model->draw();
    }
}
