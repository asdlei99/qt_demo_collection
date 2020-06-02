#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>

enum E_LANGUAGE_TYPE{
    E_CN,
    E_EN
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_translateButton_clicked();

private:
    Ui::MainWindow *ui;
    QTranslator m_translator;
    E_LANGUAGE_TYPE m_languageType;
};

#endif // MAINWINDOW_H
