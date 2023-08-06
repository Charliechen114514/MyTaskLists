#ifndef REMOVETASKWINDOW_H
#define REMOVETASKWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QCheckBox>
#include <taskgroup.h>
namespace Ui {
class removeTaskWindow;
}

class removeTaskWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit removeTaskWindow(TaskGroup* group, QWidget *parent = nullptr);
    void showAllTasks();
    void closeEvent(QCloseEvent* env);
    void removeFromList(int index);
    void appendToList(int index);
    void checkButtonAndDoList(int index, bool status);
    ~removeTaskWindow();
    QList<int> returnBackIndex(){return removeIndex;}
signals:
    void finishEdit();

private:
    Ui::removeTaskWindow         *ui;
    TaskGroup*                   group;
    QList<int>                   removeIndex;
};

#endif // REMOVETASKWINDOW_H
