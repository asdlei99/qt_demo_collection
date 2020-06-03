#ifndef CUSTOMERLIST_H
#define CUSTOMERLIST_H

#include <QList>
#include "customer.h"

class CustomerList : public QObject {
    Q_OBJECT  
  public:
    CustomerList(QString listname = QString()) {
        setObjectName(listname);
    }
    QList<Customer*> getCustomers();
    static CustomerList* sample();
};

#endif
