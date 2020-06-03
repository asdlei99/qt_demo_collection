// Filename: STL-sort.cc
// Using sort() from STL
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 5;
int main() {
    int    d[N], i, *e = d + N;
    for (i = 0; i < N; ++i)
        d[i] = rand();
    sort(d, e);
    for (i = 0; i < N; ++i)
        cout << d[i] << "  ";
    cout << endl;
}


/*out
OOP> gpp STL-sort.cc
OOP> a.out
846930886  1681692777  1714636915  1804289383
1957747793
OOP>
*/