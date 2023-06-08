#include "displayBoard.h"
#include "inventoryTable.h"
#include "mytable2.h"
#include <QDebug>
#include <QLabel>
#include <QString>
#include <QVector>
#include <algorithm>

void displayBoard::clearTables(MyTable& table, MyTable2& table2)
{
    table.clearContents();
    table.setRowCount(0);
    table2.clearContents();
    table2.setRowCount(0);
}

QString displayBoard::outputMemberCounts(const int executive, const int regular, const double totalRev)
{
    QString output;
    output += "Executive members: " + QString::number(executive) + "\n";
    output += "Regular members: " + QString::number(regular) + "\n";
    const double afterTax = totalRev + (totalRev * taxRate);
    QString taxes = QString::number(afterTax, 'f', 2);
    output += "Total Revenue: $" + taxes + "\n";
    return output;
}

void displayBoard::calculateMembers(std::map<int, double>& memberTotals, MyTable2& table2)
{
    for (auto m : members.getMList())
    {
        if (memberTotals.find(m.getMemID()) != memberTotals.end())
        {
            table2.addMemberName(m.getName());
            table2.addMemberID(QString::number(m.getMemID()));
            table2.addMemberStatus(m.boolToStr());
            table2.addMemberExpDate(m.getExpDate());
            m.setTotalSpent(memberTotals[m.getMemID()]);
            table2.addMemberTotalSpent(QString::number(memberTotals[m.getMemID()]));
            if (m.ifExecutive())
            {
                QString rebate = QString::number(m.getRebate(), 'f', 2);
                table2.addMemberRebate(rebate);
            }

            table2.addMemberRenewal(QString::number(m.getRenew()));
        }
    }
}

void displayBoard::calculatePurchases(std::map<QString, double>& purchaseTotals, MyTable& table)
{
    std::vector<QString> idHolder;
    for (auto& p : purchases.getPList())
    {
        if (unique(idHolder, p.getItemName()))
        {
            idHolder.push_back(p.getItemName());
            if (purchaseTotals[p.getItemName()])
            {
                table.addItemName(p.getItemName());
                table.addQuantity(QString::number(purchaseTotals[p.getItemName()]));
                table.addRevenue(QString::number(p.getItemPrice() * purchaseTotals[p.getItemName()]));
            }
        }
    }
}

displayBoard::displayBoard()
{
    members = {};
    purchases = {};
}

purchaseList& displayBoard::getPList()
{
    return purchases;
}

memberList& displayBoard::getMList()
{
    return members;
}

bool displayBoard::unique(const std::vector<int>& id, const int check)
{
    return std::all_of(id.begin(), id.end(), [check](const int i) { return i != check; });
}

bool displayBoard::unique(const std::vector<QString>& name, const QString& check)
{
    return std::all_of(name.begin(), name.end(), [check](const QString& names) { return names != check; });
}

QString displayBoard::filterByDate(const QString& date, MyTable& table, MyTable2& table2)
{
    clearTables(table, table2);
    double totalRev = 0.00;
    int executive = 0;
    int regular = 0;
    std::map<int, double> memberTotals;
    std::map<QString, double> purchaseTotals;
    for (const auto& m : purchases.getPList())
    {
        if (m.getPurchaseDate() == date)
        {
            for (auto& p : members.getMList())
            {
                if (m.getMemID() == p.getMemID())
                {
                    // calculate total cost of this purchase
                    double totalCost = m.getItemPrice() * m.getQuantity();

                    // if this member has made a purchase before, add to their total
                    if (memberTotals.count(p.getMemID()) > 0)
                    {
                        memberTotals[p.getMemID()] += totalCost;
                    }
                    else // otherwise, start a new total for this member
                    {
                        memberTotals[p.getMemID()] = totalCost;
                    }
                    if (p.ifExecutive())
                    {
                        executive++;
                    }
                    else
                    {
                        regular++;
                    }
                }
            }
            double totalCostP = m.getQuantity();
            if (purchaseTotals[m.getItemName()] > 0)
            {
                purchaseTotals[m.getItemName()] += totalCostP;
            }
            else // otherwise, start a new total for this member
            {
                purchaseTotals[m.getItemName()] = totalCostP;
            }

            totalRev += m.getItemPrice() * m.getQuantity();
        }
    }

    calculateMembers(memberTotals, table2);
    calculatePurchases(purchaseTotals, table);

    return outputMemberCounts(executive, regular, totalRev);
}

