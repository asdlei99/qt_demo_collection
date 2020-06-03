#include <iostream>
using namespace std;
//start
int main() {
    int myint = 5;
    int *ptr1 = &myint;
    cout << "*ptr1 = " << *ptr1 << endl;
    int anotherint = 6;
//  *ptr1 = &anotherint; /* error, invalid conversion from int* to int  */
    
    int *ptr2; /* uninitialized pointer */
    cout << "*ptr2 = " << *ptr2 << endl;
    *ptr2 = anotherint; /* unpredictable results */

    int yetanotherint = 7;
    int *ptr3;
    ptr3 = &yetanotherint; /* regular assignment */
    cout << "*ptr3 = " << *ptr3 << endl;
    *ptr1 = *ptr2;  /* dangerous assignment! */
    cout << "*ptr1 = " << *ptr1 << endl;

    return 0;
}
//end
/*OUT
*ptr1 = 5
*ptr2 = 1256764
*ptr3 = 7
*ptr1 = 6
*/

