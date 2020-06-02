#ifndef ROOMLISTWGT_H
#define ROOMLISTWGT_H

#include <QWidget>

namespace Ui {
class RoomListWgt;
}

class RoomListWgt : public QWidget
{
    Q_OBJECT

public:
    explicit RoomListWgt(QWidget *parent = 0);
    ~RoomListWgt();

private slots:
    void on_addRoom_clicked();

private:
    Ui::RoomListWgt *ui;

};

#endif // ROOMLISTWGT_H
