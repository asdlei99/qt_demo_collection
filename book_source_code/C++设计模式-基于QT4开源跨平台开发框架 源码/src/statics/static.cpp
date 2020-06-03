#include "static.h"
#include <iostream>

int Thing::sm_Count = 0;  /* must initialize static member! */

Thing::Thing(int a, int b)
        : m_First(a), m_Second(b) {
    ++sm_Count;
}

Thing::~Thing() {
    --sm_Count;
}

void Thing::display() const {
    using namespace std;
    cout << m_First << "$$" << m_Second;
}

void Thing::showCount() {      /* static function */
    using namespace std;
    cout << "Count = " << sm_Count << endl;
}

