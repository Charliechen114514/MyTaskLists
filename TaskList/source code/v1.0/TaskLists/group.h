#ifndef GROUP_H
#define GROUP_H

#include "Utils.h"
#include <QString>

class Group
{
public:
    // initer
    Group();
    Group(Index groupIndex, QString groupName);

    // use default copy assignment and operator= assignment

    // setter

    void setGroupIndex(Index groupIndex){this->groupIndex = groupIndex;}
    void setGroupName(QString groupName){this->groupName = groupName;}

    //getter
    Index getGroupIndex()   {return groupIndex;}
    QString getGroupName()  {return QString(groupName);}
private:
    Index   groupIndex;
    QString groupName;
};

#endif // GROUP_H
