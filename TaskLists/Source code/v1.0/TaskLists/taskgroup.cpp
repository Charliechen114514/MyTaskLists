#include "taskgroup.h"
#define FONTSETCONF(FONTSIZE, FONT_RED, FONT_GREEN, FONT_BLUE) \
"QCheckBox{font-size: "+ QString::number(FONTSIZE) + "px;"+ \
"color: rgb(" + QString::number(FONT_RED) +"," + QString::number(FONT_GREEN)+"," + QString::number(FONT_BLUE) + ")};"


TaskGroup::TaskGroup(QWidget *parent)
    : QWidget{parent}
{
    taskGroup = new QButtonGroup;
    taskGroup->setExclusive(false);
    taskFontSize = TASK_FONT_SIZE;
    connect(this->taskGroup,&QButtonGroup::buttonToggled,this,&TaskGroup::setFinished);
} //default NULL

TaskGroup::TaskGroup(Group& group, QList<Task*>& taskList,QWidget *parent)
        : QWidget{parent}, taskData(taskList),thisGroup(group)
{
    taskGroup = new QButtonGroup;
    taskGroup->setExclusive(false);
    taskFontSize = 20;
}

TaskGroup::TaskGroup(const TaskGroup& copy, QWidget *parent)
    : QWidget{parent}
{
    this->taskGroupButtons = copy.taskGroupButtons;
    this->taskData = copy.taskData;
    qDebug() << "in the copy assignment func: got " << this->taskData.size() << "elems";
    qDebug() << "While in copy one:" << copy.taskData.size();
}

// do not use this API directly
// only when you are sure the Index
//
void TaskGroup::addTask(Task& task)
{
    this->taskData.push_back(new Task(task));
    QCheckBox* curBox = new QCheckBox(task.getTaskText(),this);
    curBox->setMinimumSize(300,50);
    curBox->setStyleSheet(FONTSETCONF(taskFontSize,colorOfFont.red(), colorOfFont.green(),colorOfFont.blue()));
    taskGroupButtons.push_back(curBox);
    taskGroup->addButton(curBox,taskGroupButtons.size());
    showTask();
}

void TaskGroup::addTask(QString task)
{
    this->taskData.push_back
    (
        new Task
        (
            this->taskData.size() + 1, // task index
            thisGroup.getGroupIndex(), // group index
            task                       // taskText
        )
    );

    QCheckBox* curBox = new QCheckBox(QString(task),this);
    curBox->setMinimumSize(300,50);
    curBox->setStyleSheet(FONTSETCONF(taskFontSize,colorOfFont.red(), colorOfFont.green(),colorOfFont.blue()));
    curBox->setFixedSize(this->width(),50);
    taskGroupButtons.push_back(curBox);
    taskGroup->addButton(curBox,taskGroupButtons.size());
    showTask();
}

void TaskGroup::addTask(const char* task)
{
    this->taskData.push_back
    (
        new Task
        (
            this->taskData.size() + 1, // task index
            thisGroup.getGroupIndex(), // group index
            QString(task)              // taskText
        )
    );

    QCheckBox* curBox = new QCheckBox(QString(task),this);
    curBox->setMinimumSize(300,50);
    curBox->setStyleSheet(FONTSETCONF(taskFontSize,colorOfFont.red(), colorOfFont.green(),colorOfFont.blue()));
    taskGroupButtons.push_back(curBox);

    taskGroup->addButton(curBox,taskGroupButtons.size());
    showTask();
}

void TaskGroup::showTask()
{
    short CurX = CHECKBOX_X;
    short CurY = CHECKBOX_Y;
    qDebug() << "现在的taskGroupButtons Size" << taskGroupButtons.size();
    for(int curShowIndex = 0; curShowIndex < taskData.size(); curShowIndex++)
    {
        taskGroupButtons[curShowIndex]->setGeometry(
            CurX,
            CurY,
            CHECKBOX_WIDTH,
            CHECKBOX_HEIGHT
        );

        CurY += CHECKBOX_YGAP;
        // show the button
        taskGroupButtons[curShowIndex]->show();
        qDebug() << "当前ID："<< "第"<< curShowIndex + 1<< "个：>" <<  taskGroup->id(taskGroupButtons[curShowIndex]);
    }
    qDebug() << "------------------------------------------";
}

void TaskGroup::removeTask(int index)
{
    if(index == -1)
    {
        return; // not delete
    }
    // 不必删除摁扭组——只是维护关系而已
    taskGroupButtons.at(index)->deleteLater();  //为了擦除摁扭在窗口的图像
    taskGroupButtons.remove(index);
    taskData.remove(index);
    qDebug() << "当前taskData size" << taskData.size();
    showTask();
}

void TaskGroup::setTaskFontSize(int TaskFontSize)
{
    qDebug() << "in setTaskFontSize: size>>>" << TaskFontSize;
    if(TaskFontSize <= FONTSIZE_MIN || TaskFontSize >= FONTSIZE_MAX){
        return;
    }
    this->taskFontSize = TaskFontSize;
    int red = this->colorOfFont.red();
    int green = this->colorOfFont.green();
    int blue = this->colorOfFont.blue();
    qDebug() << FONTSETCONF(taskFontSize, red, green, blue);

    for(unsigned short i = 0; i < taskGroupButtons.size();i++)
    {
        taskGroupButtons[i]->setStyleSheet(FONTSETCONF(taskFontSize, red, green, blue));
        // taskGroupButtons[i]->setStyleSheet();
        // taskGroupButtons[i]->setStyleSheet("font-size: " + QString::number(taskFontSize) + "px; " + "QCheckBox{color:rgb(" + QString::number(red) + QString::number(green) + QString::number(blue) + ")}");
        // taskGroupButtons[i]->setStyleSheet("QCheckBox{color:rgb(" + QString::number(red) + QString::number(green) + QString::number(blue) + ")}");
    }
    showTask();
}

void TaskGroup::setFontColor(QColor color)
{
    this->colorOfFont = color;
    int red = this->colorOfFont.red();
    int green = this->colorOfFont.green();
    int blue = this->colorOfFont.blue();
    qDebug() << red << " " << green << " " << blue;
    qDebug() << FONTSETCONF(taskFontSize, red, green, blue);
    for(unsigned short i = 0; i < taskGroupButtons.size();i++)
    {
        taskGroupButtons[i]->setStyleSheet(FONTSETCONF(taskFontSize, red, green, blue));
//        taskGroupButtons[i]->setStyleSheet("font-size: " + QString::number(taskFontSize) + "px; " + "QCheckBox{color:rgb(" + QString::number(red) +"," + QString::number(green) +","+ QString::number(blue) + ")}");
//        taskGroupButtons[i]->setStyleSheet("font-size: " + QString::number(taskFontSize) + "px");
//        taskGroupButtons[i]->setStyleSheet("QCheckBox{color:rgb(" +
//            QString::number(red) + QString::number(green) + QString::number(blue) + ")}");
    }
    showTask();
}


void TaskGroup::setFinished(QAbstractButton* btn,bool flag)
{
    QFont setfontter = btn->font();
    setfontter.setStrikeOut(flag);
    btn->setFont(setfontter);
}












