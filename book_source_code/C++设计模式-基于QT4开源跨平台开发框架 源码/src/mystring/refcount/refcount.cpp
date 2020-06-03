#include "refcount.h"

//start
MyString::MyString(const MyString& str) : m_Impl(str.m_Impl) {
    m_Impl -> m_RefCount++;
    cout << m_Impl->m_Chars << "::refcount: " << m_Impl->m_RefCount << endl;
}

MyString::~MyString() {
    cout << m_Impl->m_Chars << "::refcount: " << m_Impl->m_RefCount << endl;
    if (--m_Impl -> m_RefCount == 0) {
        cout << m_Impl->m_Chars << "::memory released" << endl;
        delete m_Impl;
    }
}

void MyString::operator=(const MyString& str) {
    if (str.m_Impl != m_Impl) {
        if (--m_Impl -> m_RefCount == 0)
            delete m_Impl;
        m_Impl = str.m_Impl;   /* Just copy the address. */
        ++(m_Impl->m_RefCount);
    }
}
//end
void  MyString::display() const {
    cout << m_Impl -> m_Chars;
}

int MyString::length() const {
    return m_Impl->m_Len;
}

