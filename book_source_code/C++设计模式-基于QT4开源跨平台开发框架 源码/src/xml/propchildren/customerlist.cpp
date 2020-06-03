#include "customerlist.h"
#include <QList>
#include "customer.h"
#include <QVariant>

QList<Customer*> CustomerList::getCustomers() {
   return findChildren<Customer*>(); 
}

CustomerList* CustomerList::sample() {
    CustomerList* retval = new CustomerList("Customers");
    Customer* custp = new Customer();
    custp->setProperty("Name", "Simon");
    custp->setProperty("Date", QDate(1963, 11, 22));
    custp->setProperty("State", "WA");
    custp->setZip("12345");
    custp->setProperty("LuckyNumber", 834);
    custp->setFavoriteFood("Donuts");
    custp->setProperty("FavoriteDrink", "Diet YooHoo");
    custp->setParent(retval);

    custp = new Customer();
    custp->setProperty("Name", "Raja");
    custp->setProperty("Date", QDate(1969, 6, 15));
    custp->setProperty("State", "AZ");
    custp->setProperty("Zip","54321");
    custp->setProperty("LuckyNumber", 62);
    custp->setProperty("FavoriteFood","Mushrooms");
    custp->setProperty("FavoriteDrink","Jolt");
    custp->setParent(retval);
    return retval;
}


