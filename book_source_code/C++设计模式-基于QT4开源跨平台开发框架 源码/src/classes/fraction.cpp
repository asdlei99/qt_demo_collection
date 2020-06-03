#include "fraction.h"
#include <sstream>

void Fraction::set(int nn, int nd) {
    m_Numerator = nn;
    m_Denominator = nd;
}

double Fraction::toDouble() const {
    return 1.0 * m_Numerator / m_Denominator;
}

string Fraction::toString() const {
    ostringstream sstr;  /* a stream we write to, but that  
        does not get output anywhere */
    sstr << m_Numerator << "/" << m_Denominator; 
    return sstr.str();  /* convert the stream just written to a string */
}

