//start id=dtor
#include "bank.h"
#include "account.h"

Bank::~Bank() {
    foreach (Account* acct, m_Accounts) {
        delete acct;
    }
    m_Accounts.clear();
}
//end

//start id=main
Bank& Bank::operator<< (Account* acct) {
   m_Accounts << acct;
   return *this;   
}

int main(int argc, char* argv[]) { 
    Bank b;
    Account* a1 = new Account(1, 423, "Gene Kelly");
    JointAccount *a2 = new JointAccount(2, 1541, "Fred Astaire",
    "Ginger Rodgers");
    b << a1;
    b << a2;
} /* At this point, the Bank and both Accounts are destroyed. */
//end

