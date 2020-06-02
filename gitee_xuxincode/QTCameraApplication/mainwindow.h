#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void handleButton();
    //void quit();

private:
    QPushButton *m_button;
    QPushButton *q_button;
    //Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
