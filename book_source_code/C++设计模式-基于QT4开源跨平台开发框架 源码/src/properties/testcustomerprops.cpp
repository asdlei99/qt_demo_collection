#include "customer-props.h"
#include <assertequals.h>
#include <QVariant>
#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>

/** A function which converts any QObject with
    properties into a QString, using metaproperties.
*/
//start id=objToString
QString objToString(const QObject* obj) {
    QStringList result;
    const QMetaObject *meta = obj->metaObject(); /* We introspect 
        into the object via the QMetaObject. */
    result += QString("class %1 : public %2 {").arg(meta->className())
        .arg(meta->superClass()->className());
    for (int i=0; i < meta->propertyCount(); ++i) {
        const QMetaProperty qmp = meta->property(i);
        QVariant value = obj->property(qmp.name());     
        result += QString("  %1 %2 = %3;")
            .arg(qmp.type())
            .arg(qmp.name())
            .arg(value.toString());
    }
    result += "};";
    return result.join("\n");
}
//end
//start id=main
int main() {
    CustProps cust;
    cust.setName("Falafal Pita"); /* setting some simple properties */
    cust.setAddress("41 Temple Street; Boston, MA; 02114");
    cust.setPhone("617-555-1212");
    cust.setType("Government");  /* setting enum property as a string */
    ASSERT_EQUALS(cust.getType(), CustProps::Government); /* comparing to enum value */
    QString originalid = "834"; /* seting a string property */
    cust.setId(originalid);
    QVariant v = cust.property("Id");  /* getting it back as a QVariant through the 
          QObject base class method */
    QString str = v.toString();
    ASSERT_EQUALS(originalid, str);
    QDate date(2003, 7, 15); 
    cust.setProperty("DateEstablished", QVariant(date)); /* setting 
        date properties, wrapped in QVariants */
    QDate anotherDate = cust.getDateEstablished(); /* The date comes
        back through the type-specific getter. */
    ASSERT_EQUALS(date, anotherDate);
    cust.setId(QString("anotherId"));
    qDebug() << objToString(&cust);
    cust.setType(CustProps::Educational);
    qDebug() << " Educational=" << cust.getType();
    cust.setType("BogusType");
    qDebug() << " Bogus= " << cust.getType();
    return 0;
}
//end
