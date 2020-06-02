#ifndef SOLORSYSTEMWIN_H
#define SOLORSYSTEMWIN_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class SolorSystemWin;
}

class SolorSystemWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit SolorSystemWin(QWidget *parent = 0);
    ~SolorSystemWin();
protected slots:
    void slot_rotate(int);
    void slot_scale(int);
    void slot_shear(int);
    void slot_translate(int);
private:
    Ui::SolorSystemWin *ui;
    QGraphicsScene *scene;
    int currentAngle{0};
    int currentScaleValue{0};
    int currentShearValue{0};
    int currentTranslateValue{0};
};

#endif // SOLORSYSTEMWIN_H
