#include "mainwindow.h"
#include "qpushbutton.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QSpacerItem>
#include <QMessageBox>
#include <QTextStream>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QString& role, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1400, 600);
    readPurchaseFile("C:/Users/houri/OneDrive/Desktop/BulkClubFinal/day1.txt", test.getPList());
    readPurchaseFile("C:/Users/houri/OneDrive/Desktop/BulkClubFinal/day2.txt", test.getPList());
    readPurchaseFile("C:/Users/houri/OneDrive/Desktop/BulkClubFinal/day3.txt", test.getPList());
    readPurchaseFile("C:/Users/houri/OneDrive/Desktop/BulkClubFinal/day4.txt", test.getPList());
    readPurchaseFile("C:/Users/houri/OneDrive/Desktop/BulkClubFinal/day5.txt", test.getPList());
    readPurchaseFile("C:/Users/houri/OneDrive/Desktop/BulkClubFinal/day6.txt", test.getPList());
    readPurchaseFile("C:/Users/houri/OneDrive/Desktop/BulkClubFinal/day7.txt", test.getPList());

    readMemberFile("C:/Users/houri/OneDrive/Desktop/BulkClubFinal/warehouse shoppers.txt", test.getMList());

    // Create a QGridLayout
    QGridLayout* gridLayout = new QGridLayout;

    // Create a spacer item for the top
    QSpacerItem* bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(bottomSpacer, 3, 0, 1, 3);

    QSpacerItem* topSpacer = new QSpacerItem(20, 30);
    gridLayout->addItem(topSpacer, 0, 0, 1, 3);


    QLabel* Title = new QLabel();
    QFont* font = new QFont("Consolas", 25, false);

    mainRole = role;
    Title->setText("Bulk Club - " + mainRole);
    Title->setFont(*font);
    Title->setAlignment(Qt::AlignCenter);
    gridLayout->addWidget(Title, 0, 1);

    table = new MyTable;
    table2 = new MyTable2(mainRole);

    // Add the first table to the grid layout at position (1, 0)
    gridLayout->addWidget(table, 1, 0);

    // Add the second table to the grid layout at position (1, 1)
    gridLayout->addWidget(table2, 1, 1);

    // =================COMBO BOX=======================
    combo = new QComboBox;
    combo->setPlaceholderText("Filter by");
    combo->addItem("None");
    combo->addItem("By Purchase Date");
    combo->addItem("By Item Name");
    combo->addItem("By Exp Date");
    combo->addItem("By member");
    combo->addItem("By membership");
    combo->setFixedWidth(120);

    QHBoxLayout* filterHolder = new QHBoxLayout;

    // Create the filter and output box
    filter = new QLineEdit;
    filterOutput = new QTextEdit;

    filterOutput->setText(test.noFilter(*table, *table2));

    filterHolder->addWidget(filter);
    filterHolder->addWidget(combo);

    // Add the filter and output box to the filter layout
    gridLayout->addWidget(filterOutput, 2, 1);
    gridLayout->addLayout(filterHolder, 1, 3);
    filterHolder->setAlignment(Qt::AlignTop);

    // Set the right layout as the layout for the central widget
    QWidget* rightWidget = new QWidget;
    gridLayout->addWidget(rightWidget, 1, 2);
    // Set the grid layout as the layout for the central widget
    centralWidget()->setLayout(gridLayout);

    if (mainRole == "admin")
    {
        QPushButton* manageInventory = new QPushButton;
        QPushButton* addPurchase = new QPushButton;
        QPushButton* addMember = new QPushButton;
        QPushButton* deleteMember = new QPushButton;
        manageInventory->setText("Manage Inventory");
        addPurchase->setText("Add Purchase");
        addMember->setText("Add Member");
        deleteMember->setText("Delete Member");
        QHBoxLayout* adminButtons = new QHBoxLayout;
        adminButtons->addWidget(manageInventory);
        adminButtons->addWidget(addPurchase);
        adminButtons->addWidget(addMember);
        adminButtons->addWidget(deleteMember);
        gridLayout->addLayout(adminButtons, 0, 0);

        connect(manageInventory, &QPushButton::pressed, this, &MainWindow::openInventoryWindow);
        connect(addPurchase, &QPushButton::pressed, this, &MainWindow::openPurchaseWindow);
        connect(addMember, &QPushButton::pressed, this, &MainWindow::openAddWindow);
        connect(deleteMember, &QPushButton::pressed, this, &MainWindow::openDeleteWindow);
    }

    connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::handleFilterReturnPressed);
}

