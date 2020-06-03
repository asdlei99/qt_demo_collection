// Filename:  tstack.cpp
//template stack implementation:  parametric polymorphism
// Allows the same code to be used with different types.
#include <iostream>
using namespace std;

template <class T>
class Stack {
public:
    explicit Stack(int size = 1000);
    ~Stack() {
        delete []m_S;
    }
    void  reset() {
        m_Top = EMPTY;
    }
    void  push(T c) {
        m_S[++m_Top] = c;
    }
    T  pop() {
        return m_S[m_Top--];
    }
    T  top_of()const {
        return m_S[m_Top];
    }
    bool  empty()const {
        return (m_Top == EMPTY);
    }
    bool  full()const {
        return (m_Top == m_MaxLen - 1);
    }
private:
    enum {EMPTY = -1};
    T*  m_S;
    int    m_MaxLen;
    int    m_Top;
};

template <class T>
Stack<T>::Stack(int size /*=1000*/) : m_MaxLen(size) {
    m_S = new T[size];
    m_Top = EMPTY;
}


//Reversing a series of char* represented strings
void reverse(char* str[], int n) {
    Stack<char*>  stk(n);                           //this Stack holds char*
    for (int i = 0; i < n; ++i)
        stk.push(str[i]);
    for (int i = 0; i < n; ++i)
        str[i] = stk.pop();
}


int main()                                        // Client code
{
    Stack<char>  cStk1(100);                        //size only
    Stack<char>  cStk2;                             //no size?
    char reverseline[200];
    char a[] = {"My name is Salvador Dali!\n"};
    char b[] = {"My name is Vassily Kandinsky!\n"};
    Stack <char*> strStk;
    Stack<int>  intStk;
    int  i = 0;
    cStk1.reset();
    while (a[i])
        if (!cStk1.full())
            cStk1.push(a[i++]);
    i = 0;
    while (!cStk1.empty())
        reverseline[i++] = cStk1.pop();
    reverseline[i] = '\0';
    cout << reverseline;
    i = 0;
    while (b[i])
        if (!cStk2.full())
            cStk2.push(b[i++]);
    i = 0;
    while (!cStk2.empty())
        reverseline[i++] = cStk2.pop();
    reverseline[i] = '\0';
    cout << reverseline;
    i = 0;
    intStk.push(9);
    cout << "\nint Stack has " << intStk.pop()
    << endl;
    strStk.push("A string");
    while (!strStk.empty())
        cout << strStk.pop() << endl;
    return 0;
}
