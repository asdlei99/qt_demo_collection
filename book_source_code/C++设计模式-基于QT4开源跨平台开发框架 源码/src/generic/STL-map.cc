//  STL-map.cc
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    map<string, int> nameAge;
    nameAge["Duck,Donald"] = 7;
    nameAge["Mouse,Mickey"] = 39;
    nameAge["Duck,Daisy"] = 14;
    cout << "Donald is  "
    << nameAge["Duck,Donald"]
    << " years old." << endl;
}


/*out
OOP> gpp STL-map.cc
OOP> a.out
Donald is  7 years old.
OOP>
*/