#ifndef MEMBER_LIST
#define MEMBER_LIST
#include "member.h"
#include <QString>
#include <list>

class memberList
{
private:
    std::list<member> mList{};

public:
    memberList();
    void addMember(const QString& name, const QString& memberID, const QString& executive, const QString& date);
    std::list<member> getMList() const;
    QString fromID(int id);
    bool check(int id);
    bool check(QString name);
    void deleteMember(QString memberName);
};

#endif
