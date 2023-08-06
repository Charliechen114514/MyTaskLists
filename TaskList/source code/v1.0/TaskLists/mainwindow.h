#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTextBrowser>
#include <QColorDialog>
#include <QEvent>
#include "taskgroup.h"
#include "querynewtask.h"
#include "queryofnewtabsubject.h"
#include "removetaskwindow.h"
#include "queryoffontsizewindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // initer
    MainWindow(QWidget *parent = nullptr);
    // eraser
    ~MainWindow();
    // setKeySequence

    void    showQueryNewTaskWindow();
    void    showQueryNewSubjectWindow();
    void    showRemoveTaskWindow();
    void    showColorDialog();
    void    showQueryFontSizeWindow();
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
    void                    initBasicKeySequence();
    void                    initBasicConnection();
    void                    getSubjectNameFromQuerySubjectWnd();



};
#endif // MAINWINDOW_H
