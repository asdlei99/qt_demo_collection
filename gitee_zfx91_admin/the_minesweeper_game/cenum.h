#ifndef CENUM_H
#define CENUM_H

#include <QObject>

class CEnum : public QObject
{
    Q_OBJECT
public:

    enum CItemType{
        MSMine = -1,         //雷
        MSZore = 0,
        MSOne,          //1
        MSTwo,          //2
        MSThree,          //3
        MSFour,          //4
        MSFive,          //5
        MSSix,          //6
        MSSeven,          //7
        MSEight,          //8
    };

    explicit CEnum(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CENUM_H
