#include "customer-props.h"
#include <QVariant>
#include <QMetaObject>
#include <QMetaEnum>
//start
CustProps::CustProps(QObject *parent, const QString name) 
    :QObject(parent) {
    setObjectName(name);
}

void CustProps::setId(const QString &newId) {
    m_Id=newId;
}
//end

void CustProps::setName(const QString &newName) {
    m_Name=newName;
}


void CustProps::setAddress(const QString &newAddress) {
    m_Address=newAddress;
}


void CustProps::setPhone(const QString &newPhone) {
    m_Phone=newPhone;
}


void CustProps::setDateEstablished(const QDate & newDate) {
    m_Date = newDate;
}

//start
void CustProps::setType(CustPropsType theType) {
    m_Type=theType;
}

/* Method for setting enum values from Strings. */
void CustProps::setType(QString newType) { /* Overloaded version
    that accepts a string as an argument.
    Sets value to -1 if unknown. */
    
    static const QMetaObject* meta = metaObject(); /* Because 
       they are static locals, the initializations happen
       only once. */
    static int propindex = meta->indexOfProperty("Type");
    static const QMetaProperty mp = meta->property(propindex);
    
    QMetaEnum menum = mp.enumerator(); /* This code gets
           executed each time. */
    const char* ntyp = newType.toAscii().data();
    m_Type = static_cast<CustPropsType>(menum.keyToValue(ntyp));
}

QString CustProps::getTypeString() const {
    return property("Type").toString();
}
//end

