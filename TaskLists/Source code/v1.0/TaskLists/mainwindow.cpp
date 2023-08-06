#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    curViewIndex = 0;
    currentSubjectName = "";
    queryNewTaskWindow = new queryNewTask(this);
    queryNewTaskWindow->setWindowTitle("添加任务");
    queryOfNewTabSubjectWindow = new queryOfNewTabSubject(this);
    queryOfNewTabSubjectWindow->setWindowTitle("设置主题");
    queryForFontSizeWnd = new queryOfFontSizeWindow(this);
    queryForFontSizeWnd ->setWindowTitle("设置字体大小");
    queryOfNewTabSubjectWindow->setModal(true);
    removeTaskWnd = nullptr;
    tabLists.push_back(ui->MainSubject);
    initBasicConnection();
    initBasicKeySequence();

}

void MainWindow::initBasicConnection()
{
    // 添加任务窗口完成工作链接
    connect(queryNewTaskWindow,&queryNewTask::finishEdit,this,&MainWindow::addTaskFromQueryWnd);
    // 返回主题完成工作链接
    connect(queryOfNewTabSubjectWindow,&queryOfNewTabSubject::editFinish,this,&MainWindow::getSubjectNameFromQuerySubjectWnd);
    // 返回字体大小
    connect(queryForFontSizeWnd,&queryOfFontSizeWindow::editFinish,this,&MainWindow::setTaskFontSize);
    // 添加本主题任务
    connect(ui->action_addTaskInCurrentGroup,&QAction::triggered,this,&MainWindow::showQueryNewTaskWindow);
    // 添加主题
    connect(ui->action_addNewGroup,&QAction::triggered,this,&MainWindow::addNewSubject);
    // 更换主题名称
    connect(ui->action_changeSubjectName,&QAction::triggered,this,&MainWindow::showQueryNewSubjectWindow);
    // 移除任务
    connect(ui->action_removeCurSubjectTargetTask,&QAction::triggered,this,&MainWindow::showRemoveTaskWindow);
    // 设置字体颜色
    connect(ui->action_setFontColor,&QAction::triggered,this,&MainWindow::showColorDialog);
    // 设置字体大小
    connect(ui->action_setFontSize,&QAction::triggered,this,&MainWindow::showQueryFontSizeWindow);
    // 导入文件txt
    connect(ui->action_importFile,&QAction::triggered,this,&MainWindow::importTaskFromFile);
    // 导入文件MD
    connect(ui->action_importMdFile,&QAction::triggered,this,&MainWindow::importTaskFileFromMDFile);
}

