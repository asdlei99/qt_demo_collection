#include <QTextStream> 
#include "person.h"

static QTextStream cout(stdout, QIODevice::WriteOnly); 

int main(int , char**) {
    cout << "First we create a bunch of objects." << endl;
    QObject bunch; 
    bunch.setObjectName("A Stack Object"); /* not a pointer */ 
    /* other objects are created on the heap */        
    Person *mike = new Person(&bunch, "Mike"); 
    Person *carol = new Person(&bunch, "Carol");
    new Person(mike, "Greg"); /* We do not need 
             to keep pointers to children, since we can
             reach them via object navigation. */
    new Person(mike, "Peter");
    new Person(mike, "Bobby");
    new Person(carol, "Marcia");
    new Person(carol, "Jan");
    new Person(carol, "Cindy");
    new Person(0, "Alice");  /* Alice has no parent - memory leak? */
    cout << "\nDisplay the list using QObject::dumpObjectTree()" 
             << endl; 
    bunch.dumpObjectTree();
    cout << "\nProgram finished - destroy all objects." << endl;
    return 0;
}

