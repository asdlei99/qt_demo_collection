#include <iostream>
using namespace std;

int main(int, char** ) {
    enum Signal { off, on } sig;      /* a new type, 2 new enum identifiers,
                           and a variable definition all in one line */
    sig = on;
    enum Answer { no, yes, maybe = -1 }; /* just the type/enum definitions */
    Answer ans = no;                 /* an instance of an enum */
//  enum Neg {no,false} c;           /* illegal redefinitions of identifiers */
    enum { lazy, hazy, crazy } why;  /* a typeless enum variable */
    int  i, j = on;                  /* An enum can always convert to int. */
    sig = off;  
    i = ans; 
//  ans = sig;                       /* Conversions between enum types cannot be done implicitly. */
    ans = static_cast<Answer>(sig);  /* Conversion is okay with a cast. */
    ans = (sig ? no : yes);              
    why = hazy;
    cout << "sig, ans, i, j, why "
         << sig << ans << i << j << why << endl;
    return 0;
}
/*OUT
OOP> gpp enumtest.cc
a, b, i, j, why 01011
OOP>
*/

