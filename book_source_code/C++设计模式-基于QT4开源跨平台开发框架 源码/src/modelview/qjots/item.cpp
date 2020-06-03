#include "item.h"
//start
Item::Item() {
    setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable
            | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled
            | Qt::ItemIsEnabled );
}
//end
void Item::setName(QString name) {
    setText(0, name);
}

QString Item::name() const {
    return text(0);    
}

