#include <QList>
#include <assertequals.h>
#include <QtAlgorithms>   // for qSort()
#include <qstd.h>         // for cin and cout
using namespace qstd;

class CaseIgnoreString : public QString {
public:
    CaseIgnoreString(const QString& other = QString()) : QString(other) {}

    bool operator<(const QString & other) const {
        return toLower() < other.toLower();
    }
    bool operator==(const QString& other) const {
        return toLower() == other.toLower();
    }
};

int main() {
    CaseIgnoreString s1("Apple"), s2("bear"), 
                     s3 ("CaT"), s4("dog"), s5 ("Dog");

    ASSERT_TRUE(s4 == s5);
    ASSERT_TRUE(s2 < s3);
    ASSERT_TRUE(s3 < s4);

    QList<CaseIgnoreString> namelist;

    namelist << s5 << s1 << s3 << s4 << s2; /* Insert 
        all items in an order that is definitely not sorted. */ 
 
    qSort(namelist.begin(), namelist.end());
    int i=0;
    foreach (QString stritr, namelist) {
        cout << QString("namelist[%1] = %2")
                       .arg(i++).arg(stritr) << endl;
    }

    QStringList strlist;
    strlist << s5 << s1 << s3 << s4 << s2; /* The value
    collection holds QString, but we are adding 
    CaseIgnoreString. A conversion is required. */

    qSort(strlist.begin(), strlist.end());
    cout << "StringList sorted: " + strlist.join(", ") << endl;
    return 0;
}

