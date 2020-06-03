#include "refcount.h"
void fiddle(MyString lstr1) {
    cout << "inside fiddle()" << endl;
    MyString lstr2(lstr1);
    MyString lstr3;
    lstr3 = lstr2;
}

int main() {
    MyString  str1("AABBCCDD");
    {
        cout << "local block begins" << endl;
        MyString str2(str1);
        fiddle(str2);
        cout << "back from fiddle()" << endl;
    } 
    cout << "local block ends" << endl;
    str1.display();
    cout << endl;
    return 0;
}

