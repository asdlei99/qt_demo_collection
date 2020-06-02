#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>

class Camera
{
public:
    Camera();

    void forward();

    void backward();

    void right();

    void left();

    void up();

    void down();

    double speed() const;

    void set_speed(double speed);

    bool fps() const;

    void set_fps(bool enabled);

    void set_front(double pitch, double yaw);

    QMatrix4x4 lookAt();

private:
    double m_speed;
    bool m_fps;
    QVector3D m_position;
    QVector3D m_front;
    QVector3D m_up;
};

#endif // CAMERA_H
