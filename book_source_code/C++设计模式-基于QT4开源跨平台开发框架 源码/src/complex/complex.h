
#include <iostream>
using namespace std;

/** A pair of double, <re, im> 
    where re is the "real" coordinate
    and im is the "imaginary" coordinate.
    Mathematically, we think of this pair as 
    representing the expression  re + im*sqrt(-1) */

class Complex {
    // binary non-member friend function declarations
    friend ostream& operator<<(ostream& out, const Complex& c);
    friend Complex operator-(const Complex& c1, const Complex & c2);
    friend Complex operator*(const Complex& c1, const Complex & c2);
    friend Complex operator/(const Complex& c1, const Complex & c2);
    
    public:
    Complex(double re = 0.0, double im = 0.0);
    
    // binary member function operators
    Complex& operator+= (const Complex& c);
    Complex& operator-= (const Complex& c);

    
    Complex operator+(const Complex & c2); /* This hould be a 
        non-member friend like the other non-mutating
        operators. */
    
private:
    double m_Re, m_Im;
};

