#include <iostream>
#include <string>

int main() {
    using namespace std;
    const char* charstr = "this is one very long string "
                " so I will continue it on the next line";
    string str = charstr; /* STL strings can hold onto
          C-style char* strings */
    cout << str << endl;
    cout << "\nA\tb\\c\'d\"" << endl;
    return 0;
}

