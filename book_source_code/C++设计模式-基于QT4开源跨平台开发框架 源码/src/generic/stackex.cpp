// Filename: stackex.cpp
// Template stack implementation with exception handling

#include <iostream>
#include "utility.h"                              // for setInt()

using namespace std;

class Stack {
public:
    explicit Stack(int n) throw(int, bad_alloc);
    ~Stack() {
        delete []m_P;
    }
    void  reset() {
        m_Top = EMPTY;
    }
    void  push(char c) {
        m_P[++m_Top] = c;
    }
    char  pop() {
        return m_P[m_Top--];
    }
    char  getTop() const {
        return m_P[m_Top];
    }
    bool  empty() const {
        return (m_Top == EMPTY);
    }
    bool  full() const {
        return (m_Top == m_MaxLen - 1);
    }
private:
    enum {EMPTY = -1};
    char*  m_P;
    int    m_MaxLen;
    int    m_Top;
};

//Stack constructor with exceptions
Stack::Stack(int n) throw(int, bad_alloc) {
    if (n < 1)
        throw (n);                                    //want a positive value
    m_P = new char[n];                               //create a Stack of characters
    m_Top = EMPTY;
    m_MaxLen = n;
}


int main() {
    int n = 1;
    while (n != 0) {
        cout << "Enter Stack size: ";
        n = setInt();
        try {
            Stack  st(n);                               // if n is negative or 0, then give error
            char ch =  'A';
            while (!st.full())
                st.push(ch++);
            cout << "Stack contains: ";
            while (!st.empty())
                cout << st.pop() << ' ';
            cout << endl;
        }                                             //try
        catch (int n) {
            cerr << "Wrong size = " << n << endl;
        }
        catch (bad_alloc&) {
            cerr << "Insufficient memory" << endl;
        }
    }
    cout << "Bye!" << endl;
    return 0;
}
