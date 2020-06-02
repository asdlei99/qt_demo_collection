#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initTable();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    double zhengtui(double benjin,double nianlilv);
    double debxToTable(double benjin, double nianLilv);
    double debjToTable(double benjin, double nianLilv);
    double dbdxToTable(double benjin, double nianLilv);

    void customContextMenuRequested(const QPoint &pos);
    void saveListData(bool a);
    void clearListData(bool a);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
