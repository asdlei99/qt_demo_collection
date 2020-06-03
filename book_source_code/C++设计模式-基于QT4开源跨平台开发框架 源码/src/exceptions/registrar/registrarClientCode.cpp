#include "registrar.h"
#include <qstd.h>

int main() {
    using namespace qstd;
    using namespace Registrar_Namespace;
    Registrar& reg = Registrar::instance();
    while (1) {
        try {
            reg.insert("George");
            reg.insert("Peter");
            reg.insert("Mildred");
            Student s("George");
            reg.insert(s);
            reg.remove(1000004);
            reg.remove(1000004);
            reg.remove(s);
            QStringList report = reg.report();
            foreach (QString line, report) {
                cout << line << endl;
            }
        } catch (NoStudentException& nse) { 
            cout << nse.what() << endl; 
        }
        catch (NoNumberException& nne) { 
            cout << nne.what() << endl;
        }
        catch (DupNumberException& dne) {
            cout << dne.what() << endl;
        }
    }
}
