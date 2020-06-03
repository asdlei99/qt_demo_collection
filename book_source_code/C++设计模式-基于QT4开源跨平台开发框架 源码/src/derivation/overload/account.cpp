#include  "account.h"
#include <cstring>
#include <iostream>
using namespace std;

int main() {
    InsecureAccount acct;
    acct.deposit(6.23); /*  Error! No matching function -
           hidden by deposit(double, int) */
    acct.m_Balance += 6.23; /* Error! Member is protected,
         inaccessible. */
    acct.Account::deposit(6.23); /* Hidden does not mean
        inaccessible. We can still access hidden public members
        via scope resolution. */
    return 0;
}

