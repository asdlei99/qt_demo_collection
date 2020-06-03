#include "static.h"

int main() {
    Thing::showCount();  /* No objects exist at this point. */
    Thing t1(3,4), t2(5,6);
    t1.showCount();  /* direct access through object */
    {  /* An inner block of code is entered. */
        Thing t3(7,8), t4(9,10);
        Thing::showCount(); 
    } /* end inner block */

    Thing::showCount(); 
    return 0;
}

