#include "constraintmap.h"

ConstraintMap map; /* Okay, ConstraintMap is already included. */

/* redundant but harmless if #ifndef wrapped. */
#include "constraintmap.h"

Constraint * constraintP;  /* Using forward declaration from constraintmap.h. */

// Constraint p;     /* error: incomplete type. */ 
#include <constraint.h>    
Constraint q;        /* Now it is a complete type. */

void ConstraintMap::addConstraint(Constraint& c) {
    cout << c.name(); /* complete type required here */ 
}
