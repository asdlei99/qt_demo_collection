#ifndef _FRACTION_H_ 
#define _FRACTION_H_  

#include <string>
using namespace std;

class Fraction {
public:
    void set(int numerator, int denominator);
    double toDouble() const;
    string toString() const;
private:
    int m_Numerator;
    int m_Denominator;
};

#endif

