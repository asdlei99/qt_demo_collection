#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
using namespace std;

//start id=account
class Account {
 public:
    Account(unsigned acctNum, double balance, string owner);
    virtual ~Account();
 private:
    unsigned  m_AcctNum;
    double    m_Balance;
    string    m_Owner;
};
//end
//start id=jointaccount
class JointAccount : public Account {
 public:
    JointAccount (unsigned acctNum, double balance, 
                  string owner, string jowner);
    JointAccount(const Account & acct, string jowner);
    ~JointAccount();
 private:
    string m_JointOwner;
};
//end
#endif        //  #ifndef ACCOUNT_H

