#include<QCloseEvent>
#include "removetaskwindow.h"
#include "ui_removetaskwindow.h"
#include "Utils.h"
removeTaskWindow::removeTaskWindow(TaskGroup* group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::removeTaskWindow)
{
    this->group = new TaskGroup(this);
    for(unsigned short i = 0; i < group->getTaskList()->size();i++)
    {
        QCheckBox* curBox = new QCheckBox(group->getTaskList()->at(i)->getTaskText(),this);
        this->group->taskGroupButtons.push_back(curBox);
        this->group->taskGroup->addButton(curBox,i);
    }

    this->group->taskGroup->setExclusive(true);
    // connect selections
    // connect(group->taskGroup,&QButtonGroup::idToggled,this,&removeTaskWindow::checkButtonAndDoList);[abolished]
}

void removeTaskWindow::showAllTasks()
{
    short CurX = CHECKBOX_X;
    short CurY = CHECKBOX_Y;
    for(int curShowIndex = 0; curShowIndex < group->taskGroupButtons.size(); curShowIndex++)
    {
        if(CurY >= this->height() - 50)
        {
            CurX += CHECKBOX_XGAP;
            CurY = CHECKBOX_Y;
        }
        group->taskGroupButtons[curShowIndex]->setGeometry(
            CurX,
            CurY,
            CHECKBOX_WIDTH,
            CHECKBOX_HEIGHT
            );
        CurY += CHECKBOX_YGAP;
        // show the button
        qDebug() << CurX << "    " << CurY;
        group->taskGroupButtons[curShowIndex]->show();
    }
}

void removeTaskWindow::checkButtonAndDoList(int index, bool status)
{
    if(status)
    {
        qDebug() << "get";
        appendToList(index);
    }
    else
    {
        qDebug() << "erase";
        removeFromList(index);
    }
}



void removeTaskWindow::removeFromList(int index)
{
    Index find = removeIndex.indexOf(index);
    removeIndex.removeAt(find);
}

void removeTaskWindow::appendToList(int taskindex)
{
    removeIndex.push_back(taskindex);
}


void removeTaskWindow::closeEvent(QCloseEvent* env[[maybe_unused]])
{

    if(!removeIndex.contains(group->taskGroup->checkedId()))
    {
        removeIndex.push_back(group->taskGroup->checkedId());
    }
    qDebug() << "removeList size:> " << removeIndex.size();
    qDebug() << "remove button ID: " << group->taskGroup->checkedId();
    emit finishEdit();
}

removeTaskWindow::~removeTaskWindow()
{
    delete ui;
}



