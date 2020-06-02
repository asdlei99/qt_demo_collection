#include "mygl2dwidget.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions_3_2_Compatibility>

MyGL2DWidget::MyGL2DWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
//    format.setVersion(3, 2);
//    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format); // must be called before the widget or its parent window gets shown
}

void MyGL2DWidget::initializeGL()
{
    f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_2_Compatibility>();
    f->initializeOpenGLFunctions();
    // 黑色背景
    f->glClearColor( 0.0, 0.0, 0.0, 0.0 );
}

void MyGL2DWidget::resizeGL(int w, int h)
{
    f->glViewport(0, 0, w, h);
    // 选择投影矩阵
    f->glMatrixMode( GL_PROJECTION );
    // 重置投影矩阵
    f->glLoadIdentity();
    // 设置视口的大小
//    f->( 45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0 );
    // 选择模型观察矩阵
    f->glMatrixMode( GL_MODELVIEW );
    f->glLoadIdentity();
}

void MyGL2DWidget::paintGL()
{
    // 清除屏幕和深度缓存
    f->glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    f->glLoadIdentity();

    //坐标转移
    f->glTranslatef(-1.5f,0.0f,-6.0f);

    //设置颜色
    f->glColor3f( 1.0, 1.0, 0.0 );
    //绘制一个正方形
    f->glBegin( GL_QUADS );
    f->glVertex3f( -1.0,  1.0,  0.0 );
    f->glVertex3f(  1.0,  1.0,  0.0 );
    f->glVertex3f(  1.0, -1.0,  0.0 );
    f->glVertex3f( -1.0, -1.0,  0.0 );
    f->glEnd();
}
