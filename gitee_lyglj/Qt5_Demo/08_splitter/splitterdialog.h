#ifndef SPLITTERDIALOG_H
#define SPLITTERDIALOG_H

#include <QDialog>

namespace Ui {
class splitterDialog;
}

class splitterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit splitterDialog(QWidget *parent = 0);
    ~splitterDialog();

private:
    Ui::splitterDialog *ui;
};

#endif // SPLITTERDIALOG_H
