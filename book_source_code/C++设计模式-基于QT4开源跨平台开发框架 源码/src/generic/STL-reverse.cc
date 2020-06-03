// Filename: STL-reverse.cc
// Use of mutating reverse() and copy()
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main() {
    string firstname[5] = {
                              "donald", "daisy",
                              "mickey", "minnie", "twinkle"
                          };
    string lastname[5] = {
                             "duck", "duck",
                             "mouse", "mouse", "star"
                         };
    vector<string> name(firstname, firstname + 5);
    vector<string> name2(10);
    vector<string>::iterator p;
    copy(lastname, lastname + 5, name2.begin());
    copy(name.begin(), name.end(), name2.begin() + 5);
    reverse(name2.begin(), name2.end());
    for (p = name2.begin(); p != name2.end(); ++p)
        cout << *p <<"  ";
    cout << endl;
}


/*out
OOP> gpp STL-reverse.cc
OOP> a.out
twinkle  minnie  mickey  daisy  donald  star  mouse
mouse  duck  duck
OOP>
*/