void MainWindow::openInventoryWindow()
{
    // Create a new window instance
    inventoryWindow = new QMainWindow;

    // Set up the window properties and contents
    inventoryWindow->setWindowTitle("Inventory");
    inventoryWindow->setFixedSize(290, 600);
    table3 = new InventoryTable;
    test.displayInventory(*table3);

    // ======== comboBox ===============

    inven = new QComboBox;
    inven->setPlaceholderText("Manage");
    inven->addItem("Add Item");
    inven->addItem("Delete Item");
    inven->addItem("Change Item Price");

    // ==================================

    // ======= LineEdit =================

    name = new QLineEdit;
    price = new QLineEdit;

    // ==================================

    QWidget* centralWidget = new QWidget(inventoryWindow);

    inventoryWindow->setCentralWidget(centralWidget);

    // Create a layout for the central widget
    QGridLayout* centralLayout = new QGridLayout(centralWidget);
    QHBoxLayout* searchBox = new QHBoxLayout;
    searchBox->addWidget(name);
    searchBox->addWidget(price);
    centralWidget->setLayout(centralLayout);

    // Add the table3 widget to the central layout
    centralLayout->addWidget(table3, 2, 0);
    centralLayout->addWidget(inven, 0, 0);
    centralLayout->addLayout(searchBox, 1, 0);

    // Show the window
    inventoryWindow->show();

    connect(inven, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::handleManageReturnPressed);
}

void MainWindow::openPurchaseWindow()
{
    // Create a new window instance
    purchaseWindow = new QMainWindow;

    // Set up the window properties and contents
    purchaseWindow->setWindowTitle("Add Purchase");
    purchaseWindow->setFixedSize(400, 100);

    QPushButton* enter = new QPushButton;
    enter->setText("Enter");

    // ======= LineEdit =================

    date = new QLineEdit;
    purchName = new QLineEdit;
    quantity = new QLineEdit;
    id = new QLineEdit;
    date->setPlaceholderText("Date");
    purchName->setPlaceholderText("Item Name");
    quantity->setPlaceholderText("Quantity");
    id->setPlaceholderText("Member ID");

    // ==================================

    QWidget* centralWidget = new QWidget(purchaseWindow);

    purchaseWindow->setCentralWidget(centralWidget);

    // Create a layout for the central widget
    QGridLayout* centralLayout = new QGridLayout(centralWidget);
    QHBoxLayout* searchBox = new QHBoxLayout;
    searchBox->addWidget(purchName);
    searchBox->addWidget(quantity);
    searchBox->addWidget(id);
    searchBox->addWidget(date);

    centralWidget->setLayout(centralLayout);
    centralLayout->addLayout(searchBox, 0, 0);
    centralLayout->addWidget(enter, 1, 0);
    purchaseWindow->show();

    connect(enter, &QPushButton::pressed, this, &MainWindow::addPurchase);
}

void MainWindow::openDeleteWindow()
{
    // Create a new window instance
    deleteWindow = new QMainWindow;

    // Set up the window properties and contents
    deleteWindow->setWindowTitle("Delete Member");
    deleteWindow->setFixedSize(400, 100);

    QPushButton* enter = new QPushButton;
    enter->setText("Enter");

    // ======= LineEdit =================

    date = new QLineEdit;
    purchName = new QLineEdit;
    quantity = new QLineEdit;
    id = new QLineEdit;
    date->setPlaceholderText("Member Name");

    // ==================================

    QWidget* centralWidget = new QWidget(deleteWindow);

    deleteWindow->setCentralWidget(centralWidget);

    // Create a layout for the central widget
    QGridLayout* centralLayout = new QGridLayout(centralWidget);
    QHBoxLayout* searchBox = new QHBoxLayout;
    searchBox->addWidget(date);

    centralWidget->setLayout(centralLayout);
    centralLayout->addLayout(searchBox, 0, 0);
    centralLayout->addWidget(enter, 1, 0);
    deleteWindow->show();

    connect(enter, &QPushButton::pressed, this, &MainWindow::deleteMember);
}

