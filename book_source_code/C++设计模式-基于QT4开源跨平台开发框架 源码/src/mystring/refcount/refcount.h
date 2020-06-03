// MyString with reference counter
#ifndef _REF_COUNT_H_
#define _REF_COUNT_H_

#include  <iostream>
#include  <cstring>
using namespace std;

//start 
class MyString {
    class MyStringPrivate {
        friend class MyString; /* Even though this is an inner
        class, we need to give friend permissions to the
        containing class. */
      public:
        MyStringPrivate() : m_Len(0), m_RefCount(1) {
            m_Chars = new (nothrow) char[1] ;
            m_Chars[0] = 0;
        }
        MyStringPrivate(const char* p) : m_RefCount(1) {
            m_Len = strlen(p);
            m_Chars = new (nothrow) char[m_Len + 1];
            if (m_Chars)
                strncpy(m_Chars, p, m_Len + 1);
            else 
                cerr << "Out of memory in MyStringPrivate constructor!" << endl;
        }
        ~MyStringPrivate() {
            delete []m_Chars;
        }
      private:
            int    m_Len, m_RefCount;
            char*  m_Chars;
    };

  public:
    MyString()  : m_Impl(new MyStringPrivate) {}
    MyString(const char* p)
      : m_Impl(new MyStringPrivate(p)) {}
    MyString(const MyString& str);
    ~MyString();
    void operator=(const MyString& str);
    void display() const ;
    int length() const;
  private:
    MyStringPrivate*  m_Impl;
};
//end
#endif

