#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    this->setWindowTitle("帮助");
    //设置smallp人物图标
    QPixmap startsmallp;
    startsmallp.load(":/image/smallp.png");
    startsmallp=startsmallp.scaled(ui->helpsmallp->geometry().size());
    ui->helpsmallp->setPixmap(startsmallp);
}

Help::~Help()
{
    delete ui;
}
