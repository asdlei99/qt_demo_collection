#ifndef FRACTION_H
#define FRACTION_H
//start
class Fraction {
 public:
    Fraction(int n, int d) : m_Numer(n), m_Denom(d) {
        ++ctors;
    }

    Fraction(const Fraction& other)
     :  m_Numer(other.m_Numer), m_Denom(other.m_Denom) {
        ++copies;
    }

    Fraction& operator=(const Fraction& other) {
        m_Numer = other.m_Numer;
        m_Denom = other.m_Denom;
        ++assigns;
        return *this;
    }
  
    Fraction multiply(Fraction f2) ;

    static void report();

 private:
    int m_Numer, m_Denom;
    
    static int assigns;
    static int copies;
    static int ctors;
};
//end
#endif   
