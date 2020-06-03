#include <iostream>
#include "fraction.h"

int main() {
    using namespace std;
    Fraction twothirds(2,3); /* using 2-arg constructor */
    Fraction threequarters(3,4); 
    Fraction acopy(twothirds);   /* using copy constructor */
    Fraction f4 = threequarters; /* also using copy constructor */
    cout << "after declarations" ;
    Fraction::report();
    f4 = twothirds;              /* assignment */
    cout << "before    multiply" ;
    Fraction::report();
    f4 = twothirds.multiply(threequarters); /* Lots of
       objects get created here. */
    cout << "after     multiply" ;
    Fraction::report();
    return 0;
}
