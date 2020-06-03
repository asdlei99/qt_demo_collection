#include <iostream>
using namespace std;

int main() {
    int m1(11), m2(13);
    const int* n1(&m1);
    int* const n2(&m2);
    // First snapshot
    cout << "n1 = " << n1 << '\t' << *n1 << '\n'
         << "n2 = " << n2 << '\t' << *n2 << endl;
    n1 = &m2;
    //*n1 = 15;  /* error: assignment of read-only location */
    m1 = 17;    /* m2 is an ordinary int variable, okay to assign */
    //n2 = &m1; /* error: assignment of read-only variable 'n2' */
    *n2 = 16;   /* okay to change target*/
    // Second snapshot
    cout << "n1 = " << n1 << '\t' << *n1 << '\n' 
         << "n2 = " << n2 << '\t' << *n2 << endl;
    return 0;
}
/*OUT
src/constptr> g++ constptr.cpp
src/constptr> ./a.out
n1 = 0xbffff504 11
n2 = 0xbffff500 13
n1 = 0xbffff500 16
n2 = 0xbffff500 16
src/constptr>
*/

