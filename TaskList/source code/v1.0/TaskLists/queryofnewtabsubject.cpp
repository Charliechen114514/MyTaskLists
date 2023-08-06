#include "queryofnewtabsubject.h"
#include "ui_queryofnewtabsubject.h"

queryOfNewTabSubject::queryOfNewTabSubject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::queryOfNewTabSubject)
{
    ui->setupUi(this);
}

queryOfNewTabSubject::~queryOfNewTabSubject()
{
    delete ui;
}

void queryOfNewTabSubject::keyPressEvent(QKeyEvent* env)
{
    if(env->key() == Qt::Key_Return){
        on_btn_ensure_clicked(); // 调用确认函数
    }
}


void queryOfNewTabSubject::on_btn_cancel_clicked()
{
    this->close();
}


void queryOfNewTabSubject::on_btn_resume_clicked()
{
    this->ui->subjectEdit->setText("");
}


void queryOfNewTabSubject::on_btn_ensure_clicked()
{
    subjectName = this->ui->subjectEdit->text();
    if(subjectName == "")
    {
        if(ENABLE_NO_SUBJECT)
        {
            subjectName = "默 认";
        }
        else
        {
            QMessageBox::critical(this,"(╯▔皿▔)╯","不可以是空的主题！至少打个空格!");
            return;
        }
    }
    emit editFinish();
    this->ui->subjectEdit->setText("");
    this->close();
}

