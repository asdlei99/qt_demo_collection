#ifndef RUNNINGHORSELAMPFORM_H
#define RUNNINGHORSELAMPFORM_H

#include <QWidget>

namespace Ui {
class RunningHorseLampForm;
}

class RunningHorseLampForm : public QWidget
{
    Q_OBJECT

public:
    explicit RunningHorseLampForm(QWidget *parent = nullptr);
    ~RunningHorseLampForm();

private:
    Ui::RunningHorseLampForm *ui;
};

#endif // RUNNINGHORSELAMPFORM_H
