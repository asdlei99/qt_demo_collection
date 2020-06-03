
#include "vect1.h"

int main() {
    Vect a(60), b[20];

    b[1][5] = 7;
    cout << " 1 element 5 = "<< b[1][5] << endl;
    for (int i = 0; i <= a.ub(); ++i)
        a[i] = 2 * i + 1;
    for (int i = a.ub(); i >= 0; --i)
        cout << ((a[i] < 100) ? " " : "" )
        << ((a[i] < 10) ? " " : "" )
        << a[i]
        << ((i % 10) ? "  " : "\n");
    cout << endl;
    cout << "Now try to access an out-of-range index"
    << endl;
    cout << a[62] << endl;
}


/*OUT
OOP> g++ vect1test.cc 
OOP> a.out
1 element 5 = 7
119  117  115  113  111  109  107  105  103  101
99   97   95   93   91   89   87   85   83   81
79   77   75   73   71   69   67   65   63   61
59   57   55   53   51   49   47   45   43   41
39   37   35   33   31   29   27   25   23   21
19   17   15   13   11    9    7    5    3    1
Now try to access an out-of-range index
a.out: vect1.h:12: int &Vect::operator[] (int):
Assertion `i >= 0 && i < m_Size' failed.
Aborted
OOP>
*/