void MainWindow::initBasicKeySequence()
{
    // 添加新任务快捷键
    QAction* openQueryWindow = new QAction;
    openQueryWindow->setShortcut(QKeySequence(tr("Ctrl+N")));
    ui->menubar->addAction(openQueryWindow);
    connect(openQueryWindow,&QAction::triggered,this,&MainWindow::showQueryNewTaskWindow);

    // 添加新主题快捷键
    QAction* openQuerySubjectWindow = new QAction;
    openQuerySubjectWindow->setShortcut(QKeySequence(tr("Ctrl+Shift+N")));
    ui->menubar->addAction(openQuerySubjectWindow);
    connect(openQuerySubjectWindow,&QAction::triggered,this,&MainWindow::addNewSubject);

    // 更改标题快捷键
    QAction* changeCurSubjectWindow = new QAction;
    changeCurSubjectWindow->setShortcut(QKeySequence(tr("Ctrl+Shift+C")));
    ui->menubar->addAction(changeCurSubjectWindow);
    connect(changeCurSubjectWindow,&QAction::triggered,this,&MainWindow::showQueryNewSubjectWindow);

    // 添加删除快捷键
    QAction* removeTaskAction = new QAction;
    removeTaskAction->setShortcut(QKeySequence(tr("Ctrl+R")));
    ui->menubar->addAction(removeTaskAction);
    connect(removeTaskAction,&QAction::triggered,this,&MainWindow::showRemoveTaskWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTaskFromQueryWnd()
{
    qDebug() << "当前正在向：" << curViewIndex;
    tabLists[curViewIndex]->addTask(queryNewTaskWindow->getEditedTask());
}

void MainWindow::showQueryNewTaskWindow()
{
    queryNewTaskWindow->show();
}

void MainWindow::showQueryNewSubjectWindow()
{
    queryOfNewTabSubjectWindow->show();
}

void MainWindow::showQueryFontSizeWindow()
{
    queryForFontSizeWnd->show();
}

void MainWindow::showRemoveTaskWindow()
{
    if(tabLists[curViewIndex]->getTaskList()->isEmpty())
    {
        QMessageBox::critical(this,"(#`O′)！","兄啊，我删不了空的东西！");
        return;
    }

    if(removeTaskWnd != nullptr)
    {
        delete removeTaskWnd;
    }

    removeTaskWnd = new removeTaskWindow(tabLists[curViewIndex],this);
    connect(removeTaskWnd,&removeTaskWindow::finishEdit,this,&MainWindow::removeTask);
    removeTaskWnd->resize(680,480);
    removeTaskWnd->show();
    removeTaskWnd->showAllTasks();
}

void MainWindow::getSubjectNameFromQuerySubjectWnd()
{
    currentSubjectName = queryOfNewTabSubjectWindow->getSubejctName();
    setCurrentSubjectName(curViewIndex);
}

void MainWindow::setCurrentSubjectName(Index setSubjectTabIndex)
{
    QTextBrowser* thisBroswer = new QTextBrowser(ui->mainTaskTab->widget(setSubjectTabIndex));
    thisBroswer->setFontPointSize(30);
    thisBroswer->setText(QString("主题： ") + currentSubjectName);
    thisBroswer->setAlignment(Qt::AlignCenter);
    thisBroswer->setGeometry(25,25,800,70);
    thisBroswer->show();
    ui->mainTaskTab->setTabText(curViewIndex,currentSubjectName);
}

void MainWindow::removeTask()
{
    removeIndexList = removeTaskWnd->returnBackIndex();
    qDebug() << removeIndexList.size();
    for(unsigned short i = 0; i < removeIndexList.size(); i++)
    {
        tabLists[curViewIndex]->removeTask(removeIndexList[i]);
    }
    tabLists[curViewIndex]->showTask();
    ui->MainSubject->update();
}

void MainWindow::addNewSubject()
{
    curViewIndex++;
    TaskGroup* newGroup = new TaskGroup(this);
    tabLists.push_back(newGroup);
    showQueryNewSubjectWindow();
    ui->mainTaskTab->addTab(newGroup,"默 认");
    ui->mainTaskTab->setCurrentIndex(curViewIndex);
}

void MainWindow::addNewSubjectFromImport(QString subjectName)
{
    curViewIndex++;
    TaskGroup* newGroup = new TaskGroup(this);
    tabLists.push_back(newGroup);
    ui->mainTaskTab->addTab(newGroup,subjectName);
    ui->mainTaskTab->setCurrentIndex(curViewIndex);
}

void MainWindow::importTaskFromFile()
{
    QString path = QFileDialog::getOpenFileName(this,"请选择导入的文件",".",tr("TXT文件(*.txt)"));
    if(path.isEmpty()){
        return; // 没选跑路了
    }

    QFile importFile(path);
    importFile.open(QIODevice::ReadOnly);
    QTextStream out(&importFile);

    //直至读取结束
    while(!out.atEnd()){
        QString str;
        //从文件中读取一个字符串
        str = out.readLine();
        if(str == "")
        {
            continue;
        }
        if(str.contains("subject:"))
        {
            // qDebug() << str.split("subject:").last() << "----------------------";
            addNewSubjectFromImport(str.split("subject:").last());
            continue;
        }
        tabLists[curViewIndex]->addTask(str);
        qDebug() << str;
    }

    // if(taskList.contains("subject"))

    return;

}

void MainWindow::importTaskFileFromMDFile()
{
    QString path = QFileDialog::getOpenFileName(this,"请选择导入的文件",".",tr("md文件(*.md)"));
    if(path.isEmpty()){
        return; // 没选跑路了
    }

    QFile importFile(path);
    importFile.open(QIODevice::ReadOnly);
    QTextStream out(&importFile);

    //直至读取结束
    while(!out.atEnd()){
        QString str;
        //从文件中读取一个字符串
        str = out.readLine().remove('#');
        if(str == "")
        {
            continue;
        }
        if(str.contains("subject:"))
        {
            // qDebug() << str.split("subject:").last() << "----------------------";
            addNewSubjectFromImport(str.split("subject:").last());
            continue;
        }
        tabLists[curViewIndex]->addTask(str);
        qDebug() << str;
    }

    // if(taskList.contains("subject"))

    return;
}


void MainWindow::on_mainTaskTab_tabBarClicked(int index)
{
    qDebug() << "用户当前聚焦于：" << index;
    curViewIndex = index;
}

bool MainWindow::event(QEvent* env)
{

    if(env->type() == QEvent::Wheel)
    {
        qDebug() << "current index: " << curViewIndex;
        QWheelEvent* wheelEnv = dynamic_cast<QWheelEvent*>(env);
        if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
        {
            if(wheelEnv->angleDelta().y() > 0)
            {
                tabLists[curViewIndex]->setTaskFontSize(
                        tabLists[curViewIndex]->getTaskFontSize() + 1
                );
            }
            else
            {
                tabLists[curViewIndex]->setTaskFontSize(
                    tabLists[curViewIndex]->getTaskFontSize() - 1
                    );
            }

        }
    }

    return QMainWindow::event(env);
}

void MainWindow::on_mainTaskTab_tabCloseRequested(int index)
{
    if(tabLists.size() == 1)
    {
        this->close();
    }
    else
    {
        if(index == ui->mainTaskTab->indexOf(ui->tab)){
            qDebug() << "检测到主页面";
            QMessageBox::critical(this,"不允许删除主页面！悲","不允许删除主页面！悲");
            return;
        }

        if(QMessageBox::No == QMessageBox::question(this,"?","你确定删除这个主题任务嘛他们将不可以恢复！真的很久！"))
        {
            qDebug() << "不删除！";
            return;
        }

        TaskGroup* getGroup = dynamic_cast<TaskGroup*>(ui->mainTaskTab->widget(index));
        if(getGroup != nullptr)
            delete getGroup;
        qDebug() << tabLists.size();

        ui->mainTaskTab->setCurrentIndex(ui->mainTaskTab->indexOf(ui->tab));
        curViewIndex = ui->mainTaskTab->indexOf(ui->tab);
        // tabLists.remove(index);
    }

}

void MainWindow::showColorDialog()
{
    QColorDialog* dialog = new QColorDialog(this);
    dialog->setWindowTitle("设置字体颜色");
    connect(dialog, &QColorDialog::colorSelected, this,&MainWindow::changeFontColor);
    dialog->show();
}

void MainWindow::changeFontColor(const QColor& color)
{
    tabLists[curViewIndex]->setFontColor(color);
}

void MainWindow::setTaskFontSize()
{
    tabLists[curViewIndex]->setTaskFontSize(queryForFontSizeWnd->getFontSize());
}

