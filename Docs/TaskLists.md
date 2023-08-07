# MyQt Project Document

## Document01: TaskLists v1.0

## 写在前面

​		这是一个我自己的任务列表的实现，是我的第二个Qt项目（比较迷你与原始）。他的功能就是一个任务本，支持导入Markdown文本和普通文本文件的任务薄记本。作为一个写了大约8个小时的小东西，肯定有很多不完善的地方，可能会在后续改进。

## 结构

![basicStructure](.\basicStructure.png)

​		如上图所示，我并没有给这个它设计很复杂的窗口逻辑，甚至没有用到自己定义的继承——而是依靠指针简单的维护。

## 使用方法

​		简单到不需要我说什么！只不过需要注意的是——每个任务都需要单独一行，对于主题，务必加上前缀符号`subject:`

```
subject:测试
任务1
任务2
任务3
```

​		无论是Markdown还是txt格式的文件都需要如此的读取。

## 源码与实现思路

​		这是一个总结与补充，特此说明我的一些简单的设计思路。（很潦草（悲），毕竟是走路10分钟想到的框架）

### 核心: Task类和Group类

​		我们的程序抛开GUI,本质上就是对任务和任务集合进行操作. 在这里,我选择比较细致的抽象---对于任务,我采取了单独封装成类而不是简单的直接扔进集合里 ---换而言之,不是将表达任务的字符串直接扔进TaskGroup下的某个托管集合(诸如`QList<QString>`这样太简单的封装)而是将任务单独抽象.构成Task类

```C++
// task.h

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

// group.h
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

    // getter
    Index getGroupIndex()   {return groupIndex;}
    QString getGroupName()  {return QString(groupName);}
private:
    Index   groupIndex;
    QString groupName;
};

#endif // GROUP_H

```

#### Task Public方法描述

| 函数名称           | 返回类型  | 参数      | 描述                           |
| :----------------- | --------- | --------- | ------------------------------ |
| `setNewTaskIndex`  | `void`    | `Index`   | [[setter]]设置任务标号         |
| `setNewGroupIndex` | `void`    | `Index`   | [[setter]]设置任务组别         |
| `setNewTaskText`   | `void`    | `QString` | [[setter]]设置任务描述文本     |
| `getTaskIndex`     | `Index`   | `void`    | [[getter]]获取当前Task标号     |
| `getGroupIndex`    | `Index`   | `void`    | [[getter]]获取当前Task组别     |
| `getTaskText`      | `QString` | `void`    | [[getter]]获取当前Task描述文本 |

#### Task Private 字段描述

| 字段         | 类型      | 描述     |
| ------------ | --------- | -------- |
| `groupIndex` | `Index`   | 组别     |
| `taskIndex`  | `Index`   | 标号     |
| `taskText`   | `QString` | 描述文本 |

#### Group Public方法描述

| 函数名称        | 返回类型  | 参数      | 描述         |
| --------------- | --------- | --------- | ------------ |
| `setGroupIndex` | `void`    | `Index`   | 设置组别编号 |
| `setGroupName`  | `void`    | `QString` | 设置组名称   |
| `getGroupIndex` | `Index`   | `void`    | 获取组编号   |
| `getGroupName`  | `QString` | `void`    | 获取组名称   |

#### Group Private字符描述

| 字段         | 类型      | 描述     |
| ------------ | --------- | -------- |
| `groupIndex` | `Index`   | 组别号   |
| `groupName`  | `QString` | 组别名称 |

​		他很简单, 在这个v1.0版本里,这个Task就是对QString进行扩充,增加了`taskIndex`(当前任务指标)和`groupIndex`(属于的组别),在v1.0版本里我并没有启用两个附加的属性,他们将会在之后的新版本中发挥作用! 任何一个熟悉基础语法的程序员都会快速拿下这个类---我只是将其抽象化为类,没有给其书写更多相关的行为!(PS:在后续的开发中,我意识到我并没有好好利用Task类,之后会提到的),Group类同理,不做阐述.

### TaskGroup类

​		作为1.0, 我并没有细化的书写每个任务栏的行为,大部分的属性API只是对他们两者的组合类TaskGroup做操作:如下

