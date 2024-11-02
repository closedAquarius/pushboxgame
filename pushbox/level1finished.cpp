#include "level1finished.h"
#include "ui_level1finished.h"

Level1Finished::Level1Finished(int a,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level1Finished)
{
    ui->setupUi(this);
    //设置窗口标题
    QString A[13]={"自定义关卡","关卡一","关卡二","关卡三","关卡四","关卡五","关卡六","关卡七","关卡八","关卡九","关卡十","关卡十一","关卡十二"};
    setWindowTitle(A[a]);

    QPixmap con;
    con.load(":/image/con.png");
    con=con.scaled(ui->con->geometry().size());
    ui->con->setPixmap(con);
    ui->con->lower();
    ui->congratulations->setStyleSheet("color: white;");
    ui->congratulations->setText("恭喜你通过了"+A[a]+"!");
    ui->lineEdit->setStyleSheet("color: white;border: 1px solid white;");
}

Level1Finished::~Level1Finished()
{
    delete ui;
}

//响应返回关卡选择，发出信号
void Level1Finished::on_btnback_clicked()
{
    emit this->backtogamelevel();
}

//响应再来一次，发出信号
void Level1Finished::on_btnagain_clicked()
{
    emit this->level1again();
}

//响应下一关，发出信号
void Level1Finished::on_btnnextlevel_clicked()
{
    emit this->level1next();
}

void Level1Finished::setText(int step,QTime *timeRecord)
{
    QString sstep=QString::number(step);
    ui->lineEdit->clear();
    ui->lineEdit->setText("步数："+sstep);
    ui->lcdNumber->display(timeRecord->toString("hh:mm:ss"));
}

void Level1Finished::setbtn()
{
    ui->btnnextlevel->setEnabled(false);
}
