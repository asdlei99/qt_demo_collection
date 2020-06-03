#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <QObject>
#include <QDate>
//start
class Customer : public QObject {
    Q_OBJECT
  public:
    Q_PROPERTY( QString Name READ objectName WRITE setObjectName );
    Q_PROPERTY( QDate Date READ getDate WRITE setDate );
    Q_PROPERTY( int LuckyNumber READ getLuckyNumber 
                WRITE setLuckyNumber );
    Q_PROPERTY( QString State READ getState WRITE setState );
    Q_PROPERTY( QString Zip READ getZip WRITE setZip );
    Q_PROPERTY( QString FavoriteFood READ getFavoriteFood 
                WRITE setFavoriteFood );
    Q_PROPERTY( QString FavoriteDrink READ getFavoriteDrink 
                WRITE setFavoriteDrink);
    
    // typical setters and getters
    //end
    QString getFavoriteFood() const ;
    QString getState() const;
    QString getZip() const ;
    QString getFavoriteDrink() const ;
    QDate getDate() const {
        return m_Date;
    }
    int getLuckyNumber() const {
        return m_LuckyNumber;
    }
    
  public slots:
    void setFavoriteFood(QString ff);
    void setState(QString state);
    void setZip(QString zip);
    void setFavoriteDrink(QString fd) ;
    void setDate(QDate d) {
        m_Date =d;
    }
    void setLuckyNumber(int n) {
        m_LuckyNumber = n;
    }
    //start
  private:
    QString m_Name, m_State, m_Zip;
    QString m_FavoriteFood, m_FavoriteDrink;
    QDate m_Date;
    int m_LuckyNumber;
};
//end

#endif        //  #ifndef CUSTOMER_H

