#include <qstd.h>
#include <argumentlist.h>
#include <QProcess>
#include <cstdlib>

class Fork : public QProcess {
    public:
    Fork(QStringList argv = QStringList() ) {
        execute("environment", argv); /* Runs this same app as a
        child. */
    }
    ~Fork() {
        waitForFinished();
    }
};

int main(int argc, char* argv[]) {
    using namespace qstd;
    ArgumentList al(argc, argv);
    
    al.removeFirst();
    bool fork=al.getSwitch("-f");

    QStringList extraVars;
    if (al.count()  > 0) {
        setenv("PENGUIN", al.first().toAscii(), true);
    }
    cout << " HOME=" << getenv("HOME") << endl;
    cout << " PWD=" << getenv("PWD") << endl;
    cout << " PENGUIN=" << getenv ("PENGUIN") << endl;
    
    if (fork) {
        Fork f;   
    }
}
