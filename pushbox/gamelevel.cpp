#include "gamelevel.h"
#include "ui_gamelevel.h"

class level1;
Gamelevel::Gamelevel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gamelevel)
{
    ui->setupUi(this);
    this->setWindowTitle("推箱子");
    this->setFixedSize(512,512);
    //设置背景图片
    QPixmap backimage;
    backimage.load(":/image/gamelevelback.jpg");
    backimage=backimage.scaled(ui->label->geometry().size());
    ui->label->setPixmap(backimage);
    //设置smallp人物图标
    QPixmap startsmallp;
    startsmallp.load(":/image/smallp.png");
    startsmallp=startsmallp.scaled(ui->levelsmallp->geometry().size());
    ui->levelsmallp->setPixmap(startsmallp);
    //关卡2~12的按键首先失能
    ui->choose2->setEnabled(false);
    ui->choose3->setEnabled(false);
    ui->choose4->setEnabled(false);
    ui->choose5->setEnabled(false);
    ui->choose6->setEnabled(false);
    ui->choose7->setEnabled(false);
    ui->choose8->setEnabled(false);
    ui->choose9->setEnabled(false);
    ui->choose10->setEnabled(false);
    ui->choose11->setEnabled(false);
    ui->choose12->setEnabled(false);
}

Gamelevel::~Gamelevel()
{
    delete ui;
}

/*
 * 以下十二个模块功能
 * 1、点击关卡，发送tolevel(n)的信号给主页面
 * 2、结算页面出现后（即通关后），使下一关按钮得能
 */
void Gamelevel::on_choose1_clicked()
{
    emit this->toLevel1();
}
void Gamelevel::Level1Finished()
{
    ui->choose2->setEnabled(true);
}

void Gamelevel::on_choose2_clicked()
{
    emit this->toLevel2();
}
void Gamelevel::Level2Finished()
{
    ui->choose3->setEnabled(true);
}

void Gamelevel::on_choose3_clicked()
{
    emit this->toLevel3();
}
void Gamelevel::Level3Finished()
{
    ui->choose4->setEnabled(true);
}

void Gamelevel::on_choose4_clicked()
{
    emit this->toLevel4();
}
void Gamelevel::Level4Finished()
{
    ui->choose5->setEnabled(true);
}

void Gamelevel::on_choose5_clicked()
{
    emit this->toLevel5();
}
void Gamelevel::Level5Finished()
{
    ui->choose6->setEnabled(true);
}

void Gamelevel::on_choose6_clicked()
{
    emit this->toLevel6();
}
void Gamelevel::Level6Finished()
{
    ui->choose7->setEnabled(true);
}

void Gamelevel::on_choose7_clicked()
{
    emit this->toLevel7();
}
void Gamelevel::Level7Finished()
{
    ui->choose8->setEnabled(true);
}

void Gamelevel::on_choose8_clicked()
{
    emit this->toLevel8();
}
void Gamelevel::Level8Finished()
{
    ui->choose9->setEnabled(true);
}

void Gamelevel::on_choose9_clicked()
{
    emit this->toLevel9();
}
void Gamelevel::Level9Finished()
{
    ui->choose10->setEnabled(true);
}

void Gamelevel::on_choose10_clicked()
{
    emit this->toLevel10();
}
void Gamelevel::Level10Finished()
{
    ui->choose11->setEnabled(true);
}

void Gamelevel::on_choose11_clicked()
{
    emit this->toLevel11();
}
void Gamelevel::Level11Finished()
{
    ui->choose12->setEnabled(true);
}

void Gamelevel::on_choose12_clicked()
{
    emit this->toLevel12();
}


void Gamelevel::on_help_triggered()
{
    emit this->tohelp();
}

void Gamelevel::on_start_triggered()
{
    emit this->toLevel1();
}

void Gamelevel::on_custom_triggered()
{
    emit this->tocustom();
}

void Gamelevel::on_settings_triggered()
{
    emit this->tosettings();
}
