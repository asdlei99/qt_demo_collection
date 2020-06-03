#include "a.h"
#include "b.h"

int main() {
    using A::f; /* declaration - brings A::f() into scope */
    f();
    using namespace B; /* directive - brings all of
    B into scope */
    g();  /* okay */
    f();  /* ambiguous */
}
/*OUT
f from A
g from B
f from A
*/

