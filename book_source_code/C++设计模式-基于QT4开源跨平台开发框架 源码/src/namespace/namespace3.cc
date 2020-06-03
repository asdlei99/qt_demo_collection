#include "a.h"
#include "b.h"

int main() {
    using namespace A; /* brings all of A into scope */
    f();
    using namespace B; /* brings all of B into scope */
    g();
    f();              
}
/*OUT
OOP> gpp namespace3.cc
namespace3.cc: In function `int main()':
namespace3.cc:10: call of overloaded `g ()' is
ambiguous
b.h:6: candidates are: void B::g()
a.h:6:                 void A::g()
namespace3.cc:11: call of overloaded `f ()' is
ambiguous
b.h:4: candidates are: void B::f()
a.h:4:                 void A::f()
OOP>
*/
