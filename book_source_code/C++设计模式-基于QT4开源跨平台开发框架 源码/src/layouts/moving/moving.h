#ifndef MOVING_H
#define MOVING_H
#include <QMainWindow>
#include <QApplication>
#include <QStack>
#include <QQueue>

class QLabel;
class QVBoxLayout;
//start
/**
   A demo of how widgets can move from one layout to another,
   and also of how layouts can cause the containing widgets to stretch
   to accomodate new elements.
   */

class MovingApp : public QApplication {
    Q_OBJECT
public:
    MovingApp(int argc, char* argv[]);

public slots:
    void moveLeft();
    void moveRight();
    void newLeft();
    void newRight();
private:
    QString nextLabel();
    QMainWindow m_MainWindow;
    QQueue<QLabel*> m_LeftQueue, m_RightQueue;
    QVBoxLayout *m_LeftLayout, *m_RightLayout;
    int m_Count;
};
//end
#endif 

