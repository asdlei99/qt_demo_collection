#include "person.h"
#include <QTextStream>
static QTextStream cout(stdout, QIODevice::WriteOnly); 

Person::Person(QObject* parent, QString name) 
         : QObject(parent) {
    setObjectName(name);
    cout << QString("Constructing Person: %1").arg(name) << endl;
}

Person::~Person() {
    cout << QString("Destroying Person: %1").arg(objectName()) << endl;
}

