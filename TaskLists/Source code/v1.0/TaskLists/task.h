#ifndef TASK_H
#define TASK_H
#include <QString>
#include "Utils.h"


class Task
{
public:
    // initer
    Task();
    Task(Index taskIndex, Index groupIndex, QString taskText);

    // use default copy assignment and operator= assignment

    // setter
    void setNewTaskIndex(Index taskIndex)   {this->taskIndex = taskIndex;};
    void setNewGroupIndex(Index groupIndex) {this->groupIndex = groupIndex;};
    void setNewTaskText(QString taskText)   {this->taskText = taskText;};

    // getter
    Index getTaskIndex() {return taskIndex;}
    Index getGroupIndex(){return groupIndex;}
    QString getTaskText(){return QString(taskText);}
private:

    Index       taskIndex;
    Index       groupIndex;
    QString     taskText;
};

#endif // TASK_H
