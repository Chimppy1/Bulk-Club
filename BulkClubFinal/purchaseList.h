#ifndef PURCHASE_LIST
#define PURCHASE_LIST
#include <QString>
#include <list>
#include "item.h"
#include "purchase.h"

class purchaseList
{
private:
    std::list<purchase> pList{};
    std::list<item> iList{};

public:
    purchaseList();
    void addPurchase(const QString& purchaseDate, const QString& memberID, const QString& itemName, const QString& itemPrice, const QString& quantity);
    void addItem(QString& itemName, double price);
    std::list<purchase> getPList() const;
    std::list<item> getIList() const;
    bool check(QString& itemName);
    void deleteItem(QString& itemName);
    void changePrice(QString& itemName, double price);
};
#endif
