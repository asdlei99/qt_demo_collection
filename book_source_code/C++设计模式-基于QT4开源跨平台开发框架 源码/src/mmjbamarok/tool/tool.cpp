/** mmjbamarok tool by Alan Ezust 
    $Date: 2007-10-11 19:54:03 -0400 (Thu, 11 Oct 2007) $
*/    

// Local headers
#include "tool.h"
#include "ratingmapper.h"
#include "mmjbamarok.h"

// Qt4 headers
#include <QSettings>
#include <QDateTime>
#include <QTextStream>
#include <QApplication>
#include <QFileInfo>
#include <QDir>
#include <QtSql>

// headers from my own libs (utils, filetagger, dataobject)
#include <qstd.h>
#include <argumentlist.h>
#include <filetagger.h>

// Initialize static switches
const float Tool::VERSION = 1.0;
bool Tool::dryRun = false;
bool Tool::verbose = false;
int Tool::initialSkip = 0;
bool Tool::remember = false;
QString Tool::prefix = "";

void Tool::showHelp() {
    using namespace qstd;
	cerr << "mmjbamarok tool version " << VERSION << endl;
    cerr << "Usage: \n" 
             << "  mmjbamarok [-d] [-v] [-r] [-p path] [-i [-s n]]  [-t]  [-test]  [-?]\n"
             << "   -p path   songs path (root of all relative paths) \n"
             << "   -i        import mmjb pref data into amarok statistics table\n"
             << "      -s n     skip over the first n files\n"
             << "   -t        tag files for mmjb from amarok db rating\n"
             << "   -r        remember, save the last tag/import time, skip over unchanged songs \n"
             << "   -u        update last tagged date to be the current date/time.\n"
             << "   -d        dry run  \n"
             << "   -v        verbose output\n"
             << "   -?        show help\n";
}

//start id="connect"
/** Opens a database connection
    @return a QSqlDatabase
*/
QSqlDatabase connect() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    bool ok = false;
    if (!ok) {
        db.setHostName("localhost");
        db.setDatabaseName("amarok");
        db.setUserName("amarok");
        db.setPassword("amarok");
        ok=db.open();
    }
    return db;
}
//end


uint Tool::saveLastImportDate() {
    QSettings s;
    QDateTime dt = QDateTime::currentDateTime();
    s.setValue("lastImport", dt.toTime_t());
    return dt.toTime_t();
}

uint Tool::lastImportDate() { 
    QSettings s;
    QVariant lastImport = s.value("lastImport", 0);
    return lastImport.toUInt();
}

//start id="import"
/** Imports tag data from all of the files in amarok's database.
    Assumes they are in musicmatch jukebox format. 
*/
void Tool::import() {
    using namespace qstd;
    RatingMapper mapper;
    FileTagger ft;
    ::connect();
    uint timestamp = QDateTime::currentDateTime().toTime_t();
	uint lidate = 0;
    QSqlQuery insert;
    int entries=0;
    int files=0;
    if (remember) {
        lidate = lastImportDate();
    }
    insert.prepare("INSERT INTO statistics (url, deviceid, rating, uniqueid, createdate, accessdate)"
        " VALUES (?, ?, ?, ?, ?, ?) "
        " ON DUPLICATE KEY UPDATE rating=? "); /* Prepare
            an SQL statement that inserts a new statistics record,
            or updates the current record (new rating), if the record is 
            already there. Each ? is a positional parameter to
            which we later addBindValue(). */ 
    QSqlQuery query;
    query.exec("select url, deviceid, uniqueid from uniqueid");
    QFileInfo finfo;
    int size = query.size();
    emit newProgressRange(0, size);
    while (query.next()) { /* Iterate through result set. */
        QString filename = query.value(0).toString();
        
        emit newProgressValue(++files);
        if (files < initialSkip) continue;
		if (!filename.endsWith(".mp3", Qt::CaseInsensitive)) continue;
		QVariant deviceid = query.value(1).toInt();
		QString uniqueid = query.value(2).toString();
        if (remember || verbose || dryRun) {
            finfo.setFile(filename);
            if (!finfo.exists()) {
                cerr << "Can't find file: " << filename << endl;
                continue;
            }
        }
        if (remember) {
            uint tt = finfo.lastModified().toTime_t();;
            if (tt < lidate) {
                if (verbose) {
					cerr << "Skipping " << filename << " because of earlier modification date. \n";
					emit newRow(filename, "skipped");
				}
                continue;
            }
        }
        ft.setFilename(filename);
        QString preference = ft.getPreference();
        int rating = mapper.toRating(preference); 
        if (rating == 0) continue;
        if (verbose || dryRun) {
            cerr << (dryRun? "[DRYRUN: " : "[" ) 
                 << files << "] " << rating << " : " << filename << endl;
        }
        if (dryRun) {
			emit newRow(filename, QString("<dryrun: %1>").arg(rating));
			continue;
		}
        insert.addBindValue(filename);
		insert.addBindValue(deviceid);
        insert.addBindValue(rating); 
		insert.addBindValue(uniqueid);
		insert.addBindValue(timestamp);
		insert.addBindValue(timestamp);
		insert.addBindValue(rating);
        if (insert.exec()) {
            entries++;
        }
        else {
            cerr << "    Err: " << insert.executedQuery()  << endl;
			cerr << "   " << insert.lastError().text() << endl;
        }
    }
    if (verbose) cerr << "Files processed: " << files << endl;
    cerr << "Entries imported:" << entries << endl;
    if (remember) {
        if (dryRun) cerr << " saveLastImportDate() " << 
        endl;
        else saveLastImportDate();
    }
        
}
//end

