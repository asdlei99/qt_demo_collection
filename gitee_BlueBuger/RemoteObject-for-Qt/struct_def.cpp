#include <struct_def.h>

QDataStream& operator<<(QDataStream&out,const test_struct&d)
{
    out << d.type << d.body << d.array[0] << d.array[1] << d.barr[0] << d.barr[1];
    return out;
}

QDataStream& operator>>(QDataStream&in,test_struct&d)
{    
    in >> d.type >> d.body >> d.array[0] >> d.array[1] >> d.barr[0] >> d.barr[1];
    return in;
}


QString test_struct::debugStr()
{
    QString debugstr("%1 %2 %3 %4 %5 %6");
    return debugstr = debugstr.arg(type).arg(body).arg(array[0]).arg(array[1]).arg(barr[0]).arg(barr[1]);
}
