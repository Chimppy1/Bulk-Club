#ifndef MYTABLE_H
#define MYTABLE_H
#include "qheaderview.h"
#include <QTableWidget>


class MyTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit MyTable(QWidget* parent = nullptr) : QTableWidget(parent)
    {
        setColumnCount(3);
        setShowGrid(true);
        counter = 0;
        setMinimumSize(341, 400);
        setFixedWidth(370);
        setColumnWidth(0, 169);
        setColumnWidth(1, 70);
        setColumnWidth(2, 90);


        QStringList labels;
        labels << "Item Name" << "Quantity" << "Revenue";

        setHorizontalHeaderLabels(labels);
        setSortingEnabled(true);

        // set no edit triggers and disable horizontal scroll
        setEditTriggers(QAbstractItemView::NoEditTriggers);
        setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

        connect(horizontalHeader(), &QHeaderView::sectionClicked, this, &MyTable::onHeaderClicked);
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
        default: ;
        }
    }

    void addItemName(QString item)
    {
        if (counter != 0)
        {
            counter++;
        }
        insertRow(counter);
        QTableWidgetItem* newItem = new QTableWidgetItem(item);
        setItem(counter, 0, newItem);
    }

    void addQuantity(QString item)
    {
        bool ok;
        int value = item.toInt(&ok);

        QTableWidgetItem* newItem = new QTableWidgetItem();

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

    void addRevenue(QString item)
    {
        bool ok;
        double value = item.toDouble(&ok);

        if (ok)
        {
            // if the conversion to double was successful
            value = round(value * 100) / 100; // round to 2 decimal places
        }

        QTableWidgetItem* newItem = new QTableWidgetItem();
        newItem->setData(Qt::EditRole, QVariant(value));

        setItem(counter, 2, newItem);
    }

private:
    int counter;
    bool ascending;
};

#endif // MYTABLE_H
