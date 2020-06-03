#include <qstd.h>
#include <QRegExp>
#include <QString>

using namespace qstd;
//start
QRegExp usformat
("(\\+?1[- ]?)?\\(?(\\d{3})\\)?[\\s-]?(\\d{3})[\\s-]?(\\d{4}"); /* All
    U.S. format numbers have country-code 1, and have 3 + 3 + 4 = 10 digits.
    Whitespaces, dashes and parantheses between these digit groups 
    are ignored, but they help to make the digit groups recognizable. */

QRegExp nlformat
("(\\+|00)?[\\s\\-]?(31)[\\s\\-]?(\\d\\d)[\\s\\-]?(.*)$"); /* Netherlands
    (countrycode 31) numbers have 2 + 2 + 7 = 11 digits. */

QRegExp nlformat2
("(\\d\\d)(\\d\\d)(\\d{3}"); /* The last 7 digits will be be 
    arranged as  2 + 2 + 3. */

QRegExp filtercharacters
("[\\s-\\+\\(\\)\\-]"); /* These are characters we ignore in the last
7 digits of NL numbers. */

QString stdinReadPhone() { /* Ensures that the user-entered phone string
complies with a regular expression, and extracts the proper 
components from it.  */
    QString str;
    bool format=false;
    do {         /* Keep asking until you get a valid number. */
        cout << "Enter a phone Number (or q to quit): ";
        cout.flush();
        str = cin.readLine();
        if (str=="q")
            return str;
        if (usformat.exactMatch(str)) {
            format = true;
            QString areacode = usformat.cap(2);
            QString exchange = usformat.cap(3);
            QString number = usformat.cap(4);
            str = QString("(US/Canada) +1 %1-%2-%3")
                  .arg(areacode).arg(exchange).arg(number);
        }
//end
        if (nlformat.exactMatch(str)) {
            QString country = nlformat.cap(2);
            QString citycode = nlformat.cap(3);
            QString rest = nlformat.cap(4);
            rest.remove(filtercharacters);
            if (nlformat2.exactMatch(rest)) {
                format = true;
                QString number = QString("%1-%2-%3")
                                 .arg(nlformat2.cap(1))
                                 .arg(nlformat2.cap(2))
                                 .arg(nlformat2.cap(3));
                cout << "\n Number: " << number;
                str = QString("(NL) + %1 (0)%2-%3").
                      arg(country).arg(citycode).arg(number);
            }
        }
//start
        if (format == false) {
            cout << "Unknown format" << endl;
        }
    } while (format == false) ;
    return str;
}

int main() {
    QString str;
    do {
        str =  stdinReadPhone();
        if (str != "q")
            cout << "validated: " << str << endl;
    } while (str != "q");
    return 0;
}
//end
