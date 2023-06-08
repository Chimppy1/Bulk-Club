#ifndef QDATETABLEWIDGETITEM_H
#define QDATETABLEWIDGETITEM_H
#include <QDate>
#include <QTableWidgetItem>

class DateTableWidgetItem : public QTableWidgetItem
{
public:
    explicit DateTableWidgetItem(const QDate& date)
        : QTableWidgetItem(date.toString()), m_date(date)
    {
    }

    bool operator <(const QTableWidgetItem& other) const
    {
        const auto* otherItem = dynamic_cast<const DateTableWidgetItem*>(&other);
        if (otherItem != nullptr)
        {
            return m_date < otherItem->m_date;
        }
        return QTableWidgetItem::operator<(other);
    }

private:
    QDate m_date{};
};

#endif // QDATETABLEWIDGETITEM_H
