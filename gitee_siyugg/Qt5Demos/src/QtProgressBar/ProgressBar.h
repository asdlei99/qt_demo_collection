#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QDialog>

namespace Ui {
class ProgressBar;
}

class ProgressBar : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressBar(QWidget *parent = 0);
    ~ProgressBar();

private slots:
    void on_startButton_clicked();

private:
    Ui::ProgressBar *ui;
};

#endif // PROGRESSBAR_H
