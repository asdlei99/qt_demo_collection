#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
//start
class Student  {
 public:
    Student(QString nm, long id, QString m_Major, int year = 1);
    virtual QString getClassName() const;   /* Note the keyword virtual here. */ 
    QString toString() const; /* This should be virtual, too. */
    virtual ~Student() {}  /* It is a good idea to make the
        destructor virtual, too */
    QString yearStr() const;
 private:
    QString m_Name;
    QString m_Major;
    long m_StudentId;
 protected:
    int m_Year;
};
// derived classes are the same as before...
//end

class Undergrad: public Student {
 public:
    Undergrad(QString name, long id, QString major, int year);
    QString getClassName() const;

};

class GradStudent : public Student {
 public:
    enum Support { ta, ra, fellowship, other };
    GradStudent(QString nm, long id, QString major, 
                int yr, Support support);

    QString getClassName() const ;
    QString toString() const;
 protected:
    static QString supportStr(Support sup) ;
 private:
    Support  m_Support;
};


#endif        //  #ifndef STUDENT_H