```cpp
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
    /* Three constructor */
    explicit TaskGroup(QWidget *parent = nullptr);
    explicit TaskGroup(Group& group, QList<Task*>& taskList,QWidget *parent = nullptr); 
    explicit TaskGroup(const TaskGroup& copy,QWidget *parent = nullptr);
    // this addTask shouldn't be use unless in future version(Copy Task)
    void                     addTask(const Task& task); 
    // Mainly used
    void                     addTask(QString taskName);
    // Another constructor:> will add `explicit` in future version
    void                     addTask(const char* taskName);
    // queryMainWindowOne is in mainWindow section
    void                     showTask();
    // remove item
    void                     removeTask(int removeIndex);

    // setTaskFinished
    void                     setFinished(QAbstractButton* btn, bool flag);
	
    // getter for font-size
    int                      getTaskFontSize()                      {return taskFontSize;}
    // setter for font-size
    void                     setTaskFontSize(int taskFontSize);
    // getter for font-color
    QColor                   getFontColor()                      	{return colorOfFont;};
    // setter for font-color
    void                     setFontColor(const QColor color);
    
    // public getter for data
    QList<QCheckBox*>*       getTaskButtonList()                    {return &taskGroupButtons;}
    QList<Task*>*            getTaskList()                          {return &taskData;}
signals:
    void                     signalTaskFull(); [[deprecated]]

private:
	// store Tasks for a Group
    QList<Task*>             taskData;
    // signal a Group and store group-relevant information
    Group                    thisGroup;
    // get Remove index for future version:> [[TODO]] remove multiple data at one time
    QList<int>               removeIndex;
	QButtonGroup*            taskGroup;
    QList<QCheckBox*>        taskGroupButtons;
    // font Related:
    QColor                   colorOfFont;
    int                      taskFontSize;
};

#endif // TASKGROUP_H
```

​		好多API, wait我一下啊,我列一下

#### TaskGroup Public方法描述

| 方法名称                      | 返回类型 | 参数                                                         | 描述                            |
| ----------------------------- | -------- | ------------------------------------------------------------ | ------------------------------- |
| [[Overrides]]TaskGroup(CONFG) | NON      | QWidget parent = nullptr  [or] <br>Group& group, QList<Task*>& taskList,QWidget *parent = nullptr [or]<br>const TaskGroup& copy,QWidget *parent = nullptr | 构造函数                        |
| [[Overrides]]addTask(CONFG)   | void     | Task& task [or]<br>QString taskText [or]<br>const char* taskText | 向该任务组内添加任务            |
| showTask                      | void     | void                                                         | 为窗口绘图作控件生成预备        |
| removeTask                    | void     | int removeIndex                                              | 根据给出的removeIndex来删除任务 |
| setFinished                   | void     | QAbstractButton* btn, bool flag                              | 对传入的摁扭作已完成勾选处理    |
| getTaskFontSize               | int      | void                                                         | [[getter]]得到字体的大小        |
| setTaskFontSize               | void     | int taskFontSize                                             | [[setter]]设置全组的字体大小    |
| getFontColor                  | QColor   | void                                                         | [[getter]]得到字体的颜色        |
| setFontColor                  | void     | QColor fontColor                                             | [[setter]]设置全组的字体颜色    |

#### TaskGroup Private 字段维护

| 字段名称           | 类型              | 说明             |
| ------------------ | ----------------- | ---------------- |
| taskData           | QList<Task*>      | Task集合         |
| thisGroup          | Group             | Group组别        |
| [[tmp]]removeIndex | `QList<int>`      | 移除的Index集合  |
| taskGroup          | QButtonGroup*     | 摁扭逻辑关系合集 |
| taskGroupButtons   | QList<QCheckBox*> | 摁扭             |
| colorOfFont        | QColor            | 字体颜色         |
| taskFontSize       | int               | 字体大小         |



### MainWindow

​		任何一个写初步Qt程序的都知道，Qt构建时就会默认的创建运行主线程的文件：main.cpp

```Cpp
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("MyTaskLists");
    w.show();
    return a.exec();
}
```

​		MainWindow就是我们一开始打开弹出的那个窗口了！所以，我们主要围绕它，来设计我们的任务薄记本。

​		MainWindow的API如下

