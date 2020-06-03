#include "mp3db.h"

#include <filetagger.h>
#include <mp3file.h>
#include <QDebug>
#include <QSqlError>
#include <QFile>
#include <QPointer>

//start id=connect
bool Mp3db::connect()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("mp3db");
    db.setUserName("mp3user");
    db.setPassword("mp3dbpw");
    if (!db.open()) {
        qCritical("Cannot open database: %s (%s)", 
                db.lastError().text().toLatin1().data(),
                qt_error_string().toLocal8Bit().data());
        return false;
    }
    return true;
}
//end
//start id=prepare

Mp3db::Mp3db()  {
    connect();
    // QSqlQuery m_insertQuery;
    m_insertQuery.prepare("INSERT INTO FileTagger ("
                        "Artist, TrackTitle, AlbumTitle, TrackNumber, Genre, "
                        "Comment, Preference, Filename) VALUES (?,?,?,?,?,?,?,?)");
}
//end
//start id=add
void Mp3db::addFile(FileTagger* song) {
    m_insertQuery.addBindValue(song->getArtist());
    m_insertQuery.addBindValue(song->getTrackTitle());
    m_insertQuery.addBindValue(song->getAlbumTitle());
    m_insertQuery.addBindValue(song->getTrackNumber());
    m_insertQuery.addBindValue(song->getGenre());
    m_insertQuery.addBindValue(song->getComment());
    m_insertQuery.addBindValue(song->getPreference());
    m_insertQuery.addBindValue(song->getFilename());
    m_insertQuery.exec();
}
//end
void Mp3db::addFile(QString filename) {
    m_ft.setFilename(filename);
    addFile(&m_ft);
}

void Mp3db::clearSongs() {
    //    Q_ASSERT(FALSE);
    QSqlQuery query;
    //    int rows = rowCount();
    query.exec("delete from FileTagger");
    qDebug() << "All Clear()";
    reset();
}
