#ifndef INFORDIALOG_H
#define INFORDIALOG_H

#include <QDialog>

namespace Ui {
class InforDialog;
}

class InforDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InforDialog(QWidget *parent = 0);
    ~InforDialog();

private slots:
    void on_questionDia_clicked();

    void on_informationDia_clicked();

    void on_warningDia_clicked();

    void on_criticalDia_clicked();

    void on_aboutDia_clicked();

    void on_aboutQtDia_clicked();

    void on_customDia_clicked();

private:
    Ui::InforDialog *ui;
};

#endif // INFORDIALOG_H
