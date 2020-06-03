#include <qstd.h>
using namespace qstd;
#include "customerlist.h"
#include "xmlexport.h"

int main(int argc, char** argv[]) {
    CustomerList *cl = CustomerList::sample();
    XMLExport xmle;
    cout << xmle.objectToXml(cl);
    delete cl;
    return 0;
}

