#ifndef MYTABLE2_H
#define MYTABLE2_H
#include "QDateTableWidgetItem.h"
#include "qheaderview.h"
#include <QTableWidget>


class MyTable2 : public QTableWidget
{
    Q_OBJECT
public:
    explicit MyTable2(QString role, QWidget* parent = nullptr) : QTableWidget(parent)
    {
        tableRole = role;

        setColumnCount(7);
        setShowGrid(true);
        counter = 0;
        setMinimumSize(554, 400);
        setFixedWidth(691);

        setColumnWidth(0, 160);
        setColumnWidth(1, 50);
        setColumnWidth(2, 80);
        setColumnWidth(3, 110);
        setColumnWidth(4, 90);
        setColumnWidth(5, 80);
        setColumnWidth(6, 80);

        QStringList labels;
        labels << "Name" << "ID" << "Status" << "Exp/Date" << "Total Spent" << "Rebate" << "Renewal";

        setHorizontalHeaderLabels(labels);
        setSortingEnabled(true);

        // set no edit triggers and disable horizontal scroll
        setEditTriggers(QAbstractItemView::NoEditTriggers);
        setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

        // Prevent the user from moving or resizing columns
        horizontalHeader()->setSectionsMovable(false);
        horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

        connect(horizontalHeader(), &QHeaderView::sectionClicked, this, &MyTable2::onHeaderClicked);
    }

public slots:
    void onHeaderClicked(int column)
    {
        switch (column)
        {
        case 0:
            if (ascending)
            {
                sortItems(column, Qt::AscendingOrder);
                ascending = false;
            }
            else
            {
                sortItems(column, Qt::DescendingOrder);
                ascending = true;
            }
            break;

        case 1:
            if (ascending)
            {
                sortItems(column, Qt::AscendingOrder);
                ascending = false;
            }
            else
            {
                sortItems(column, Qt::DescendingOrder);
                ascending = true;
            }
            break;

        case 2:
            if (ascending)
            {
                sortItems(column, Qt::AscendingOrder);
                ascending = false;
            }
            else
            {
                sortItems(column, Qt::DescendingOrder);
                ascending = true;
            }
            break;
        case 3:
            if (ascending)
            {
                sortItems(column, Qt::AscendingOrder);
                ascending = false;
            }
            else
            {
                sortItems(column, Qt::DescendingOrder);
                ascending = true;
            }
            break;
        case 4:
            if (ascending)
            {
                sortItems(column, Qt::AscendingOrder);
                ascending = false;
            }
            else
            {
                sortItems(column, Qt::DescendingOrder);
                ascending = true;
            }
            break;
        case 5:
            if (ascending)
            {
                sortItems(column, Qt::AscendingOrder);
                ascending = false;
            }
            else
            {
                sortItems(column, Qt::DescendingOrder);
                ascending = true;
            }
            break;
        case 6:
            if (ascending)
            {
                sortItems(column, Qt::AscendingOrder);
                ascending = false;
            }
            else
            {
                sortItems(column, Qt::DescendingOrder);
                ascending = true;
            }
            break;
        default: ;
        }
    }

    void addMemberName(QString item)
    {
        if (counter != 0)
        {
            counter++;
        }
        insertRow(counter);
        QTableWidgetItem* newItem = new QTableWidgetItem(item);
        setItem(counter, 0, newItem);
    }

    void addMemberID(QString item)
    {
        bool ok;
        int value = item.toInt(&ok);

        QTableWidgetItem* newItem = new QTableWidgetItem(item);

        if (ok)
        {
            // if the conversion to double was successful
            newItem->setData(Qt::EditRole, QVariant(value));
        }
        else
        {
            // if the conversion was not successful, fall back to treating it as a string
            newItem->setData(Qt::EditRole, QVariant(item));
        }

        setItem(counter, 1, newItem);
    }

    void addMemberStatus(QString item)
    {
        QTableWidgetItem* newItem = new QTableWidgetItem(item);

        status = item;

        setItem(counter, 2, newItem);
    }

    void addMemberExpDate(QString item)
    {
        QDate date = QDate::fromString(item, "MM/dd/yyyy");
        DateTableWidgetItem* newItem = new DateTableWidgetItem(date);
        setItem(counter, 3, newItem);;
    }

    void addMemberTotalSpent(QString item)
    {
        removeCellWidget(counter, 4);
        //bool ok;
        float value = item.toFloat();

        QTableWidgetItem* newItem = new QTableWidgetItem(item);

        newItem->setData(Qt::EditRole, QVariant(value));


        if(tableRole == "admin")
        {
            if(status == "Executive")
            {
                if(item.toDouble() < 2750)
                {
                    newItem->setToolTip("should downgrade");
                }
            }
            if(status == "Regular")
            {
                if(item.toDouble() > 2750)
                {
                    newItem->setToolTip("should upgrade");
                }
            }
        }

        setItem(counter, 4, newItem);
    }

    void addMemberRebate(QString item)
    {
        //bool ok;
        float value = item.toFloat();

        QTableWidgetItem* newItem = new QTableWidgetItem(item);

        newItem->setData(Qt::EditRole, QVariant(value));

        setItem(counter, 5, newItem);
    }

    void addMemberRenewal(QString item)
    {
        bool ok;
        int value = item.toInt(&ok);

        QTableWidgetItem* newItem = new QTableWidgetItem(item);
        if (ok)
        {
            // if the conversion to double was successful
            newItem->setData(Qt::EditRole, QVariant(value));
        }
        else
        {
            // if the conversion was not successful, fall back to treating it as a string
            newItem->setData(Qt::EditRole, QVariant(item));
        }

        setItem(counter, 6, newItem);
    }

private:
    int counter;
    bool ascending;
    QString status;
    QString tableRole;
};

#endif // MYTABLE2_H