/** Saves the last tag date into QSettings for future executions, 
    so we can ignore the songs we have tagged on previous executions.
    @return number of seconds since some arbitrary date.
*/
uint Tool::saveLastTagDate() {
    QSettings s;
    QSqlDatabase db = ::connect();
    QSqlQuery query;
    query.exec("select max(accessdate) from statistics");
    if (query.next()) {
        QVariant retval = query.value(0);   
        s.setValue("lastTagged", retval);
        return retval.toUInt();
    }
    else return 0;
}

/**
   @return the last time someone used this program to tag some mmjb tags,
     in seconds since some arbitrary date.
*/
uint Tool::lastTagDate() {
    QSettings s;
    QVariant lastTagged = s.value("lastTagged", 0);
    return lastTagged.toUInt();
}


/** Queries an amarok database for recently set ratings of
    tracks, and tags the id3v2 tags with corresponding mmjb
    preference values 
    @param remember if true, store the last time we did this and skip over 
            the records which were not accessed since then. 
*/

void Tool::tag() {
    using namespace qstd;
    QSqlDatabase db = ::connect();
    QSqlQuery query;
    QString queryString = "select url,rating,accessdate from statistics where rating > 0 and accessdate";
    if (remember) {
        QString str;
        str = QString(" > %1").arg(lastTagDate());
        queryString += str;
    }
    query.exec(queryString);
    RatingMapper mapper;
    FileTagger ft;
    int size = query.size();
    int count = 0;
    emit newProgressRange(0, size);
    while (query.next()) {
		QString result;
        emit newProgressValue(++count);
        QString filename = query.value(0).toString();
		if (!filename.endsWith(".mp3", Qt::CaseInsensitive)) continue;
        int rating = query.value(1).toInt();
        QString preference = mapper.toPreference(rating);
         
        if (dryRun) {
			result = QString(" <dryrun set: %1>").arg(preference);
            cerr << filename << result << endl;
			emit newRow(filename, result);
            continue;
        }
        ft.setFilename(filename);
        QString oldPref = ft.getPreference();
        if (oldPref != preference) {
            ft.setPreference(preference);
        }
        else {
			result = "SKIPPED";
            cerr << "[SKIPPED: " << preference << ":" << filename << "]" << endl;
			emit newRow(filename, result);
            continue;
        }
        if (verbose) {
            cerr << "[ " << preference << ":" << filename << "]" << endl; 
        }
		result = QString("<TAG: %1>").arg(preference);
		emit newRow(filename, result);
        ft.commit();
    }
    if (remember) {
        if (dryRun) cerr << "saveLastTagDate();";
        else saveLastTagDate();
    }
}


void testLastTagged() {
    using namespace qstd;
    uint time = Tool::lastTagDate();
    QDateTime date;
    date.setTime_t(time);
    cerr << "LastTagged: " << time << ": " << date.toString()
        << endl;
}



int main(int argc, char** argv) {
	
    QApplication app(argc, argv);
    app.setOrganizationName("kde");
    app.setOrganizationDomain("kde.org");
    app.setApplicationName("mmjbamarok");
    
    ArgumentList al;
    Tool tool;    
    if (al.getSwitch("-?") || al.getSwitch("--help")) {
        tool.showHelp();
        return 0;
    }
    QString skipStr = al.getSwitchArg("-s", "0");
    Tool::initialSkip = skipStr.toUInt();
    Tool::prefix = al.getSwitchArg("-p", "");
    if (Tool::prefix.length() > 0) {
        QDir::setCurrent(Tool::prefix);
    }
    if (al.getSwitch("-r")) {
        Tool::remember=true;
    }
    if (al.getSwitch("-d")) {
        Tool::dryRun = true;
    }
    if (al.getSwitch("-v")) {
        Tool::verbose = true;
    }
    if (al.getSwitch("-test")) {
        testLastTagged();
    }
    else if (al.getSwitch("-u")) {
        Tool::saveLastTagDate();
    }
    else if (al.getSwitch("-i")) {
        tool.import();
    }
    else if (al.getSwitch("-t")) {
        tool.tag();
    }
    else { /* Run GUI */
		MMJBAmarok mainWin;
		mainWin.show();
		return app.exec();
	}
    return 0;
}
