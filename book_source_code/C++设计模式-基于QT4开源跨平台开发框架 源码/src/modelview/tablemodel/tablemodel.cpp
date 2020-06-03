#include "dataobjecttablemodel.h"
#include "customerfactory.h"
#include "country.h"

DataObjectTableModel* model() {
    CustomerFactory* fac = CustomerFactory::instance();
    Customer* cust1 = fac->newCustomer("luke skywalker", Country::USA);
    DataObjectTableModel* retval = new
    DataObjectTableModel(cust1); /* header model */ 
    cust1->setId("14123");
    *retval << cust1;   /* Insert row into table. */
    *retval << fac->newCustomer("Ben Kenobi", Country::Canada);
    *retval << fac->newCustomer("Princess Leia", Country::USA);    
    return retval;
}

#include <QTableView>
#include <QApplication>
#include <QMainWindow>
#include <QDebug>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    DataObjectTableModel *mod = model();
    QMainWindow mainwin;
    QTableView view ;
    view.setModel(mod);
    mainwin.setCentralWidget(&view);
    mainwin.setVisible(true);
    int retval =  app.exec();
    qDebug() << "Application Exited. " << endl;
    qDebug() << mod->toString() << endl;
    delete mod;
    return retval;
}

