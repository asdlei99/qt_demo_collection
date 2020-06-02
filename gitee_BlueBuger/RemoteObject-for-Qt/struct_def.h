#ifndef STRUCT_DEF_H
#define STRUCT_DEF_H

#include <QtCore>
#include <QDataStream>
#include <iostream>

struct test_struct
{
    int type;
    QString body;
    int array[2];
    bool barr[2];

    test_struct(){
        std::fill(array,array+1,0);
    }
    friend QDataStream &operator<<(QDataStream &,const test_struct&);
    friend QDataStream &operator>>(QDataStream &,test_struct&);

    QString debugStr();
};
Q_DECLARE_METATYPE(test_struct)


#endif // STRUCT_DEF_H
