#include "shoppinglist.h"

QString ShoppingList::sm_Check("[ ] ");

QStringList& ShoppingList::operator<<(const QString& newitem) {
    append(sm_Check + newitem);
    return *this;
}

QString ShoppingList::makePrintList() {
    sort();
    prepend("****** Shopping List *******");
    return join("\n");
}
