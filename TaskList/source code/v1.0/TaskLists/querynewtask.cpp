#include "querynewtask.h"
#include "ui_querynewtask.h"
queryNewTask::queryNewTask(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::queryNewTask)
{
    ui->setupUi(this);
}

queryNewTask::~queryNewTask()
{
    delete ui;
}

void queryNewTask::on_btn_cancel_clicked()
{
    this->close();
}

void queryNewTask::on_btn_redo_clicked()
{
    this->ui->taskEdit->setText(DEF_REDO_STR);
}

void queryNewTask::on_btn_ensure_clicked()
{
    QTextDocument* pDoc = ui->taskEdit->document();
    QTextBlock textBlock = pDoc->findBlockByNumber(0);
    tasktext = textBlock.text(); // finishInit
    if(tasktext.isEmpty())
    {
        QMessageBox::critical(this,"嘿！","任务不可以为空！别想混！");
        return;
    }

    emit finishEdit();
    ui->taskEdit->setText("");
    this->close();
}

