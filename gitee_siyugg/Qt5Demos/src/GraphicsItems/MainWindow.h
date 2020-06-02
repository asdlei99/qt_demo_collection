#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MyGraphicsItem.h"
#include <QMainWindow>

class QGraphicsScene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //QString imgFileName;
    MyGraphicsItem *myItem;
    QGraphicsScene *scene;

    int currentAngle;
    int currentScaleValue;
    int currentShearValue;
    int currentTranslateValue;
protected slots:
    void slot_openImg();
    void slot_quit();
    void slot_rotate(int);
    void slot_scale(int);
    void slot_shear(int);
    void slot_translate(int);
};

#endif // MAINWINDOW_H
