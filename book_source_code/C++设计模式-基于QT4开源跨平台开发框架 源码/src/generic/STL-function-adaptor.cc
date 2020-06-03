// Filename: STL-function-adaptor.cc
// Use of the function adaptor bind2nd
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;
template <class Iter>
void display(Iter fst, Iter lst, const char* ttl) {
    cout << ttl << endl;
    while ( fst != lst)
        cout << *fst++ << '\t';
    cout << endl;
}


int main() {
    int data[3] = { 9, 10, 11};
    display(data, data + 3, "Original values");
    transform(data, data + 3, data,
              bind2nd(multiplies<int>(), 2));
    display(data, data + 3, "New values");
}


/*out
OOP> gpp STL-function-adaptor.cc
OOP> a.out
Original values
9       10      11
New values
18      20      22
OOP>
*/