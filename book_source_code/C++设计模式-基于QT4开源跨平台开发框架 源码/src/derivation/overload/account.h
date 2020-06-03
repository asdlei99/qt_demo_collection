#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QDate>
//start
class Account {
protected:
    static const int SS_LEN = 80;
public:
    virtual void deposit(double amt);
    virtual const char* toString() const;
    virtual const char* toString(char delimiter); /* overloaded
       function */
protected:
    unsigned  m_AcctNo;
    double    m_Balance;
    char     m_Owner[SS_LEN];
};

class InsecureAccount: public Account {
public:
    const char* toString() const; /* Overrides base method
       and hides toString(char). */
    void deposit(double amt, QDate postDate); /* Does not
       override any method, but hides all Account::deposit()
       methods */
};
//end
#endif        //  #ifndef ACCOUNT_H

