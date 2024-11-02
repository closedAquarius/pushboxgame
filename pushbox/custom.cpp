#include "custom.h"
#include "ui_custom.h"

Custom::Custom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Custom)
{
    ui->setupUi(this);
    setWindowTitle("自定义关卡");
}

//读取用户输入的信息
void Custom::setmap(int(*map)[8])
{
    QString s1=ui->lineEdit_1->text();
    for(int j=0;j<8;j++)
    {
        map[0][j]=s1[j].toLatin1()-'0';
    }
    QString s2=ui->lineEdit_2->text();
    for(int j=0;j<8;j++)
    {
        map[1][j]=s2[j].toLatin1()-'0';
    }
    QString s3=ui->lineEdit_3->text();
    for(int j=0;j<8;j++)
    {
        map[2][j]=s3[j].toLatin1()-'0';
    }
    QString s4=ui->lineEdit_4->text();
    for(int j=0;j<8;j++)
    {
        map[3][j]=s4[j].toLatin1()-'0';
    }
    QString s5=ui->lineEdit_5->text();
    for(int j=0;j<8;j++)
    {
        map[4][j]=s5[j].toLatin1()-'0';
    }
    QString s6=ui->lineEdit_6->text();
    for(int j=0;j<8;j++)
    {
        map[5][j]=s6[j].toLatin1()-'0';
    }
    QString s7=ui->lineEdit_7->text();
    for(int j=0;j<8;j++)
    {
        map[6][j]=s7[j].toLatin1()-'0';
    }
    QString s8=ui->lineEdit_8->text();
    for(int j=0;j<8;j++)
    {
        map[7][j]=s8[j].toLatin1()-'0';
    }
}

//每次重新打开前清空文本框
void Custom::cleartext()
{
    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
}

Custom::~Custom()
{
    delete ui;
}

//用户点击“点击创建”的按钮进行保存创建
void Custom::on_create_clicked()
{
    emit this->create();
}

//用户点击“进入游戏”的按钮进入游戏
void Custom::on_toclevel_clicked()
{
    emit this->toclevel();
}
