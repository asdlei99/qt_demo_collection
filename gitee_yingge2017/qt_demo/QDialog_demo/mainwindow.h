#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwidget.h>
#include <qdialog.h>

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
    void on_pushButton_111_clicked();
    void on_pushButton_22_clicked();
    void on_pushButton33_clicked();
    void on_pushButton444_clicked();
private:
    Ui::MainWindow *ui;
    QDialog *d1,*d2,*d3;
};

class Widget :public QWidget{
Q_OBJECT
public:
};

#endif // MAINWINDOW_H
