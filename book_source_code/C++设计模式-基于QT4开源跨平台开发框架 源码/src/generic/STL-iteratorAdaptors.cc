// Filename: STL-iteratorAdaptors.cc
#include <iostream>
#include <vector>
using namespace std;
template <class Iter>
void display(Iter fst, Iter lst, const char* ttl) {
    cout << ttl << endl;
    while ( fst != lst)
        cout << *fst++ << '\t';
    cout << endl;
}


int main() {
    int  data[3] = { 9, 10, 11};
    vector<int> d(data, data + 3);
    vector<int>::reverse_iterator p = d.rbegin();
    display(d.begin(), d.end(), "Original");
    display(p, d.rend(), "Reverse");
}


/*out
OOP> gpp STL-iteratorAdaptors.cc
OOP> a.out
Original
9       10      11
Reverse
11      10      9
OOP>
*/