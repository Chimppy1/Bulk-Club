#include "memberList.h"
#include <QDebug>

memberList::memberList()
{
    mList = {};
}

void memberList::addMember(const QString& name, const QString& memberID, const QString& executive, const QString& date)
{
    const int memID = memberID.toInt();
    mList.sort([](const member& a, const member& b)
               {
                   return a.getMemID() < b.getMemID();
               });
    const member tmp(name, memID, executive, date);
    mList.push_back(tmp);
}

std::list<member> memberList::getMList() const
{
    return mList;
}

QString memberList::fromID(const int id)
{
    for (auto& m : mList)
    {
        if (m.getMemID() == id)
        {
            return m.getName();
        }
    }
    return "";
}

bool memberList::check(int id)
{
    for(auto m : mList)
    {
        if(m.getMemID() == id)
        {
            return true;
        }
    }
    return false;
}

bool memberList::check(QString name)
{
    for(auto m : mList)
    {
        if(m.getName() == name)
        {
            return true;
        }
    }
    return false;
}

void memberList::deleteMember(QString memberName)
{
    auto iter = mList.begin();
    while (iter != mList.end()) {
        if (iter->getName() == memberName) {
            // Erase the item from the list
            iter = mList.erase(iter);
        } else {
            // Move to the next item
            ++iter;
        }
    }
}
