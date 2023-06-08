#ifndef DISPLAY_BOARD
#define DISPLAY_BOARD
#include "memberList.h"
#include "mytable.h"
#include "mytable2.h"
#include "purchaseList.h"
#include "inventoryTable.h"
#include <QString>
#include <vector>

class displayBoard
{
private:
    const double taxRate = 0.0775;
    memberList members;
    purchaseList purchases;

    double gTotal;

public:
    displayBoard();
    void clearTables(MyTable& table, MyTable2& table2);
    bool unique(const std::vector<int>& id, int check);
    bool unique(const std::vector<QString>& name, const QString& check);
    void calculateMembers(std::map<int, double>& memberTotals, MyTable2& table2);
    void calculatePurchases(std::map<QString, double>& purchaseTotals, MyTable& table);
    QString outputMemberCounts(const int executive, const int regular, const double totalRev);
    purchaseList& getPList();
    memberList& getMList();
    QString filterByDate(const QString& date, MyTable& table, MyTable2& table2);
    QString filterByExpDate(const QString& date, MyTable& table, MyTable2& table2);
    QString filterByStatus(const QString& exec, MyTable& table, MyTable2& table2);
    QString noFilter(MyTable& table, MyTable2& table2);
    QString filterItemName(const QString& name, MyTable& table, MyTable2& table2);
    QString filterMemberName(const QString& name, MyTable& table, MyTable2& table2);
    void addItem(QString& name, double price);
    void changePrice(QString& name, double price);
    void addPurchase(QString& date, QString& itemName, QString& quantity, QString& id);
    void deleteItem(QString& name);
    QString displayInventory(InventoryTable& table);
};

#endif
