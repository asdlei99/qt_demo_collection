#ifndef DBWGT_H
#define DBWGT_H

#include <QWidget>

namespace Ui {
class DbWgt;
}

class DbWgt : public QWidget
{
    Q_OBJECT

public:
    explicit DbWgt(QWidget *parent = 0);
    ~DbWgt();

private slots:

    void on_addBtn_clicked();

    void on_modifyBtn_clicked();

    void flashAllUser();

    void deleteOneUser();

private:
    Ui::DbWgt *ui;
};

#endif // DBWGT_H
