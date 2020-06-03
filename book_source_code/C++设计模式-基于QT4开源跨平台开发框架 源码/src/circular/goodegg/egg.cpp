#include "chicken.h"
#include "egg.h"

Chicken* Egg::getParent() {
    return new Chicken(); /* requires definition of Chicken */   
}
