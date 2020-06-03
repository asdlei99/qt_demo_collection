// Filename: STL-stack.cc
// Adapting a stack from a vector
#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string, vector<string> > strStack;
    string quote[3] = {
                          "Any food that starts out hard will soften when stale.\n",
                          "Any food that starts out soft will harden when stale.\n",
                          "Isaac's Strange Rule of Staleness\n"
                      };

    for (int i =0; i < 3; ++i)
        strStack.push(quote[i]);
    while (!strStack.empty()) {
        cout << strStack.top();
        strStack.pop();
    }
}


/*out
OOP> gpp STL-stack.cc
OOP> a.out
Isaac's Strange Rule of Staleness
Any food that starts out soft will harden when stale.
Any food that starts out hard will soften when stale.
OOP>
*/