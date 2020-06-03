// Filename: rational.cc
// Overloading functions

#include "rational.h"

ostream& operator<<(ostream& out, Rational  x) {
    return (out << x.m_A << " / " << x.m_Q << '\t');
}


istream& operator>>(istream& in, Rational& x)
// Unprotected Input!!!
{
    return (in >> x.m_A >> x.m_Q);
}

void Rational::display() const {
        cout << m_A << " / " << m_Q;
}

bool Rational::operator>(const Rational& other) const {
    return ( (double)*this  >  (double) other );
}

Rational max(Rational r1, Rational r2) {
    return (r1 > r2 ? r1: r2);   
}

int main() {
    int     i = 10, j = 5;
    float   x = 7.0;
    double  y = 14.5;
    Rational v(5,0), w(10), z(3.5), zmax;
    cout << v << "\tzero denominator?"
    << "\nmax(" << i << ", " << j << ") = "
    << max(i, j)
    << "\nmax(" << x << ", " << y << ") = "
    << max(x, y)
    << "\nmax(" << i << ", " << z << ") = "
    << max(static_cast<Rational>(i), z);
    zmax = max(w, z);
    cout << "\ngreater(" << w << ", " << z << ") = "
    <<  zmax
    << "\nEnter two longs for Rational: ";
    cin >> w;
    cout << "Rational value: "<< w
    << "   double value: "<< y
    << "\nsum = " << w + y << "\tproduct = "
    << w * y  << endl;
}


/*
OOP> gpp rational.cc
OOP> ./a.out
5 / 1           zero denominator?
greater(10, 5) = 10
greater(7, 14.5) = 14.5
greater(10, 3500 / 1000 ) = 10 / 1
greater(10 / 1  , 3500 / 1000   ) = 10 / 1
Enter two longs for Rational: 432
123
Rational value: 432 / 123   double value: 14.5
sum = 18.0122   product = 50.9268
OOP>
*/

