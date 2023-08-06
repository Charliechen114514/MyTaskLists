#ifndef QUERYOFNEWTABSUBJECT_H
#define QUERYOFNEWTABSUBJECT_H

#define ENABLE_NO_SUBJECT 1

#include <QDialog>
#include <QKeyEvent>
#include <QMessageBox>
namespace Ui {
class queryOfNewTabSubject;
}

class queryOfNewTabSubject : public QDialog
{
    Q_OBJECT

public:
    explicit queryOfNewTabSubject(QWidget *parent = nullptr);
    QString getSubejctName(){return QString(this->subjectName);}

    void    keyPressEvent(QKeyEvent* env);

    ~queryOfNewTabSubject();
signals:

    void editFinish();

private slots:
    void on_btn_cancel_clicked();

    void on_btn_resume_clicked();

    void on_btn_ensure_clicked();

private:
    Ui::queryOfNewTabSubject *ui;
    QString subjectName;
};

#endif // QUERYOFNEWTABSUBJECT_H
