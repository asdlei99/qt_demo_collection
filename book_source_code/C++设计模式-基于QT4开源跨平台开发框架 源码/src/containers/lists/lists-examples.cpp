#include <QStringList>
#include <QDebug>
#include <cassert>

/* Some simple examples using QStringList, split and join */

int main() {

    QString winter = "December, January, February";
    QString spring = "March, April, May";
    QString summer = "June, July, August";
    QString fall = "September, October, November";

    QStringList list;
    list << winter;        /* append operator 1 */
    list += spring;        /* append operator 2 */
    list.append(summer);   /* append member function */
    list << fall;

    qDebug() << "The Spring months are: " << list[1] ;
    
    
    QString allmonths = list.join(", "); 
    /* from list to string - join with a ", " delimiter */
    qDebug() << allmonths;

    QStringList list2 = allmonths.split(", ");  
    /* split is the opposite of join. Each month will have its own element. */

    assert(list2.size() == 12); /* assertions abort the program
        if the condition is not satisfied. */

    foreach (QString str, list) {  /* Qt 4 foreach loop - similar
      to Perl/Python and Java 1.5  style for loops. */
        qDebug() << QString(" [%1] ").arg(str);
    }

    for (QStringList::iterator it = list.begin();
         it != list.end(); ++it) { /* C++ STL-style iteration */
        QString current = *it;   /* pointer-style dereference */
        qDebug() << "[[" << current << "]]";
    }
    
    QListIterator<QString> itr (list2); /* Java 1.2 style Iterator */ 
    while (itr.hasNext()) {  /* Java Iterators point
                                inbetween elements. */
        QString current = itr.next();
        qDebug() << "{" <<  current << "}";
    }
    
    return 0;
}

