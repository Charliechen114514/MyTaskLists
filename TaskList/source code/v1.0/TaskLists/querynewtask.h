#ifndef QUERYNEWTASK_H
#define QUERYNEWTASK_H

#include <QMainWindow>
#include <QTextEdit>
#include <QTextBlock>
#include <QTextDocument>
#include <QMessageBox>
#define DEF_REDO_STR "在这里！输入你的任务："


namespace Ui {
class queryNewTask;
}

class queryNewTask : public QMainWindow
{
    Q_OBJECT

public:
    explicit queryNewTask(QWidget *parent = nullptr);
    QString getEditedTask() const {return tasktext;}
    ~queryNewTask();

signals:
    void finishEdit(); // press btn_ensure and emit the signals

private slots:

    void    on_btn_cancel_clicked();

    void    on_btn_redo_clicked();

    void    on_btn_ensure_clicked();

private:
    Ui::queryNewTask *ui;
    QString tasktext;
};

#endif // QUERYNEWTASK_H
