#include <iostream>
#include "thing.h"


void Thing::set(int num, char c) {
    m_Number = num;
    m_Character = c;
}

void Thing::increment() {
    ++m_Number;
    ++m_Character;
}

void Thing::show() {
    using namespace std;
    cout << m_Number << '\t' << m_Character << endl;
}

