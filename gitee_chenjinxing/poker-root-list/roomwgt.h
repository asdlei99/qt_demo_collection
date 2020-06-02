#ifndef ROOMWGT_H
#define ROOMWGT_H

#include <QWidget>

namespace Ui {
class RoomWgt;
}

class RoomWgt : public QWidget
{
    Q_OBJECT

public:
    explicit RoomWgt(QWidget *parent = 0);
    ~RoomWgt();

private:
    Ui::RoomWgt *ui;

public:
    void initRoom(const QString &user1,const QString &user2,const QString &user3,bool isBeginGame=false);

protected:
    void paintEvent(QPaintEvent *);
};

#endif // ROOMWGT_H
