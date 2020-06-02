#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();

    Producer p;
    p.start();

#if 0
    QVector<Customer*> vtr;
    for(int i = 0; i < 5; ++i){
        Customer c;
        c.start();
        vtr.push_back(&c);
    }

    p.wait();
    for(auto &item:vtr){
        item->wait();
    }
#endif
#if 1
    QVector<Customer*> vtr;
    for(int i = 0; i < 5; ++i){
        Customer *c = new Customer;
        QObject::connect(c,&Customer::finished,
                         c,&Customer::deleteLater);
        vtr.push_back(c);
        c->start();
    }

    p.wait();
#if 1
    for(auto item : vtr){
        if(item != nullptr){
            item->wait();
        }
    }

    for(auto &item : vtr){
        if(item != nullptr){
            delete item;
            item = nullptr;
        }
    }
#endif

#endif

#if 0
    Customer c;
    c.start();

    Customer cc;
    cc.start();

    p.wait();
    c.wait();
    cc.wait();
#endif

    return a.exec();
}
