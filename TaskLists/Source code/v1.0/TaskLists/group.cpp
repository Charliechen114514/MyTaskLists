#include "group.h"

Group::Group()
{
    groupIndex = 0;
    groupName = "";
}

Group::Group(Index groupIndex, QString groupName)
{
    this->groupIndex = groupIndex;
    this->groupName = groupName;
}