void MainWindow::openAddWindow()
{
    // Create a new window instance
    addWindow = new QMainWindow;

    // Set up the window properties and contents
    addWindow->setWindowTitle("Add Member");
    addWindow->setFixedSize(400, 100);

    QPushButton* enter = new QPushButton;
    enter->setText("Enter");

    // ======= LineEdit =================

    date = new QLineEdit;
    purchName = new QLineEdit;
    quantity = new QLineEdit;
    id = new QLineEdit;
    date->setPlaceholderText("Member Name");
    purchName->setPlaceholderText("Member ID");
    quantity->setPlaceholderText("Status");
    id->setPlaceholderText("Exp Date");

    // ==================================

    QWidget* centralWidget = new QWidget(addWindow);

    addWindow->setCentralWidget(centralWidget);

    // Create a layout for the central widget
    QGridLayout* centralLayout = new QGridLayout(centralWidget);
    QHBoxLayout* searchBox = new QHBoxLayout;
    searchBox->addWidget(date);
    searchBox->addWidget(purchName);
    searchBox->addWidget(quantity);
    searchBox->addWidget(id);

    centralWidget->setLayout(centralLayout);
    centralLayout->addLayout(searchBox, 0, 0);
    centralLayout->addWidget(enter, 1, 0);
    addWindow->show();

    connect(enter, &QPushButton::pressed, this, &MainWindow::addMember);
}

void MainWindow::deleteMember()
{
    QString _name = date->text();
    if(test.getMList().check(_name))
    {
        test.getMList().deleteMember(_name);
        table->setSortingEnabled(false);
        table2->setSortingEnabled(false);
        table->clearContents();
        table->setRowCount(0);
        table2->clearContents();
        table2->setRowCount(0);
        filterOutput->setText(test.noFilter(*table, *table2));
        QMessageBox::information(this, "Success!", "Member Deleted");
        table->setSortingEnabled(true);
        table2->setSortingEnabled(true);
        deleteWindow->close();
        return;
    }
    QMessageBox::warning(this, "Incorrect", "Not a Member");
    return;
}


void MainWindow::addMember()
{
    QString _name = date->text();
    QString _id = purchName->text();
    QString _status = quantity->text();
    QString _expDate = id->text();
    bool ok;
    int id = _id.toInt(&ok);
    table->setSortingEnabled(false);
    table2->setSortingEnabled(false);
    if(!test.getMList().check(_name) && _name.length() > 0)
    {
        if(!test.getMList().check(_id.toInt()) && _id.length() == 5 && ok == true)
        {
            if(_status == "Executive" || _status == "Regular")
            {
                if(_expDate.length() > 0)
                {
                    test.getMList().addMember(_name, _id, _status, _expDate);
                    table->clearContents();
                    table->setRowCount(0);
                    table2->clearContents();
                    table2->setRowCount(0);
                    filterOutput->setText(test.noFilter(*table, *table2));
                    QMessageBox::information(this, "Success!", "Member Added");
                    table->setSortingEnabled(true);
                    table2->setSortingEnabled(true);
                    addWindow->close();
                    return;
                }
                QMessageBox::warning(this, "Incorrect", "No Experation Date");
                table->setSortingEnabled(true);
                table2->setSortingEnabled(true);
                return;
            }
            QMessageBox::warning(this, "Incorrect", "Invalid Status");
            table->setSortingEnabled(true);
            table2->setSortingEnabled(true);
            return;
        }
        QMessageBox::warning(this, "Incorrect", "ID Taken or Invalid ID");
        table->setSortingEnabled(true);
        table2->setSortingEnabled(true);
        return;
    }
    QMessageBox::warning(this, "Incorrect", "Already a Member or No Name");
    table->setSortingEnabled(true);
    table2->setSortingEnabled(true);
    return;
}


