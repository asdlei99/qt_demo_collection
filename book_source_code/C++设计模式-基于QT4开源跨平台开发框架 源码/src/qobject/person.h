#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QString>
//start

class Person : public QObject {
   
 public:
    Person(QObject* parent, QString name);
    virtual ~Person();
};
//end

#endif 
