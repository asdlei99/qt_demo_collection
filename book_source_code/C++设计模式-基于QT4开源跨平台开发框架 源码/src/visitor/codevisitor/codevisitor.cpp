#include "codevisitor.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>


CodeVisitor::CodeVisitor(QString filters, bool recursive) : m_NumFiles(0) {
        QStringList filterList = filters.split(",");
        setFilters(filterList);
        setRecursive(recursive);
}
CodeVisitor::CodeVisitor(QStringList filterList, bool recursive) :
    FileVisitor(filterList, recursive), m_NumFiles(0) { }


//start id="processfile"
void CodeVisitor::processFile(QString filename) {
    m_Result << filename;
    QString line;
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream filestream(&file);
    while (! filestream.atEnd()) {
        line = filestream.readLine();
        if (line.startsWith("#include"))
            m_Result << QString("    %1").arg(line);
    }
    file.close();
    ++m_NumFiles;
}
//end

int CodeVisitor::getNumFiles() const {
    return m_NumFiles;
}

QString CodeVisitor::getResultString() const {
    return m_Result.join("\n");
}

