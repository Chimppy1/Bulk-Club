#ifndef MEMBER_H
#define MEMBER_H

#include <QString>

class member
{
private:
    QString name{};
    int memberID;
    bool executive;
    QString expDate{};
    double rebate;
    double totalSpent;
    int renew;
    bool strToBool(const QString& executive);

public:
    member(const QString& _name, int _memberID, const QString& _executive, const QString& _expDate);
    QString getName() const;
    QString boolToStr() const;
    int getMemID() const;
    bool ifExecutive() const;
    QString getExpDate() const;
    double getRebate();
    double getTotalSpent() const;
    void addRebate(double add);
    void addTotalSpent(double add);
    void setTotalSpent(double spent);
    int getRenew() const;
    void setRenew(int set);
};

#endif
