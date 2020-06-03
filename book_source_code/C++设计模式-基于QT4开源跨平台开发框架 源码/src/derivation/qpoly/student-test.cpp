#include <QTextStream> 
#include "student.h"

static QTextStream cout(stdout, QIODevice::WriteOnly); 

void graduate(Student* student) {
    cout << "\nThe following "
         << student->getClassName()
         << " has graduated\n "
         << student->toString() << "\n";
}

int main() {
    Undergrad us("Frodo", 5562, "Ring Theory", 4);
    GradStudent gs("Bilbo", 3029, "History", 6, GradStudent::fellowship);
    cout << "Here is the data for the two students:\n";
    cout << gs.toString() << endl;
    cout << us.toString() << endl;
    cout << "\nHere is what happens when they graduate:\n";
    graduate(&us);
    graduate(&gs);
    return 0;
}
