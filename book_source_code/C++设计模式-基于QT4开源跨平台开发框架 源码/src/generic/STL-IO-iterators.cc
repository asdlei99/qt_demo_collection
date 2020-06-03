// Filename: STL-IO-iterators.cc
// Use of istream_iterator and ostream_iterator.
#include <iterator>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cout << "enter 5 numbers" << endl;
    vector<int> d(5);
    int  i, sum ;
    istream_iterator<int> in(cin);
    ostream_iterator<int> out(cout, "\t");

    sum = d[0] = *in;                               //input first value
    for(i = 1; i < 5; ++i) {
        d[i] = *++in;                                 //input consecutive values
        sum += d[i];
    }
    for(i = 0; i < 5; ++i)
        *out = d[i] ;                                 //output consecutive values
    cout << "\nsum = " << sum << endl;
}


/*out
OOP> gpp STL-IO-iterators.cc
OOP> a.out
enter 5 numbers
1 3 5 7 9
1       3       5       7       9
sum = 25
OOP>
*/