```cpp
/* from MainWindow.h */
class MainWindow : public QMainWindow
{
    Q_OBJECT // QObj的基本属性宏

public:
    // initer
    MainWindow(QWidget *parent = nullptr); // 构造函数
    // eraser
    ~MainWindow(); // 析构函数
    // setKeySequence
	// 显示新增Task
    void    showQueryNewTaskWindow();
    void    showQueryNewSubjectWindow();
    void    showRemoveTaskWindow();
    void    showColorDialog();
    void    showQueryFontSizeWindow();

    void    importTaskFromFile();
    void    importTaskFileFromMDFile();
    void    setCurrentSubjectName(Index setSubjectTabIndex); // from currentSubectName;
    void    removeTask();
    bool    event(QEvent* env);
    void    changeFontColor(const QColor& color);
    void    setTaskFontSize();
private slots:
    void    on_mainTaskTab_tabBarClicked(int index);
    void    on_mainTaskTab_tabCloseRequested(int index);


private:
    Ui::MainWindow*         ui;
    queryNewTask*           queryNewTaskWindow;
    queryOfNewTabSubject*   queryOfNewTabSubjectWindow;
    removeTaskWindow*       removeTaskWnd;
    queryOfFontSizeWindow*  queryForFontSizeWnd;

    QList<TaskGroup*>       tabLists;
    QList<QTextBrowser>     browserList;
    QStringList             subjectList;
    QString                 currentSubjectName;
    Index                   curViewIndex;
    QList<int>              removeIndexList;
    QTabWidget*             mainTaskTab;
    // addTaskFromQueryMainWindow
    void                    addTaskFromQueryWnd();
    void                    addNewSubject();
    void                    addNewSubjectFromImport(QString subjectName);
    void                    initBasicKeySequence();
    void                    initBasicConnection();
    void                    getSubjectNameFromQuerySubjectWnd();
};
```

​		作为最核心的窗口，我分的权限比较细致，如下：

#### Public 方法 维护

| 方法名称                  | 返回类型 | 参数                        | 描述                                |
| ------------------------- | -------- | --------------------------- | ----------------------------------- |
| showQueryNewTaskWindow    | void     | void                        | 显示新增任务窗口                    |
| showQueryNewSubjectWindow | void     | void                        | 显示任务主题设置窗口                |
| showRemoveTaskWindow      | void     | void                        | 显示任务移除窗口                    |
| showColorDialog           | void     | void                        | 显示文本调色窗口                    |
| showQueryFontSizeWindow   | void     | void                        | 显示文本大小调整窗口                |
| importTaskFromFile        | void     | void                        | 导入TXT文件窗口                     |
| importTaskFileFromMDFile  | void     | void                        | 导入MD文件窗口                      |
| setCurrentSubjectName     | void     | Index setSubjectTabIndex    | 设置当前主题文本框                  |
| removeTask                | void     | void                        | 依照removeIndex链表删除当前组别任务 |
| event                     | void     | QEvent* env[[maybe_unused]] | 重写的窗口关闭行为                  |
| changeFontColor           | void     | const QColor& color         | 设置文本颜色                        |
| setTaskFontSize           | void     | void                        | 设置文本大小                        |

#### Private Slot 维护

| 方法名称                                       | 返回类型 | 参数      | 描述                      |
| ---------------------------------------------- | -------- | --------- | ------------------------- |
| on_mainTaskTab_tabBarClicked                   | void     | int index | 切换到Index页下的函数响应 |
| on_mainTaskTab_tabCloseRequested[[deprecated]] | void     | int index | Index页关闭响应           |

#### Private 方法描述

| 方法名称                         | 返回类型 | 参数                | 描述                         |
| -------------------------------- | -------- | ------------------- | ---------------------------- |
| addTaskFromQueryWnd              | void     | void                | 通过询问窗口添加任务         |
| addNewSubject                    | void     | void                | 添加主题                     |
| addNewSubjectFromImport          | void     | QString subjectName | 通过外部导入添加主题         |
| initBasicKeySequence             | void     | void                | 设置快捷键                   |
| initBasicConnection              | void     | void                | 设置信号与槽                 |
| etSubjectNameFromQuerySubjectWnd | void     | void                | 通过询问窗口添加得到主题名称 |

#### Private 字段描述

| 名称                       | 类型                   | 说明                |
| -------------------------- | ---------------------- | ------------------- |
| ui                         | Ui::MainWindow*        | UI界面的控件        |
| queryNewTaskWindow         | queryNewTask*          | 新建任务窗口        |
| queryOfNewTabSubjectWindow | queryOfNewTabSubject*  | 新建主题窗口        |
| removeTaskWnd              | removeTaskWindow*      | 移除任务窗口        |
| queryForFontSizeWnd        | queryOfFontSizeWindow* | 询问字体大小窗口    |
| tabLists                   | QList<TaskGroup*>      | GUI控件维护链表     |
| browserList                | `QList<QTextBrowser>`  | 文本框维护链表      |
| subjectList                | QStringList            | 主题维护链表        |
| currentSubjectName         | QString                | [[tmp]]当前主题名称 |
| curViewIndex               | Index                  | 但前浏览的Index     |
| removeIndexList            | `QList<int>`           | [[tmp]]移除的Index  |

​		其他窗体类都是获取类的窗体---这里不做展开字段说明
