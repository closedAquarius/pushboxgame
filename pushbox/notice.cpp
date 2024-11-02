#include "notice.h"
#include "ui_notice.h"
#include <QPixmap>

Notice::Notice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Notice)
{
    ui->setupUi(this);
    QPixmap warn;
    warn.load(":/image/warning.png");
    warn=warn.scaled(ui->warn->geometry().size());
    ui->warn->setPixmap(warn);
}

Notice::~Notice()
{
    delete ui;
}
