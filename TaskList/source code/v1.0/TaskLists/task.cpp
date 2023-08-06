#include "task.h"

Task::Task()
{
    groupIndex  =  0;
    taskIndex   =  0;
    taskText    =  "";
}


Task::Task(Index taskIndex, Index groupIndex, QString taskText)
{
    this->groupIndex    = groupIndex;
    this->taskIndex     = taskIndex;
    this->taskText      = taskText;
}


