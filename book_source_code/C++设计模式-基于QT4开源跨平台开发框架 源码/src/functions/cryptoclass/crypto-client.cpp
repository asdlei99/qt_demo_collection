#include "crypto.h"
#include <QTextStream>
QTextStream cout(stdout, QIODevice::WriteOnly);

int main()  {
     QString str1 ("This is a sample string"), str2;
     cout << "Original string: " << str1 << endl;
     QString seqstr("pspsps");
     ushort key(13579);
     Crypto crypt(key, seqstr);
     str2 = crypt.encrypt(str1);
     cout << "Encrypted string: " << str2 << endl;
     cout << "Recovered string: " << crypt.decrypt(str2) << endl;
 }


