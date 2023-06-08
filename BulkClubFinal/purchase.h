#ifndef PURCHASE
#define PURCHASE
#include <QString>

class purchase
{
private:
    QString purchaseDate;
    int memberID;
    QString itemName;
    double itemPrice;
    int quantity;

public:
    purchase(const QString& _purchaseDate, int _memberID, const QString& _itemName, double _itemPrice, int _quantity);
    QString getPurchaseDate() const;
    int getMemID() const;
    QString getItemName() const;
    double getItemPrice() const;
    int getQuantity() const;
};

#endif
