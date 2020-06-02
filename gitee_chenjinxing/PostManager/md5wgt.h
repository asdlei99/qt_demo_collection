#ifndef MD5WGT_H
#define MD5WGT_H

#include <QWidget>

namespace Ui {
class Md5Wgt;
}

class Md5Wgt : public QWidget
{
    Q_OBJECT

public:
    explicit Md5Wgt(QWidget *parent = 0);
    ~Md5Wgt();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Md5Wgt *ui;
};

#endif // MD5WGT_H
