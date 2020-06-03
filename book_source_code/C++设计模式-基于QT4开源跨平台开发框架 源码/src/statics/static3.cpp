#include "static3.h"
#include <iostream>

int Client::sm_SavedID(1000);

int main() {
    Client cust1("George");
    cout << cust1.getID() << endl;
    cout << Client::getName() << endl;
}

