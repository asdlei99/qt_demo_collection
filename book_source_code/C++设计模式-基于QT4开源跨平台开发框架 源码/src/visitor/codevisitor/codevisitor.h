#ifndef _CODE_VISITOR_H_
#define _CODE_VISITOR_H_

#include <filevisitor.h>
#include <QStringList>


/**
   This program will visit every selected file
   in or below the specified directory and produce a list
   of the names of the files that it #includes.
*/
//start
class CodeVisitor : public FileVisitor {
  public:
    CodeVisitor(QString filter = "*.h,*.cpp", bool recursive = true);
    CodeVisitor(QStringList filterList, bool recursive = true);
    void processFile(QString filename);
    int getNumFiles() const;
    QString getResultString() const;
 private:
    int m_NumFiles;
    QStringList m_Result;
};
//end
#endif
