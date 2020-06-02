#ifndef MODELVIEWDIALOG_H
#define MODELVIEWDIALOG_H

#include <QDialog>

namespace Ui {
class ModelViewDialog;
}

class ModelViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModelViewDialog(QWidget *parent = 0);
    ~ModelViewDialog();

private:
    void createListView();
    void createStringListView();

    Ui::ModelViewDialog *ui;

};

#endif // MODELVIEWDIALOG_H