QString displayBoard::filterByExpDate(const QString& date, MyTable& table, MyTable2& table2)
{
    clearTables(table, table2);
    QString output;
    int executive = 0;
    int regular = 0;

    for (const auto& m : members.getMList())
    {
        if (m.getExpDate() == date)
        {
            if (m.ifExecutive())
            {
                executive++;
            }
            else
            {
                regular++;
            }
            table2.addMemberName(m.getName());
            table2.addMemberID(QString::number(m.getMemID()));
            table2.addMemberStatus(m.boolToStr());
            table2.addMemberExpDate(m.getExpDate());
        }
    }
    output += "Executive members: " + QString::number(executive) + "\n";

    output += "Regular members: " + QString::number(regular) + "\n";

    return output;
}

QString displayBoard::filterByStatus(const QString& executive, MyTable& table, MyTable2& table2)
{
    clearTables(table, table2);
    bool filter;
    double totalRev = 0.00;
    int exec = 0;
    int regular = 0;
    double totalCostP = 0;
    std::vector<int> idHolder;
    std::map<int, double> memberTotals;
    std::map<QString, double> purchaseTotals;

    if (executive == "Executive")
    {
        filter = true;
    }
    else if (executive == "Regular")
    {
        filter = false;
    }
    else
        return "";

    for (auto& m : members.getMList())
    {
        if (m.ifExecutive() == filter)
        {
            if (memberTotals.find(m.getMemID()) == memberTotals.end())
            {
                // The key does not exist in the map.
                memberTotals[m.getMemID()] = 0;
            }
            if (unique(idHolder, m.getMemID()))
            {
                if (m.ifExecutive())
                {
                    exec++;
                }
                else
                {
                    regular++;
                }
                idHolder.push_back(m.getMemID());
            };

            for (auto& p : purchases.getPList())
            {
                if (purchaseTotals[p.getItemName()] > 0)
                {
                    purchaseTotals[p.getItemName()] += totalCostP;
                }
                else // otherwise, start a new total for this member
                {
                    purchaseTotals[p.getItemName()] = totalCostP;
                }
                if (p.getMemID() == m.getMemID())
                {
                    double totalCost = p.getQuantity() * p.getItemPrice();
                    if (memberTotals[m.getMemID()] > 0)
                    {
                        memberTotals[m.getMemID()] += totalCost;
                    }
                    else // otherwise, start a new total for this member
                    {
                        memberTotals[m.getMemID()] = totalCost;
                    }
                    totalRev += (p.getItemPrice() * p.getQuantity());
                }
                totalRev += (p.getItemPrice() * p.getQuantity());
            }
        }
    }

    calculateMembers(memberTotals, table2);
    calculatePurchases(purchaseTotals, table);
    return outputMemberCounts(exec, regular, totalRev);
}

QString displayBoard::noFilter(MyTable& table, MyTable2& table2)
{
    clearTables(table, table2);
    double totalRev = 0.00;
    int executive = 0;
    int regular = 0;
    std::vector<int> idHolder;
    std::map<int, double> memberTotals;
    std::map<QString, double> purchaseTotals;

    for (auto& p : purchases.getPList())
    {
        double totalCostP = p.getQuantity();

        if (purchaseTotals[p.getItemName()] > 0)
        {
            purchaseTotals[p.getItemName()] += totalCostP;
        }
        else // otherwise, start a new total for this member
        {
            purchaseTotals[p.getItemName()] = totalCostP;
        }

        totalRev += (p.getItemPrice() * p.getQuantity());

        for (auto& m : members.getMList())
        {
            if (memberTotals.find(m.getMemID()) == memberTotals.end())
            {
                // The key does not exist in the map.
                memberTotals[m.getMemID()] = 0;
            }
            if (p.getMemID() == m.getMemID())
            {
                double totalCost = p.getQuantity() * p.getItemPrice();
                if (memberTotals[m.getMemID()] > 0)
                {
                    memberTotals[m.getMemID()] += totalCost;
                }
                else // otherwise, start a new total for this member
                {
                    memberTotals[m.getMemID()] = totalCost;
                }
            }
            if (unique(idHolder, m.getMemID()))
            {
                if (m.ifExecutive())
                {
                    executive++;
                }
                else
                {
                    regular++;
                }
                idHolder.push_back(m.getMemID());
            };
        }
    }

    calculateMembers(memberTotals, table2);
    calculatePurchases(purchaseTotals, table);

    return outputMemberCounts(executive, regular, totalRev);
}

