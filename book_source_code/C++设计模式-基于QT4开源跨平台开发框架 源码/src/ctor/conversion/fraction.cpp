class Fraction {
public:
    Fraction(int n, int d = 1)   /* default argument */ 
        : m_Numerator(n), m_Denominator(d) {}
private:
    int m_Numerator, m_Denominator;
};
int main() {
    int i;
    Fraction frac(8);     /* conversion constructor call */
    Fraction frac2 = 5;   /* copy init (calls conversion ctor too) */
    frac = 9;             /* conversion followed by assignment */
    frac = (Fraction) 7;  /* C-style typecast (deprecated) */
    frac = Fraction(6);   /* explicit temporary, also a C++ typecast */
    frac = static_cast<Fraction>(6); /* preferred ANSI style typecast */
    return 0;
}
