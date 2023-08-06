#ifndef QUERYFORSETSUBJECT_H
#define QUERYFORSETSUBJECT_H

#include <QWidget>
#include "queryofnewtabsubject.h"
class queryForSetSubject : public QWidget
{
    Q_OBJECT
public:
    explicit queryForSetSubject(QWidget *parent = nullptr);
    queryOfNewTabSubject*                  queryWindow;
    void setSubjectName(){subjectName = queryWindow->getSubejctName();}
signals:
    void finishEditNewSubjectName();
    QString subjectName;
private:
    void setConnections();

};

#endif // QUERYFORSETSUBJECT_H
