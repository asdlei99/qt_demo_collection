/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.30
 ** @brief:      时区界面
 */

#ifndef ZONESET_H
#define ZONESET_H

#include "headutils.h"
#include "zonetable.h"

class ZoneSet : public QWidget
{
    Q_OBJECT
public:
    explicit ZoneSet(QWidget *parent = 0);

signals:
    void backDisp();

private:
    void createZoneList();
    HeadUtils *head;
    ZoneTable *table;
    QStringList zonelist;
};
#endif // ZONESET_H
