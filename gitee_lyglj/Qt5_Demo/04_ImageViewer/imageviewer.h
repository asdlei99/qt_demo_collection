#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>


#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = 0);
    ~ImageViewer();

private slots:
    void on_action_exit_triggered();

    void on_action_Open_triggered();

    void on_action_ZoomIn_triggered();

    void on_action_ZoomOut_triggered();

    void on_action_NormalSize_triggered();

    void on_action_fitToWindow_triggered();

    void on_action_Print_triggered();

    void on_action_About_triggered();

    void on_action_AboutQt_triggered();

private:
    Ui::ImageViewer *ui;

    QLabel *imageLabel;
    QScrollArea *scrollArea;


    double scaleFactor;

    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif
};

#endif // IMAGEVIEWER_H
