#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "displayBoard.h"
#include "mytable.h"
#include "mytable2.h"
#include "inventoryTable.h"
#include "qtextedit.h"
#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString& role, QWidget* parent = nullptr);
    ~MainWindow();

public slots:

private slots:

    void handleMenuSelection(int index);
    void handleManageSelection(const int index);
    void handleFilterReturnPressed();
    void handleManageReturnPressed();
    void openInventoryWindow();
    void openPurchaseWindow();
    void addPurchase();
    void openAddWindow();
    void addMember();
    void deleteMember();
    void openDeleteWindow();

private:
    Ui::MainWindow* ui{};
    QMainWindow* inventoryWindow;
    QMainWindow* purchaseWindow;
    QMainWindow* addWindow;
    QMainWindow* deleteWindow;
    displayBoard test;
    MyTable* table;
    MyTable2* table2;
    InventoryTable* table3;
    QComboBox* combo{}; // drop down menu
    QString mainRole;
    QComboBox* inven{};
    QLineEdit* name;
    QLineEdit* price;
    QLineEdit* date;
    QLineEdit* purchName;
    QLineEdit* quantity;
    QLineEdit* id;

    QLineEdit* filter{}; // enter filter info
    QTextEdit* filterOutput{}; // output box

    bool readMemberFile(const QString& filename, memberList& data);
    bool readPurchaseFile(const QString& filename, purchaseList& data);
    void noFilter();
    void applyExpDateFilter();
    void applyDateFilter();
    void applyItemNameFilter();
    void applyMemberFilter();
    void applyMembershipFilter();
    void addItem();
    void changeItemPrice();
    void removeItem();
};
#endif // MAINWINDOW_H
