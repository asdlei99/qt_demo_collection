#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
using namespace std;

class Rational {
public:
    Rational(int n = 0) : m_A(n), m_Q(1) {}
    Rational(int i, int j) : m_A(i), m_Q(j?j:1) {}
    Rational(double r) :
    m_A(static_cast<long>(r * BIG)), m_Q(BIG) {}

    void  display() const;
    operator double() const {
        return static_cast<double>(m_A)/m_Q;
    }
    friend ostream& operator<<(ostream& out,
                               Rational x);
    friend istream& operator>>(istream& in,
                               Rational& x);
    bool operator> (const Rational& other) const;                           
private:
    long  m_A, m_Q;
    enum {BIG = 1000};
};

#endif        //  #ifndef RATIONAL_H

