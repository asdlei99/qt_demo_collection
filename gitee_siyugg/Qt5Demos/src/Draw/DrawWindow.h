#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QMainWindow>
class QLabel;
class QComboBox;
class QAction;
class QSpinBox;
class DrawArea;
class QMouseEvent;

namespace Ui {
class DrawWindow;
}

class DrawWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrawWindow(QWidget *parent = 0);
    ~DrawWindow();

private:
    Ui::DrawWindow *ui;
    DrawArea *drawArea;
    QLabel *styleLabel;
    QComboBox *styleBox;
    QLabel *widthLabel;
    QSpinBox *widthBox;
    QLabel *colorLabel;
    QAction *colorAct;
    QAction *clearAct;

    QLabel *currentStyleLabel,*currentWidthLabel;

    void createTools();

public slots:
    void selectColor();
    void showCurrentStyle(QString);
    void showCurrentWidth(QString);
};

#endif // DRAWWINDOW_H
