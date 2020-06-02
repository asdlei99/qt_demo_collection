#include "opengl_widget.h"
#include "cube_engine.h"
#include "circle_engine.h"
#include "cylinder_engine.h"

#include <QTimer>
#include <QDateTime>
#include <QOpenGLTexture>
#include <QKeyEvent>

OpenGLWidget::OpenGLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    m_cube(NULL),
    m_circle(NULL),
    m_cylinder(NULL),
    m_texture1(NULL),
    m_texture2(NULL),
    m_moveForward(false),
    m_moveBackward(false),
    m_moveRight(false),
    m_moveLeft(false),
    m_mousePressed(false),
    m_yaw(-90),
    m_pitch(0.0),
    m_fov(45)
{
    setFocusPolicy(Qt::WheelFocus);

//    m_camera.set_fps(true);

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
    if (m_circle) {
        delete m_circle;
    }
    if (m_cylinder) {
        delete m_cylinder;
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

    glEnable(GL_DEPTH_TEST);    //启用深度测试。
    glEnable(GL_BLEND);         // 启用颜色混合。用于实现半透明效果
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //指定混合函数
//    glEnable(GL_CULL_FACE);   // 启用多边形背面消除特性

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

//    m_cube = new CubeEngine(m_program);

//    m_circle = new CircleEngine(m_program);

    m_cylinder = new CylinderEngine(m_program);

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

    update_camera();
    m_program.setUniformValue("view", m_camera.lookAt());

    QMatrix4x4 projection;
    projection.perspective(m_fov, 1.0*size().width()/size().height(), 0.1, 100.0);
    m_program.setUniformValue("projection", projection);

    m_texture1->bind(0);
    m_texture2->bind(1);

    if (m_cube) {
        m_cube->draw();
    }

    if (m_circle) {
        m_circle->draw();
    }

    if (m_cylinder) {
        m_cylinder->draw();
    }
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
    case Qt::Key_Up:
        m_moveForward = true;
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        m_moveBackward = true;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        m_moveLeft = true;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        m_moveRight = true;
        break;
    case Qt::Key_Space:
        m_camera.up();
        break;
    case Qt::Key_Z:
        m_camera.down();
    default:
        return;
        break;
    }

    update();
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
    case Qt::Key_Up:
        m_moveForward = false;
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        m_moveBackward = false;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        m_moveLeft = false;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        m_moveRight = false;
        break;
    default:
        return;
        break;
    }
}

void OpenGLWidget::mousePressEvent(QMouseEvent *e)
{
    m_mousePressed = true;
    m_lastMousePos = e->pos();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    m_mousePressed = false;
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (!m_mousePressed) {
        return;
    }

    float xoffset = m_lastMousePos.x() - e->pos().x();
    float yoffset = e->pos().y() - m_lastMousePos.y();
    m_lastMousePos = e->pos();

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    m_yaw   += xoffset;
    m_pitch += yoffset;

    if(m_pitch > 89.0f)
        m_pitch = 89.0f;
    if(m_pitch < -89.0f)
        m_pitch = -89.0f;

    m_camera.set_front(m_pitch, m_yaw);
}

void OpenGLWidget::wheelEvent(QWheelEvent *e)
{
    if (e->delta() < 0) {
        m_fov += 1;
    } else {
        m_fov -= 1;
    }

    if (m_fov < 1.0) {
        m_fov = 1.0;
    } else if (m_fov > 89){
        m_fov = 89;
    }
}

void OpenGLWidget::update_camera()
{
    if (m_moveBackward) {
        m_camera.backward();
    }
    if (m_moveForward) {
        m_camera.forward();
    }
    if (m_moveLeft) {
        m_camera.left();
    }
    if (m_moveRight) {
        m_camera.right();
    }
}
