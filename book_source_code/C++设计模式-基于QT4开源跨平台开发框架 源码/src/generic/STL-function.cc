// Filename: STL-function.cc
// Using the function object minus<int>

#include <iostream>
#include <numeric>
using namespace std;
int main() {
    double v1[3] = {1.0, 2.5, 4.6},
                   sum;
    sum = accumulate(v1, v1 + 3, 0.0, minus<int>());
    cout << "sum = " << sum << endl;                //sum = -7
}


/*out
OOP> g++ stl_function.cc
// warnings about feeding double to minus<int>
OOP> a.out
sum = -7
OOP>
*/