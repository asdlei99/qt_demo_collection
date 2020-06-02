#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLineEdit;
class OpenGLWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void do_toolButton_clicked();

    void do_insideSpinBox_changed(double v);

    void do_outsideSpinBox_changed(double v);

    void do_lengthSpinBox_changed(double v);

    void do_widthSpibBox_changed(double v);

    void do_heightSpibBox_changed(double v);

private:
    QLineEdit *m_textureLineEdit;
    OpenGLWidget *m_openglWidget;
};

#endif // MAINWINDOW_H
