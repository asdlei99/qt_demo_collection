#include <QString>
#include <qstd.h>
using namespace qstd;
#include "vtable.h"

Base::Base() {
    m_X = 4;
    m_Y = 12;
    cout << " Base::Base: " ;
    virtualFun();
}

Derived::Derived() {
    m_X = 5;
    m_Y = 13;
    m_Z = 22;
}

void Base::virtualFun() const {
    QString val=QString("[%1,%2]").arg(m_X).arg(m_Y);
    cout << " VF: the opposite of Acid: " << val << endl;
}

void Derived::virtualFun() const {
    QString val=QString("[%1,%2,%3)")
        .arg(m_X).arg(m_Y).arg(m_Z);
    cout << " VF: add some treble: " << val << endl;
}

Base::~Base() {
    cout << " ~Base() " << endl;
    virtualFun();
}

Derived::~Derived() {
    cout << " ~Derived() " << endl;
}


int main() {
    Base b;
    Derived d;
}

