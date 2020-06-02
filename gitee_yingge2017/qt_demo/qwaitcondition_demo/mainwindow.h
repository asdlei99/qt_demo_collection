#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qthread.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

class Producer:public QThread{
        Q_OBJECT
public:
    Producer(){}
protected:
    void run()override;
};

class Customer:public QThread{
    Q_OBJECT
public:
    Customer(){}
protected:
    void run()override;
};

#endif // MAINWINDOW_H
