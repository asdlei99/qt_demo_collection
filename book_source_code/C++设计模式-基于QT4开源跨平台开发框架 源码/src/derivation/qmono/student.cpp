//start id="student"
#include <QTextStream>
#include "student.h"

Student::Student(QString nm, long id, QString major, int year)
        : m_Name(nm), m_Major(major), m_StudentId(id), m_Year(year) {}


QString Student::getClassName() const {
    return "Student";
}

QString Student::toString() const {
    QString retval;
    QTextStream os(&retval); /* We write to the
       stream, and return the string it uses. */
    os << "[" << getClassName() << "]" 
         << " name: " << m_Name
         << " Id: " << m_StudentId
         << " Year: " << yearStr()
         << " Major: " << m_Major  ;
    return retval;
}
//end

QString Student::yearStr() const {
    switch(m_Year) {
    case 1:
        return "fresh";
    case 2:
        return "soph";
    case 3:
        return "junior";
    case 4:
        return "senior";
    case 5:
        return "graduate student";
    case 6:
        return "gradual student";
    case 7:
        return "oldtimer";
    case 8:
        return "relic";
    }
    return "unknown";
}


//start id="undergrad"
Undergrad::Undergrad(QString name, long id, QString major, int year)
                : Student(name, id, major, year) /* The base class 
                object is considered a subobject of the derived object.
                Class members and base classes both must be
                initialized and cleaned up in an order determined by
                the order that they appear in the class definition. */
               { }

QString Undergrad::getClassName() const {
    return "Undergrad";
}
                  
//end

//start id="grad"
GradStudent::
GradStudent(QString nm, long id, QString major, int yr, 
                   Support support) :Student(nm, id, major, yr), 
            m_Support(support) { }

QString GradStudent::toString() const {
    QString result;
    QTextStream os(&result);
    os <<  Student::toString()  /* base class version */
         << "\n  [Support: "      /* ... plus items that are specific to GradStudent  */ 
         << supportStr(m_Support)
         << " ]\n";
    return result;
}
//end

QString GradStudent::supportStr(Support sup) {
    switch(sup) {
    case ta:
        return "ta";
    case ra:
        return "ra";
    case fellowship:
        return "fellowship";
    case other:
        return "other";
    }
    return "unknown";
}
QString GradStudent::getClassName() const {
    return "GradStudent";
}

