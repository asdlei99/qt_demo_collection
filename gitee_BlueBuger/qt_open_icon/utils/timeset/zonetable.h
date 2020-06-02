/**
 ** @author:	   浓咖啡
 ** @date:	   2016.6.30
 ** @brief:      时区界面需要的表格组件
 */

#ifndef ZONETABLE_H
#define ZONETABLE_H

#include "baselabel.h"

class ZoneTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit ZoneTable(const QStringList &list);

signals:

private slots:
    void currentCellChangedSlot(int currentRow, int currentColumn,\
                            int previousRow, int previousColumn);
private:

    bool first;
    const int columnCount = 4;
};

#endif // ZONETABLE_H
