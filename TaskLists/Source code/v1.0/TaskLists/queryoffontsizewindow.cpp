#include "queryoffontsizewindow.h"
#include "ui_queryoffontsizewindow.h"

queryOfFontSizeWindow::queryOfFontSizeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::queryOfFontSizeWindow)
{
    ui->setupUi(this);
    isCancelFlag = false;
    QRegularExpression regExp("0|[1-9]\\d{0,1}");
    ui->fontSizeQueryLineEdit->setValidator(new QRegularExpressionValidator(regExp));
}

queryOfFontSizeWindow::~queryOfFontSizeWindow()
{
    delete ui;
}



void queryOfFontSizeWindow::on_btn_cancel_clicked()
{
    isCancelFlag = true;
    this->close();
}


void queryOfFontSizeWindow::on_btn_clear_clicked()
{
    ui->fontSizeQueryLineEdit->setText("");
}


void queryOfFontSizeWindow::on_btn_ensure_clicked()
{

    this->close();
}

void queryOfFontSizeWindow::closeEvent(QCloseEvent* env[[maybe_unused]])
{
    if(isCancelFlag)
    {
        env->accept();
        isCancelFlag = false;
    }
    else
    {
        if(ui->fontSizeQueryLineEdit->text().toInt() <= FONTSIZE_MIN || ui->fontSizeQueryLineEdit->text().toInt() > FONTSIZE_MAX)
        {
            qDebug() << "检测到超出范围的字体设置请求";
            QMessageBox::critical(this,"(╯▔皿▔)╯","喂！不要设置过大或者过小的字体！");
            env->ignore();
        }
        else
        {
            this->fontSize = ui->fontSizeQueryLineEdit->text().toInt();
            emit editFinish();
        }
    }


}

