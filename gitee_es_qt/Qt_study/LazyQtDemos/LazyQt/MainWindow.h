#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <LzRadioButtonView.h>

class DialogStar;
class DialogCheck;

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
    // 第一行
    void on_btnReadExcel_clicked();
    void on_btnShowRadioView_clicked();
    void on_pushButtonModelView_clicked();

    // 第二行
    void on_pushButtonMySelection_clicked();
    void on_pushButtonStar_clicked();
    void on_pushButtonCheck_clicked();
    void on_pushButtonSleep_clicked();


private:
    Ui::MainWindow *ui;

    LzRadioButtonView *radioButtonView;

    DialogStar *dialogStar;
    DialogCheck *dialogCheck;
};


#endif // MAINWINDOW_H
