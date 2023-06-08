#include "member.h"
#include <QString>

member::member(const QString& _name, const int _memberID, const QString& _executive, const QString& _expDate)
{
    name = _name;
    memberID = _memberID;
    executive = strToBool(_executive);
    if (!executive)
    {
        constexpr double regularMember = 65;
        renew = regularMember;
    }
    else
    {
        constexpr double executiveMember = 120;
        renew = executiveMember;
    }
    expDate = _expDate;
    rebate = 0;
    totalSpent = 0;
}

bool member::strToBool(const QString& executive)
{
    return executive == "Executive";
}

QString member::getName() const
{
    return name;
}

QString member::boolToStr() const
{
    QString status = "Regular";
    if (executive)
    {
        status = "Executive";
        return status;
    }
    return status;
}

int member::getMemID() const
{
    return memberID;
}

bool member::ifExecutive() const
{
    return executive;
}

QString member::getExpDate() const
{
    return expDate;
}

double member::getRebate()
{
    if (executive)
    {
        constexpr double rebatePercentage = .02;
        rebate = totalSpent * rebatePercentage;
        return rebate;
    }
    return 0;
}

double member::getTotalSpent() const
{
    return totalSpent;
}

void member::addRebate(double add)
{
    if (executive)
    {
        constexpr double rebatePercentage = .02;
        add = add * rebatePercentage;
        rebate = rebate + add;
    }
}

void member::addTotalSpent(const double add)
{
    totalSpent = totalSpent + add;
}

void member::setTotalSpent(const double spent)
{
    totalSpent = spent;
}

int member::getRenew() const
{
    return renew;
}

void member::setRenew(const int set)
{
    renew = set;
}
