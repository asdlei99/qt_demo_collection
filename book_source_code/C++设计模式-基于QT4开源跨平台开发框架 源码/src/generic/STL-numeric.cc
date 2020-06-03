// Filename: STL-numeric.cc
#include <iostream>
#include <numeric>
using namespace std;

int main() {
    double v1[3] = {1.0, 2.5, 4.6},
                   v2[3] = {1.0, 2.0, -3.5};
    double sum, inner_p;
    sum = accumulate(v1, v1 + 3, 0.0);
    inner_p = inner_product(v1, v1 + 3, v2, 0.0);
    cout << "sum = " << sum
    << ",product = " << inner_p << endl;
}


/*out
OOP> g++ STL-numeric.cc
OOP> a.out
sum = 8.1,product = -10.1
OOP>
*/