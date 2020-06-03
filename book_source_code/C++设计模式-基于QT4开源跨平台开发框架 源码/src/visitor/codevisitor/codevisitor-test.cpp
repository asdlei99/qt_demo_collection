
#include <argumentlist.h>
#include <codevisitor.h>
#include <QApplication>
#include <qstd.h>
using namespace qstd;

void usage(QString appname) {
    cout << appname << " Usage: \n"
         << "codevisitor [?] [-r] [-d startdir] [-f filter] [file-list]\n"
         << "\t-?        \tthis help list\n"
         << "\t-r        \tvisitor will recurse into subdirs\n"
         << "\t-d startdir\tspecifies starting directory\n"
         << "\t-f filter\tfilename filter to restrict visits (i.e. -f \"*.cpp\") \n"
         << "\toptional list of files to be visited\n" 
         << "Use double quotes to delimit all strings in command line."<< endl;
}

int main(int argc, char** argv) {
    ArgumentList al(argc, argv);
    QString appname = al.takeFirst(); /* app name is always first in the list. */ 
    if (al.getSwitch("?") or al.getSwitch("-?")) {
        usage(appname);
        exit(1);
    }
    bool recursive(al.getSwitch("-r"));
    QString startdir(al.getSwitchArg("-d"));
    QStringList filterList;
    QString filter;
    
    while ((filter = al.getSwitchArg("-f", QString())) != QString()) {
        cout << "added filter: " << filter << endl;
        filterList << filter;
    }
    CodeVisitor cvis(filterList, recursive);
    if (startdir != QString()) {
		// change directory to startdir
        cvis.processEntry(startdir);
    }
    if (al.size()) {
        cvis.processFileList(al);
    }

    cout << "Files Processed: " << cvis.getNumFiles() << endl;
    cout << cvis.getResultString() << endl;
    return 0;
}

