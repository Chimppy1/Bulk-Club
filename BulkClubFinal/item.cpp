#include "item.h"
#include <QString>

item::item(QString& _name, double _price)
{
    name = _name;
    price = _price;
}

void item::setName(QString& _name)
{
    name = _name;
}

void item::setPrice(double _price)
{
    price = _price;
}

QString item::getName()
{
    return name;
}

double item::getPrice()
{
    return price;
}
