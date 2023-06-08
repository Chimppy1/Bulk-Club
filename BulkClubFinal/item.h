#ifndef ITEM_H
#define ITEM_H
#include <QString>


class item
{
private:
    QString name;
    double price;
public:
    item(QString& _name, double _price);
    void setPrice(double _price);
    void setName(QString& _name);
    QString getName();
    double getPrice();
};

#endif // ITEM_H
