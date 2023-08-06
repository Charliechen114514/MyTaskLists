#ifndef QUERYOFFONTSIZEWINDOW_H
#define QUERYOFFONTSIZEWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <Utils.h>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
namespace Ui {
class queryOfFontSizeWindow;
}

class queryOfFontSizeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit queryOfFontSizeWindow(QWidget *parent = nullptr);
    void setFontSize(int fontSize)  {this->fontSize = fontSize;}
    int getFontSize()               {return fontSize;}
    ~queryOfFontSizeWindow();

private slots:

    void on_btn_cancel_clicked();

    void on_btn_clear_clicked();

    void on_btn_ensure_clicked();

    void closeEvent(QCloseEvent* env);
signals:
    void editFinish();

private:
    Ui::queryOfFontSizeWindow *ui;
    bool isCancelFlag;
    int fontSize;
};

#endif // QUERYOFFONTSIZEWINDOW_H
