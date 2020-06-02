#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = 0);
    ~InputDialog();

private slots:
    void on_nameModBtn_clicked();

    void on_sexModBtn_clicked();

    void on_mathModBtn_clicked();

    void on_literalModBtn_clicked();

private:
    Ui::InputDialog *ui;
};

#endif // INPUTDIALOG_H
