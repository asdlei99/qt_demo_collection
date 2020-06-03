#include "fraction.h"
#include <iostream>

/* static member definitions */
int Fraction::assigns = 0;
int Fraction::copies = 0;
int Fraction::ctors = 0;

Fraction Fraction::multiply(Fraction f2) {
    return Fraction (m_Numer*f2.m_Numer, m_Denom*f2.m_Denom);
}
 
void Fraction::report() {
    using namespace std;
    cout << "\n [ assigns: " << assigns 
         << " copies: " << copies
         << " ctors: " << ctors << " ] " << endl;
}
