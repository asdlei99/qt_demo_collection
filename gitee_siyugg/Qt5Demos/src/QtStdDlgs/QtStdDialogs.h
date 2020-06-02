#ifndef QTSTDDIALOGS_H
#define QTSTDDIALOGS_H

#include <QDialog>

namespace Ui {
class QtStdDialogs;
}

class QtStdDialogs : public QDialog
{
    Q_OBJECT

public:
    explicit QtStdDialogs(QWidget *parent = 0);
    ~QtStdDialogs();

private slots:
    void on_fileDiaBtn_clicked();

    void on_colorDiaBtn_clicked();

    void on_fontDiaBtn_clicked();

    void on_fontDiaBtn_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::QtStdDialogs *ui;
};

#endif // QTSTDDIALOGS_H
