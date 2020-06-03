#include <iostream>
using namespace std;

int main (int argCount, char* argValue[]) {
    for (int i=0; i<argCount; ++i) {
        cout << "argv# " << i << " is " << argValue[i] << endl;
    }
    return 0; 
}

