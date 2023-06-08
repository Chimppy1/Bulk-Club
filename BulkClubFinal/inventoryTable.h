#ifndef INVTABLE_H
#define INVTABLE_H
#include "qheaderview.h"
#include <QTableWidget>

class InventoryTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit InventoryTable(QWidget* parent = nullptr) : QTableWidget(parent)
    {
        setColumnCount(2);
        setShowGrid(true);
        counter = 0;
        setFixedWidth(270);
        setColumnWidth(0, 169);
        setColumnWidth(1, 60);


        QStringList labels;
        labels << "Item Name" << "Item Price";

        setHorizontalHeaderLabels(labels);
        setSortingEnabled(true);

        // set no edit triggers and disable horizontal scroll
        setEditTriggers(QAbstractItemView::NoEditTriggers);
        setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

        connect(horizontalHeader(), &QHeaderView::sectionClicked, this, &InventoryTable::onHeaderClicked);
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

    void addPrice(QString item)
    {
        bool ok;
        double value = item.toDouble(&ok);

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

private:
    bool ascending;
    int counter;
};

#endif // INVTABLE_H
