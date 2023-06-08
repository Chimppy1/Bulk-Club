#include "purchase.h"

purchase::purchase(const QString& _purchaseDate, const int _memberID, const QString& _itemName, const double _itemPrice, const int _quantity)
{
    purchaseDate = _purchaseDate;
    memberID = _memberID;
    itemName = _itemName;
    itemPrice = _itemPrice;
    quantity = _quantity;
}

QString purchase::getPurchaseDate() const
{
    return purchaseDate;
}

int purchase::getMemID() const
{
    return memberID;
}

QString purchase::getItemName() const
{
    return itemName;
}

double purchase::getItemPrice() const
{
    return itemPrice;
}

int purchase::getQuantity() const
{
    return quantity;
}
