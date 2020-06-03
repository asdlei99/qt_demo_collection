// Filename: STL-vector.cc
#include <iostream.h>
#include <deque>
#include <vector>
using namespace std;

int main() {
    int data[5] = { 6, 8, 7, 6, 5 };
    vector<int> v(5, 6);
    vector<int>::iterator q;
    for(q = v.begin(); q != v.end(); ++q)
        cout << *q << "  ";
    cout << endl;
    deque<int> d(data, data + 5);
    deque<int>::iterator p;
    cout << "Deque values" << endl;
    for (p = d.begin(); p != d.end(); ++p)
        cout << *p << "  ";
    cout << endl;
    d.insert(d.begin(), v.begin(), v.end());
    for (p = d.begin(); p != d.end(); p++)
        cout << *p << "  ";
    cout << endl;
    d.erase(d.begin() + 3, d.begin() + 6);
    for (p = d.begin(); p != d.end(); p++)
        cout << *p << "  ";                           //display:6 6 6 8 7 6 5
    cout << endl;
}


/*out
OOP> gpp STL-vector.cc
OOP> a.out
6  6  6  6  6
Deque values
6  8  7  6  5
6  6  6  6  6  6  8  7  6  5
6  6  6  8  7  6  5
OOP>
*/