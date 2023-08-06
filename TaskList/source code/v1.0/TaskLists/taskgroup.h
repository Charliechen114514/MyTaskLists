#ifndef TASKGROUP_H
#define TASKGROUP_H



#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QCheckBox>
#include "task.h"
#include "group.h"
class TaskGroup : public QWidget
{
    Q_OBJECT
public:
    explicit TaskGroup(QWidget *parent = nullptr);// 1
    explicit TaskGroup(Group& group, QList<Task*>& taskList,QWidget *parent = nullptr); // 1
    explicit TaskGroup(const TaskGroup& copy,QWidget *parent = nullptr);
    void                     addTask(Task& task); // 1
    void                     addTask(QString taskName);// 1
    void                     addTask(const char* taskName);// 1
    // queryMainWindowOne is in mainWindow section
    void                     showTask();
    // remove item
    void                     removeTask(int removeIndex);

    // setTaskFinished
    void                     setFinished(QAbstractButton* btn, bool flag);

    int                      getTaskFontSize()                      {return taskFontSize;}
    void                     setTaskFontSize(int taskFontSize);
    QColor                   getFontColor()                         {return colorOfFont;};
    void                     setFontColor(const QColor color);
    // public space
    QList<QCheckBox*>*       getTaskButtonList()                    {return &taskGroupButtons;}
    QList<Task*>*            getTaskList()                          {return &taskData;}
    QButtonGroup*                       taskGroup;
    QList<QCheckBox*>                   taskGroupButtons;
signals:
    void                     signalTaskFull();

private:

    QList<Task*>                        taskData;
    Group                               thisGroup;
    QList<int>                          removeIndex;

    // font Related:
    QColor                              colorOfFont;
    int                                 taskFontSize;
};

#endif // TASKGROUP_H
