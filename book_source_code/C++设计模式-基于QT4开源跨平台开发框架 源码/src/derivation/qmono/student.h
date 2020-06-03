#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student  {
 public:
    Student(QString nm, long id, QString m_Major, int year = 1);
    ~Student() {}
    QString getClassName() const; /* There are other ways
             of identifying the classname that are better 
             than defining a getClassName() for each class.
             getClassName() is used here only to demonstrate
             how inheritance and polymorphism work. */
    QString toString() const;
    QString yearStr() const;
 private:
    QString m_Name;
    QString m_Major;
    long m_StudentId;
 protected:
    int m_Year;
};

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

