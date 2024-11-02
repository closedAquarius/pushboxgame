#include "allfinished.h"
#include "ui_allfinished.h"
#include <QPixmap>

AllFinished::AllFinished(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllFinished)
{
    ui->setupUi(this);
    this->setWindowTitle("恭喜恭喜");

    //设置dog庆祝图标
    QPixmap dog;
    dog.load(":/image/dogcongratulations.png");
    dog=dog.scaled(ui->dog->geometry().size());
    ui->dog->setPixmap(dog);
}

AllFinished::~AllFinished()
{
    delete ui;
}

//响应返回关卡选择，发出信号
void AllFinished::on_back_clicked()
{
    emit this->backtogamelevel();
}

//响应再来一次，发出信号
void AllFinished::on_again_clicked()
{
    emit this->level1again();
}
void AllFinished::setText(int step,QTime *timeRecord)
{
    QString sstep=QString::number(step);
    ui->step->clear();
    ui->step->setText("步数："+sstep);
    ui->lcdNumber->display(timeRecord->toString("hh:mm:ss"));

}