void MainWindow::addPurchase()
{
    QString _date = date->text();
    QString _itemName = purchName->text();
    QString _quantity = quantity->text();
    QString _id = id->text();
    table->setSortingEnabled(false);
    table2->setSortingEnabled(false);
    if(!_date.isEmpty())
    {
        if(test.getPList().check(_itemName))
        {
            if(_quantity.toInt() > 0)
            {
                if(test.getMList().check(_id.toInt()))
                {
                    test.addPurchase(_date, _itemName, _quantity, _id);
                    table->clearContents();
                    table->setRowCount(0);
                    table2->clearContents();
                    table2->setRowCount(0);
                    filterOutput->setText(test.noFilter(*table, *table2));
                    table->setSortingEnabled(true);
                    table2->setSortingEnabled(true);
                    purchaseWindow->close();
                    return;
                }
                QMessageBox::warning(this, "Incorrect", "Member does not exist");
                table->setSortingEnabled(true);
                table2->setSortingEnabled(true);
                return;
            }
            QMessageBox::warning(this, "Incorrect", "Invalid Quantity");
            table->setSortingEnabled(true);
            table2->setSortingEnabled(true);
            return;
        }
        QMessageBox::warning(this, "Incorrect", "Item does not exist");
        table->setSortingEnabled(true);
        table2->setSortingEnabled(true);
        return;
    }
    QMessageBox::warning(this, "Incorrect", "Invalid Date");
    table->setSortingEnabled(true);
    table2->setSortingEnabled(true);
    return;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleFilterReturnPressed()
{
    const int index = combo->currentIndex();
    handleMenuSelection(index);
}

void MainWindow::handleManageReturnPressed()
{
    const int index = inven->currentIndex();
    handleManageSelection(index);
}

void MainWindow::handleManageSelection(const int index)
{
    QPalette palette = filter->palette();
    switch (index)
    {
    case 0:
        name->clear();
        price->clear();
        name->setPlaceholderText("Item Name");
        price->setPlaceholderText("Item Price");
        palette.setColor(QPalette::Base, Qt::white);
        palette.setColor(QPalette::Text, Qt::black);
        price->setPalette(palette);
        price->setReadOnly(false);
        connect(price, &QLineEdit::returnPressed, this, &MainWindow::addItem);

        break;
    case 1:
        name->clear();
        price->clear();
        name->setPlaceholderText("Item Name");
        price->setPlaceholderText("Item Price");
        palette.setColor(QPalette::Base, Qt::lightGray);
        palette.setColor(QPalette::Text, Qt::gray);
        price->setPalette(palette);
        price->setReadOnly(true);
        connect(name, &QLineEdit::returnPressed, this, &MainWindow::removeItem);
        break;
    case 2:
        // Set up the line edit for item name filtering
        name->clear();
        price->clear();
        name->setPlaceholderText("Item Name");
        price->setPlaceholderText("Leave Empty");
        palette.setColor(QPalette::Base, Qt::white);
        palette.setColor(QPalette::Text, Qt::black);
        price->setPalette(palette);
        price->setReadOnly(false);
        connect(price, &QLineEdit::returnPressed, this, &MainWindow::changeItemPrice);
        break;
    default: ;
    }
}

void MainWindow::addItem()
{
    QString itemName = name->text();
    QString itemPrice = price->text();
    table3->setSortingEnabled(false);
    if(!itemName.isEmpty())
    {
        if(!test.getPList().check(itemName))
        {
            if(itemPrice.toDouble() > 0)
            {
                test.getPList().addItem(itemName, itemPrice.toDouble());
                table3->clearContents();
                table3->setRowCount(0);
                test.displayInventory(* table3);
                QMessageBox::information(this, "Success!", "Item Added");
                table3->setSortingEnabled(true);
                inventoryWindow->close();
                return;
            }
        }
    }
    table3->setSortingEnabled(true);
    inventoryWindow->close();
    QMessageBox::warning(this, "Incorrect format", "Invalid Name or Price");
}

void MainWindow::removeItem()
{
    QString itemName = name->text();
    table3->setSortingEnabled(false);
    if(test.getPList().check(itemName))
    {
        test.deleteItem(itemName);
        table3->clearContents();
        table3->setRowCount(0);
        test.displayInventory(* table3);
        QMessageBox::information(this, "Success!", "Item Removed");
        table3->setSortingEnabled(true);
        inventoryWindow->close();
        return;
    }
    QMessageBox::warning(this, "Incorrect", "Item does not Exist");
    inventoryWindow->close();
    table3->setSortingEnabled(true);
}

void MainWindow::changeItemPrice()
{
    QString itemName = name->text();
    QString itemPrice = price->text();
    table3->setSortingEnabled(false);
    if(!itemName.isEmpty())
    {
        if(test.getPList().check(itemName))
        {
            if(itemPrice.toDouble() > 0)
            {
                test.getPList().changePrice(itemName, itemPrice.toDouble());
                table3->clearContents();
                table3->setRowCount(0);
                test.displayInventory(* table3);
                QMessageBox::information(this, "Success!", "Item Price Changed");
                table3->setSortingEnabled(true);
                inventoryWindow->close();
                return;
            }
        }
    }
    QMessageBox::warning(this, "Incorrect", "Item does not Exist or Price is Incorrect");
    inventoryWindow->close();
    table3->setSortingEnabled(true);
}

/*
void MainWindow::addMember()
{
    QString memberName = name->text();
    QString memberId = price->text();
    QString memberExp =
    if(!memberName.isEmpty())
    {
        if(test.getMList().check(memberName) && test.getMList().check(memberId.toInt()))
        {

            test.getMList().addMember(memberName, memberId);
            table3->clearContents();
            table3->setRowCount(0);
            test.displayInventory(* table3);
            return;
        }
    }
    QMessageBox::warning(this, "Incorrect", "Item does not Exist or Price is Incorrect");
}
*/

bool MainWindow::readMemberFile(const QString& filename, memberList& data)
{
    QFile myFile(filename);

    if (!myFile.open(QIODevice::ReadOnly))
    {
        // Handle file open error

        return false;
    }

    QTextStream stream(&myFile);


    while (!stream.atEnd())
    {
        QString name = stream.readLine();
        QString id = stream.readLine();
        QString executive = stream.readLine();
        QString expDate = stream.readLine();

        data.addMember(name, id, executive, expDate);
    }


    myFile.close();

    return true;
}

bool MainWindow::readPurchaseFile(const QString& filename, purchaseList& data)
{
    QFile myFile(filename);

    if (!myFile.open(QIODevice::ReadOnly))
    {
        // Handle file open error

        return false;
    }

    QTextStream stream(&myFile);


    while (!stream.atEnd())
    {
        QString purchaseDate = stream.readLine();
        QString id = stream.readLine();
        QString itemName = stream.readLine();
        QString itemPrice = stream.readLine();
        QString quantity = stream.readLine();

        data.addPurchase(purchaseDate, id, itemName, itemPrice, quantity);
        data.addItem(itemName, itemPrice.toDouble());
    }


    myFile.close();

    return true;
}

void MainWindow::handleMenuSelection(const int index)
{
    QPalette palette = filter->palette();
    switch (index)
    {
    case 0:
        filter->clear();
        filterOutput->clear();
        palette.setColor(QPalette::Base, Qt::lightGray);
        palette.setColor(QPalette::Text, Qt::gray);
        filter->setPalette(palette);
        filter->setReadOnly(true);
        filter->setPlaceholderText("No filter selected");
        noFilter();
        break;

    case 1:
        // Set up the line edit for date filtering
        filter->clear();
        filterOutput->clear();
        palette.setColor(QPalette::Base, Qt::white);
        palette.setColor(QPalette::Text, Qt::black);
        filter->setPalette(palette);
        filter->setReadOnly(false);
        filter->setPlaceholderText("Enter a purchase date");
        connect(filter, &QLineEdit::returnPressed, this, &MainWindow::applyDateFilter);
        break;
    case 2:
        // Set up the line edit for item name filtering
        filter->clear();
        filterOutput->clear();
        palette.setColor(QPalette::Base, Qt::white);
        palette.setColor(QPalette::Text, Qt::black);
        filter->setPalette(palette);
        filter->setReadOnly(false);
        filter->setPlaceholderText("Enter an item name");
        connect(filter, &QLineEdit::returnPressed, this, &MainWindow::applyItemNameFilter);
        break;
    case 3:
        // Set up the line edit for item name filtering
        filter->clear();
        filterOutput->clear();
        palette.setColor(QPalette::Base, Qt::white);
        palette.setColor(QPalette::Text, Qt::black);
        filter->setPalette(palette);
        filter->setReadOnly(false);
        filter->setPlaceholderText("Enter an Expiration Date");
        connect(filter, &QLineEdit::returnPressed, this, &MainWindow::applyExpDateFilter);
        break;
    case 4:
        // Set up the line edit for item name filtering
        filter->clear();
        filterOutput->clear();
        palette.setColor(QPalette::Base, Qt::white);
        palette.setColor(QPalette::Text, Qt::black);
        filter->setPalette(palette);
        filter->setReadOnly(false);
        filter->setPlaceholderText("Enter Member id/name");
        connect(filter, &QLineEdit::returnPressed, this, &MainWindow::applyMemberFilter);
        break;
    case 5:
        // Set up the line edit for item name filtering
        filter->clear();
        filterOutput->clear();
        palette.setColor(QPalette::Base, Qt::white);
        palette.setColor(QPalette::Text, Qt::black);
        filter->setPalette(palette);
        filter->setReadOnly(false);
        filter->setPlaceholderText("Enter Membership");
        connect(filter, &QLineEdit::returnPressed, this, &MainWindow::applyMembershipFilter);
        break;
    default: ;
    }
}

void MainWindow::noFilter()
{
    table->setSortingEnabled(false);
    table2->setSortingEnabled(false);
    filterOutput->setText(test.noFilter(*table, *table2));
    table->setSortingEnabled(true);
    table2->setSortingEnabled(true);
}

void MainWindow::applyDateFilter()
{
    QString filterText = filter->text();
    if (filterText.isEmpty())
    {
        // Empty filter text, handle accordingly (e.g., show no results)
        return;
    }
    table->setSortingEnabled(false);
    table2->setSortingEnabled(false);
    // Apply the date filter using the entered text
    filterOutput->setText(test.filterByDate(filterText, *table, *table2));
    table->setSortingEnabled(true);
    table2->setSortingEnabled(true);
}

void MainWindow::applyItemNameFilter()
{
    QString filterText = filter->text();

    if (filterText.isEmpty())
    {
        // Empty filter text, handle accordingly (e.g., show no results)
        filterOutput->setText("Nothing");
        return;
    }

    table->setSortingEnabled(false);
    table2->setSortingEnabled(false);
    // Apply the item name filter using the entered text
    filterOutput->setText(test.filterItemName(filterText, *table, *table2));
    table->setSortingEnabled(true);
    table2->setSortingEnabled(true);
}

void MainWindow::applyExpDateFilter()
{
    QString filterText = filter->text();
    if (filterText.isEmpty())
    {
        // Empty filter text, handle accordingly (e.g., show no results)
        return;
    }
    table->setSortingEnabled(false);
    table2->setSortingEnabled(false);

    // Apply the date filter using the entered text
    filterOutput->setText(test.filterByExpDate(filterText, *table, *table2));
    table->setSortingEnabled(true);
    table2->setSortingEnabled(true);
}

void MainWindow::applyMemberFilter()
{
    QString filterText = filter->text();
    if (filterText.isEmpty())
    {
        // Empty filter text, handle accordingly (e.g., show no results)
        return;
    }
    table->setSortingEnabled(false);
    table2->setSortingEnabled(false);
    // Apply the date filter using the entered text
    filterOutput->setText(test.filterMemberName(filterText, *table, *table2));
    table->setSortingEnabled(true);
    table2->setSortingEnabled(true);
}

void MainWindow::applyMembershipFilter()
{
    QString filterText = filter->text();
    if (filterText.isEmpty())
    {
        // Empty filter text, handle accordingly (e.g., show no results)
        return;
    }
    table->setSortingEnabled(false);
    table2->setSortingEnabled(false);
    // Apply the date filter using the entered text
    filterOutput->setText(test.filterByStatus(filterText, *table, *table2));
    table->setSortingEnabled(true);
    table2->setSortingEnabled(true);
}
