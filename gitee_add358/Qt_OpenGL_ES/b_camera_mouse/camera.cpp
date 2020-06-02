#include "camera.h"
#include <qmath.h>

Camera::Camera() :
    m_speed(0.05),
    m_fps(false),
    m_position(0.0, 0.0, 3.0),
    m_front(0.0, 0.0, -1.0),
    m_up(0.0, 1.0, 0.0)
{

}

void Camera::forward()
{
    m_position += m_speed * m_front;
}

void Camera::backward()
{
    m_position -= m_speed * m_front;
}

void Camera::right()
{
    m_position += QVector3D::crossProduct(m_front, m_up).normalized() * m_speed;
}

void Camera::left()
{
    m_position -= QVector3D::crossProduct(m_front, m_up).normalized() * m_speed;
}

void Camera::up()
{
    m_position += QVector3D(0.0, m_speed, 0.0);
}

void Camera::down()
{
    m_position += QVector3D(0.0, -m_speed, 0.0);
}

double Camera::speed() const
{
    return m_speed;
}

void Camera::set_speed(double speed)
{
    m_speed = speed;
}

bool Camera::fps() const
{
    return m_fps;
}

void Camera::set_fps(bool enabled)
{
    m_fps = enabled;
}

void Camera::set_front(double pitch, double yaw)
{
    m_front = QVector3D(qCos(qDegreesToRadians(yaw)) * qCos(qDegreesToRadians(pitch)),
                        qSin(qDegreesToRadians(pitch)),
                        qSin(qDegreesToRadians(yaw)) * qCos(qDegreesToRadians(pitch))).normalized();
}

QMatrix4x4 Camera::lookAt()
{
    if (m_fps) {
        m_position.setY(0);
    }
    QMatrix4x4 matrix;
    matrix.lookAt(m_position,
                  m_position + m_front,
                  m_up);
    return matrix;
}
