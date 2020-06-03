#include "customer.h"

    QString Customer::getFavoriteFood() const {
        return m_FavoriteFood;
    }

    QString Customer::getState() const {
        return m_State;
    }

    QString Customer::getZip() const {
        return m_Zip;
    }

    QString Customer::getFavoriteDrink() const {
        return m_FavoriteDrink;
    }

    void Customer::setFavoriteFood(QString ff) {
        m_FavoriteFood = ff;
    }

    void Customer::setState(QString state) {
        m_State = state;
    }

    void Customer::setZip(QString zip) {
        m_Zip = zip;
    }

    void Customer::setFavoriteDrink(QString fd) {
        m_FavoriteDrink = fd;
    }

