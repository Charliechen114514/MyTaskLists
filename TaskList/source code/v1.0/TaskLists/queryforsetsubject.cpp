#include "queryforsetsubject.h"

queryForSetSubject::queryForSetSubject(QWidget *parent)
    : QWidget{parent}
{
    queryWindow = new queryOfNewTabSubject(this);
    queryWindow->show();
}

void queryForSetSubject::setConnections()
{
    // get string from the windows
    connect(queryWindow,&queryOfNewTabSubject::editFinish,this,&queryForSetSubject::setSubjectName);
}

void
