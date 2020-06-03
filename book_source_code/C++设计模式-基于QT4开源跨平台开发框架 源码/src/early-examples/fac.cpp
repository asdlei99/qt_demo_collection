/* Computes and prints n! for a given n. 
   Uses several basic elements of C++. */

#include <iostream> /* standard c++ library - 
       In older versions of C++, you might find <iostream.h>
       instead, but that version is regarded as obsolete 
       or "deprecated" */

int main() { /* start of function "main" which returns int */
    using namespace std; /* permits us to use the
                            symbols cin, cout, and endl without prefixing each name with std:: */
    // Declarations of variables
    int factArg = 0 ;        /* C style initialization syntax */ 
    int fact(1) ;            /* C++ style initialization syntax */
    do { /* start of "do..while" loop. */                  
        cout << "Factorial of: "; /* Write to standard output */
        cin >> factArg;      /* read from standard input and convert to int */
        if ( factArg < 0 ) {
            cout << "No negative values, please!" << endl;
        } /* end of if block */
    } while (factArg < 0) ; /* if false, break out of do loop */
    int i = 2;
    while ( i <= factArg ) {  /* start of while loop  */ 
        fact = fact * i; 
        i = i + 1;
    } /* end of while block */
    cout << "The Factorial of " << factArg << " is: " << fact << endl;
    return 0; /* when main returns 0, that normally means "no errors"  */
} /* end of main block */
