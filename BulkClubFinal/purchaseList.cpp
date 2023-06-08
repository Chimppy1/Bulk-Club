#include "purchaseList.h"

purchaseList::purchaseList()
{
    pList = {};
    iList = {};
}

void purchaseList::addPurchase(const QString& purchaseDate, const QString& memberID, const QString& itemName, const QString& itemPrice, const QString& quantity)
{
    const int purchaseID = memberID.toInt();
    const double price = itemPrice.toDouble();
    const int _quantity = quantity.toInt();

    pList.sort([](const purchase& a, const purchase& b)
               {
                   return a.getItemName() < b.getItemName();
               });

    QString name = itemName;

    if (!check(name))
    {
        item tmp1(name, price);
        iList.push_back(tmp1);
    }

    const purchase tmp(purchaseDate, purchaseID, itemName, price, _quantity);
    pList.push_back(tmp);
}


std::list<item> purchaseList::getIList() const
{
    return iList;
}

void purchaseList::addItem(QString& itemName, double price)
{
    if(!check(itemName))
    {
        item tmp1(itemName, price);
        iList.push_back(tmp1);
    }
}

void purchaseList::changePrice(QString& itemName, double price)
{
    for (auto& item : iList)
    {
        if (item.getName() == itemName)
        {
            item.setPrice(price); // Item with the same name exists
        }
    }
}

void purchaseList::deleteItem(QString& itemName)
{
    // Create an iterator to traverse the item list
    auto iter = iList.begin();
    while (iter != iList.end()) {
        if (iter->getName() == itemName) {
            // Erase the item from the list
            iter = iList.erase(iter);
        } else {
            // Move to the next item
            ++iter;
        }
    }
}

std::list<purchase> purchaseList::getPList() const
{
    return pList;
}

bool purchaseList::check(QString& itemName)
{
    for (auto& item : iList)
    {
        if (item.getName() == itemName)
        {
            return true; // Item with the same name exists
        }
    }
    return false; // Item with the same name does not exist
}
