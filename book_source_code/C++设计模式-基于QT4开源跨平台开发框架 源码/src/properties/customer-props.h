#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include <QObject>
#include <QDateTime>
#include <QString>
//start
class CustProps : public QObject {
    Q_OBJECT  /* macro required for moc to preprocess class */

    /* Each property declaration has the following syntax:

    Q_PROPERTY( type name READ getFunction [WRITE setFunction]
    [RESET resetFunction] [DESIGNABLE bool]
    [SCRIPTABLE bool] [STORED bool] )
    */

    Q_PROPERTY( QString Id READ getId WRITE setId );
    Q_PROPERTY( QString Name READ getName WRITE setName );
    Q_PROPERTY( QString Address READ getAddress WRITE setAddress );
    Q_PROPERTY( QString Phone READ getPhone WRITE setPhone);
    Q_PROPERTY( QDate DateEstablished
                READ getDateEstablished
                WRITE setDateEstablished );
    Q_PROPERTY( CustPropsType Type READ getType WRITE setType );
    Q_ENUMS( CustPropsType ) ; /* special macro to generate string-to-enum 
        conversion functions */

  public:
    enum CustPropsType
    { Corporate, Individual, Educational, Government }; /* The enum type 
        definition must be in the same class definition as the Q_ENUMS macro. */

    CustProps(QObject *parent = 0, const QString name = QString());

    QString getId() const {
        return m_Id;
    }
//end
    QString getName() const {
        return m_Name;
    }
    QString getAddress() const {
        return m_Address;
    }
    QString getPhone() const {
        return m_Phone;
    }
    QDate getDateEstablished() const {
        return m_Date;
    }
//start
    CustPropsType getType() const {
        return m_Type;
    }
    
    QString getTypeString() const;
    void setId(const QString &newId);
//end
    void setName(const QString &newName);
    void setAddress(const QString &newAddress);
    void setPhone(const QString &newPhone);
    void setDateEstablished(const QDate & newDate);
//start
    // Overloaded, so we can set the type 2 different ways:
    void setType(CustPropsType newType);
    void setType(QString newType);
private:
    QString m_Id, m_Name, m_Address, m_Phone;
    QDate m_Date;
    CustPropsType m_Type;
};
//end
#endif

