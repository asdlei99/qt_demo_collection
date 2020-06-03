//start id=ctor
#include  "account.h"
#include <iostream>

Account::Account(unsigned acctNum, double balance, string owner) :
     m_AcctNum(acctNum), m_Balance(balance), m_Owner(owner)
    { }

JointAccount::JointAccount (unsigned acctNum, double balance,
                            string owner, string jowner)
    :Account(acctNum, balance, owner), 
     m_JointOwner(jowner)  /* base class initialization required */
     { }

JointAccount::JointAccount (const Account& acc, string jowner)
    :Account(acc), /* compiler-generated copy constructor call */
     m_JointOwner(jowner)
    { }
//end

//start id=dtor
Account::~Account() {
    cout << "Closing Acct - sending e-mail to primary acctholder:"
         << m_Owner << endl;
}
         
JointAccount::~JointAccount () {
    cout << "Closing Joint Acct - sending e-mail to joint acctholder:";
    cout << m_JointOwner << endl;
}

//end
