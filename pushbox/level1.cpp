#include "level1.h"
#include "ui_level1.h"
#include <QLabel>
#include <QRandomGenerator>

Level1::Level1(int (*map)[8],int a,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Level1)
{
    ui->setupUi(this);
    //设置窗口名称
    QString A[13]={"自定义关卡","关卡一","关卡二","关卡三","关卡四","关卡五","关卡六","关卡七","关卡八","关卡九","关卡十","关卡十一","关卡十二"};
    this->setWindowTitle(A[a]);
    this->setFixedSize(512,512);
    //初始化图形绘制器
    box=new BoxGame;
    box->InitMap(map);
    qmap=new QPainter(this);
    //初始化计时器
    timer=new QTimer(this);
    timeRecord=new QTime;
    ui->lcdnumber->setDigitCount(8);//设置显示八位数字
    timer->start(1000);
    connect(timer,&QTimer::timeout,this,&Level1::updateTime);
    _notice=new Notice;
}
//初始化计步器
void Level1::initStep()
{
    backstep=0;
    step=0;
    sstep=QString::number(step);
    ui->labstep->clear();//每次填写文本前先清空labstep里的文本
    ui->labstep->setText("步数："+sstep);//向labstep里填写该次的步数
    box->initmaps();
}

void Level1::startRecord()//开始计时
{
    initTime();
}
void Level1::endRecord()//停止记时
{
    timer->stop();
}
void Level1::initTime()//初始化计时器
{
    timeRecord->setHMS(0,0,0);//时间复位为0A
    ui->lcdnumber->display(timeRecord->toString("hh:mm:ss"));
}
void Level1::updateTime()//每秒更新时间
{
    *timeRecord = timeRecord->addSecs(1);
    ui->lcdnumber->display(timeRecord->toString("hh:mm:ss"));
}
//响应键盘敲击，先将回退次数初始化，再调用boxgame的的keyDown事件，而后步数++，并进行判断游戏是否成功
void Level1::keyPressEvent(QKeyEvent* event)
{
    // Ctrl键与其他键同时被按下
    if (event->modifiers() & Qt::ControlModifier) {
        return;
    }
    if(backstep>0)
    {
        backstep--;
    }
    box->keyDown(event);
    step++;
    sstep=QString::number(step);
    ui->labstep->clear();
    ui->labstep->setText("步数："+sstep);//向labstep里填写该次的步数
    if(box->gameOver())
    {
        emit this->ok(step,timeRecord);
    }
}
void Level1::paintEvent(QPaintEvent* event)//绘制地图
{
    Q_UNUSED(event);
    qmap->begin(this);
    box->drawMap(qmap);
    qmap->end();
    update();
}
void Level1::Level1again(int (*map)[8])//重置地图
{
    initTime();
    initStep();
    box->InitMap(map);
}
Level1::~Level1()
{
    delete ui;
}

void Level1::on_restart_triggered()//点击菜单“重新开始”
{
    emit this->sLevel1again();
}

void Level1::on_back_triggered()//点击菜单“撤回”
{
    if(this->ui->labstep->text()!="步数：0"&&backstep<3)//判断条件，步数必须大于0且不超过3次
    {
        backstep++;//回退次数++
        //调用boxgame的back函数后重新绘制地图
        box->back();
        qmap->begin(this);
        box->drawMap(qmap);
        qmap->end();
        update();
        step--;//回退时步数--
        //再在labstep中填入信息
        sstep=QString::number(step);
        ui->labstep->clear();
        ui->labstep->setText("步数："+sstep);
    }
    else if(backstep==3)
    {
        _notice->show();
    }
}
//返回帮助信号
void Level1::on_help_triggered()
{
    emit this->tohelp();
}
//返回返回关卡选择信号
void Level1::on_backtolevel_triggered()
{
    emit this->backtolevel();
}
//返回开挂按钮
void Level1::on_action1_triggered()
{
    //随机一个0，1的数
    int t = QRandomGenerator::global()->bounded(2);
    if(t)
    {
        emit this->quickend();
    }
    else
    {
        box->dewall();
        qmap->begin(this);
        box->drawMap(qmap);
        qmap->end();
        update();
    }
}

void Level1::setbtn()
{
    ui->action1->setEnabled(false);
}
