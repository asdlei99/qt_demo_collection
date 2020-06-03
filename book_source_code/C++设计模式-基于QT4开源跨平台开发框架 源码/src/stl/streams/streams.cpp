//start id="writing"
#include <iostream>
#include <sstream>
#include <fstream>

int main() {
    using namespace std;
    ostringstream strbuf;

    int lucky = 7;
    float pi=3.14;
    double e=2.71;
    
    /* An in-memory stream */
    strbuf << "luckynumber " << lucky << endl
           << "pi " << pi << endl
           << "e " << e << endl;

    string strval = strbuf.str(); /* Convert the stringstream to a string. */
    cout << strval;

    /* An output file stream. */
    ofstream outf; 
    outf.open("mydata");   /* Creates (or overwrites) a disk file for output. */
    outf << strval ;   
    outf.close();
//end

//start id="reading"
    /* An input file stream */
    ifstream inf;   
    inf.open("mydata"); 
    string newstr;  
    int lucky2;
    inf >> newstr >> lucky2;
    if (lucky != lucky2)
        cerr << "ERROR! wrong lucky number" << endl;
    
    float pi2;
    inf >> newstr >> pi2;
    if (pi2 != pi) cerr << "ERROR! Wrong pi." << endl;
    
    double e2;
    inf >> newstr >> e2;
    if (e2 != e) cerr << "e2: " << e2 << " e: " << e << endl;
    inf.close();   
//end
//start id="getline"
    /* Read line-by-line */
    inf.open("mydata");
    while (not inf.eof()) {
        getline(inf, newstr);
        cout << newstr << endl;
    }
    inf.close();
    return 0;
}
//end

