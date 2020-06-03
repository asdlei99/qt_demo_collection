
/* This function searches for all Mp3 files in a directory
   tree and adds them. */

void Mp3Db::recurseAddDir(QDir d) {
    d.setSorting( QDir::Name );
    d.setFilter( QDir::Files | QDir::Dirs );
    QStringList qsl = d.entryList();
    foreach (QString entry, qsl) {
        QFileInfo finfo(entry);
        if ( finfo.isSymLink () && !m_SymLink )
            return;
        if ( finfo.isDir() ) {
            if (!m_Recursive )
                return;
            QString dirname = finfo.fileName();
            if ((dirname==".") || (dirname == ".."))
                return;
            QDir sd(finfo.filePath());
            if (skipDir(sd))
                continue;
            recurseAddDir(sd);
        } else {
            if (finfo.extension(false)=="mp3") {
                addMp3File(finfo.absFilePath()); /* non-reusable part */
            }
        }
    }
}