QString displayBoard::filterItemName(const QString& name, MyTable& table, MyTable2& table2)
{
    clearTables(table, table2);
    double totalRev = 0.00;
    int executive = 0;
    int regular = 0;
    std::vector<int> idHolder;
    std::map<int, double> memberTotals;
    std::map<QString, double> purchaseTotals;

    for (auto& p : purchases.getPList())
    {
        if (p.getItemName() == name)
        {
            for (auto& m : members.getMList())
            {
                if (p.getMemID() == m.getMemID())
                {
                    if (unique(idHolder, p.getMemID()))
                    {
                        if (m.ifExecutive())
                        {
                            executive++;
                        }
                        else
                        {
                            regular++;
                        }
                        idHolder.push_back(p.getMemID());
                    };
                    double totalCost = p.getItemPrice() * p.getQuantity();

                    if (memberTotals[m.getMemID()] > 0)
                    {
                        memberTotals[m.getMemID()] += totalCost;
                    }
                    else // otherwise, start a new total for this member
                    {
                        memberTotals[m.getMemID()] = totalCost;
                    }
                    totalRev += (p.getItemPrice() * p.getQuantity());
                }
            }
            double totalCostP = p.getQuantity();
            if (purchaseTotals[p.getItemName()] > 0)
            {
                purchaseTotals[p.getItemName()] += totalCostP;
            }
            else // otherwise, start a new total for this member
            {
                purchaseTotals[p.getItemName()] = totalCostP;
            }
        }
    }

    calculateMembers(memberTotals, table2);
    calculatePurchases(purchaseTotals, table);

    return outputMemberCounts(executive, regular, totalRev);
}

QString displayBoard::filterMemberName(const QString& name, MyTable& table, MyTable2& table2)
{
    clearTables(table, table2);
    double totalRev = 0.00;
    int executive = 0;
    int regular = 0;
    double totalCost = 0;
    std::map<int, double> memberTotals;
    std::map<QString, double> purchaseTotals;

    for (auto& m : members.getMList())
    {
        if (m.getName() == name || QString::number(m.getMemID()) == name)
        {
            if (m.ifExecutive())
            {
                executive++;
            }
            else
            {
                regular++;
            }

            for (auto& p : purchases.getPList())
            {
                if (m.getMemID() == p.getMemID())
                {
                    totalCost += p.getItemPrice() * p.getQuantity();

                    memberTotals[p.getMemID()] = totalCost;

                    double totalCostP = p.getQuantity();
                    if (purchaseTotals[p.getItemName()] > 0)
                    {
                        purchaseTotals[p.getItemName()] += totalCostP;
                    }
                    else // otherwise, start a new total for this member
                    {
                        purchaseTotals[p.getItemName()] = totalCostP;
                    }

                    totalRev += (p.getItemPrice() * p.getQuantity());
                }
            }
            break;
        }
    }

    calculateMembers(memberTotals, table2);
    calculatePurchases(purchaseTotals, table);

    return outputMemberCounts(executive, regular, totalRev);
}

// ========== ADMIN ONLY ==================================

void displayBoard::addItem(QString& name, double price)
{
    purchases.addItem(name, price);
}

void displayBoard::changePrice(QString& name, double price)
{
    for(auto i : purchases.getIList())
    {
        if(name == i.getName())
        {
            i.setPrice(price);
            break;
        }
    }
}
void displayBoard::addPurchase(QString& date, QString& itemName, QString& quantity, QString& id)
{
    for(auto i : purchases.getIList())
    {
        if(itemName == i.getName())
        {
            purchases.addPurchase(date, id, i.getName() , QString::number(i.getPrice()), quantity);
        }
    }
}

void displayBoard::deleteItem(QString& itemName)
{
    purchases.deleteItem(itemName);
}

QString displayBoard::displayInventory(InventoryTable& table)
{
    for(auto& i : purchases.getIList())
    {
        table.addItemName(i.getName());
        table.addPrice(QString::number(i.getPrice()));
    }
    return "";
}

// ===============================================================
