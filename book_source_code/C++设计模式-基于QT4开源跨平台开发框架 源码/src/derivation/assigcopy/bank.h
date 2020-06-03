#ifndef BANK_H
#define BANK_H
#include <QList>
class Account;

class Bank {
 public:
    Bank& operator<< (Account* acct); /* This is how 
         we add object ptrs into m_Accounts. */
    ~Bank();
 private:
    QList<Account*> m_Accounts;
};
#endif

