#include "start.h"
#include "ui_start.h"
#include <QTimer>

Start::Start(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Start)
{
    ui->setupUi(this);
    //设置主窗口参数
    this->setWindowTitle("推箱子");
    this->setFixedSize(512,512);

    //添加背景图片startback和人物图startsmallp
    QPixmap startsmallp;
    startsmallp.load(":/image/smallp.png");
    startsmallp=startsmallp.scaled(ui->startsmallp->geometry().size());
    ui->startsmallp->setPixmap(startsmallp);
    QPixmap startback;
    startback.load(":/image/startback.jpg");
    startback=startback.scaled(ui->startback->geometry().size());
    ui->startback->setPixmap(startback);

    //设置背景音乐
    _music=new Music;


    //创建关卡页面 _gamelevel1
    _gamelevel1=new Gamelevel;

    //响应关卡选择页面发出的“设置”
    connect(_gamelevel1,&Gamelevel::tosettings,[=](){
       _music->show();
    });
    //创建帮助页面并响应关卡选择页面“帮助”按钮
    _help=new Help;
    connect(_gamelevel1,&Gamelevel::tohelp,this,[=](){
       _help->show();
    });


    //创建关卡1 _level11A
    _level11=new Level1(map1,1);
    //关卡1响应信号模块
        //响应关卡选择页面点击“关卡一”按钮，跳转到关卡1界面并开始计时，初始化步数
    connect(_gamelevel1,&Gamelevel::toLevel1,[=](){
        _gamelevel1->hide();
        _level11->show();
        _level11->Level1again(map1);//再次点击“关卡一”按钮时，重置地图
        _level11->startRecord();//初始化计时器并开始计时
        _level11->initStep();//初始化计数器和撤回容器
    });
        //响应关卡1“菜单”中“重新开始”页面，重置关卡1地图
    connect(_level11,&Level1::sLevel1again,this,[=](){
        _level11->Level1again(map1);//此函数功能是集成1、初始化计时器并开始计时；2、初始化计数器和撤回容器，3、重置地图
    });
        //响应关卡1“菜单”中“帮助”页面，跳出帮助
    connect(_level11,&Level1::tohelp,this,[=](){
        _help->show();
    });
        //响应关卡1“菜单”中“返回”页面，跳转关卡选择
    connect(_level11,&Level1::backtolevel,this,[=]()
    {
        _gamelevel1->show();
        _level11->close();
    });
        //响应关卡1“菜单”中“一键通关”页面，一键通关
    connect(_level11,&Level1::quickend,this,[=]()
    {
        _level11->Level1again(qmap1);
    });
    //创建关卡1的结算页面 _level1finished
    _level1finished=new Level1Finished(1);
        //响应捕捉关卡1通关条件发出的信号ok，显示结算页面and选择关卡页面关卡2得能
    connect(_level11,&Level1::ok,[=](int step,QTime *timeRecord){
        _level1finished->show();
        _level1finished->setText(step,timeRecord);
        _level11->endRecord();//暂停计时
        _gamelevel1->Level1Finished();
    });
        //响应关卡1结算页面点击按钮“返回”，跳转到选择关卡页面and关闭关卡1
    connect(_level1finished,&Level1Finished::backtogamelevel,this,[=](){
        _level11->close();
        _level1finished->close();
        _gamelevel1->show();
    });
        //响应关卡1结算页面点击按钮“再来一次”，关闭结算页面，并展示关卡1后重置地图
    connect(_level1finished,&Level1Finished::level1again,this,[=](){
        _level1finished->close();
        _level11->show();
        _level11->Level1again(map1);
    });
    /*总结：
     * 1、响应关卡选择页面关卡按钮tolevel(n)
     * 2、响应游戏关卡页面菜单“重新开始”slevel1again
     * 3、响应游戏关卡页面菜单“帮助”tohelp
     * 4、响应游戏关卡页面菜单“返回”backtolevel
     * 5、响应游戏关卡页面菜单“遥遥领先”quickend
     * 6、响应游戏关卡通关条件0k
     * 7、响应游戏关卡结算页面“返回”backtogamelevel
     * 8、响应游戏关卡结算页面“再来一次”level1again
     * 9、响应游戏关卡结算页面“下一关”level1next——一般在下一关响应
     * 10、响应游戏关卡页面菜单“重新开始”
     * 每关逻辑大差不差
     */



    //创建关卡2 _level12
    _level12=new Level1(map2,2);
    //关卡2响应信息模块
        //响应关卡1结算页面点击按钮“下一关”，跳转到关卡2and关闭关卡1
    connect(_level1finished,&Level1Finished::level1next,this,[=](){
        _level11->close();
        _level1finished->close();
        _level12->show();
        _level12->Level1again(map2);
        _level12->startRecord();
        _level12->initStep();
    });
        //响应选择关卡页面点击“关卡二”按钮，跳转到关卡2界面
    connect(_gamelevel1,&Gamelevel::toLevel2,this,[=](){
        _gamelevel1->hide();
        _level12->show();
        _level12->Level1again(map2);
        _level12->startRecord();
        _level12->initStep();
    });
        //响应关卡2“菜单”中“重新开始”页面，重置关卡2地图
    connect(_level12,&Level1::sLevel1again,this,[=](){
        _level12->Level1again(map2);
    });
        //响应关卡2“菜单”中“帮助”页面，跳出帮助
    connect(_level12,&Level1::tohelp,this,[=](){
        _help->show();
    });
        //响应关卡2“菜单”中“返回”页面，跳转关卡选择
    connect(_level12,&Level1::backtolevel,this,[=]()
    {
        _gamelevel1->show();
        _level12->close();
    });
        //响应关卡2“菜单”中“一键通关”页面，一键通关
    connect(_level12,&Level1::quickend,this,[=]()
    {
        _level12->Level1again(qmap2);
    });
    //创建关卡2的结算页面 _level2finished
    _level2finished=new Level1Finished(2);
        //响应捕捉关卡2通关条件发出的信号ok，显示结算页面and选择关卡页面关卡3得能
    connect(_level12,&Level1::ok,[=](int step,QTime *timeRecord){
        _level2finished->show();
        _level2finished->setText(step,timeRecord);
        _level12->endRecord();
        _gamelevel1->Level2Finished();
    });
        //响应关卡2结算页面点击按钮“返回”，跳转到选择关卡页面and关闭关卡2
    connect(_level2finished,&Level1Finished::backtogamelevel,this,[=](){
        _level12->close();
        _level2finished->close();
        _gamelevel1->show();
    });
        //响应关卡2结算页面点击按钮“再来一次”，关闭结算页面，并展示关卡2后重置地图
    connect(_level2finished,&Level1Finished::level1again,this,[=](){
        _level2finished->close();
        _level12->show();
        _level12->Level1again(map2);
    });



    //创建关卡3 _level13
    _level13=new Level1(map3,3);
    //关卡3响应信息模块
        //响应关卡2结算页面点击按钮“下一关”，跳转到关卡3and关闭关卡2
    connect(_level2finished,&Level1Finished::level1next,this,[=](){
        _level12->close();
        _level2finished->close();
        _level13->show();
        _level13->Level1again(map3);
        _level13->startRecord();
        _level13->initStep();
    });
        //响应选择关卡页面点击“关卡三”按钮，跳转到关卡3界面
    connect(_gamelevel1,&Gamelevel::toLevel3,this,[=](){
        _gamelevel1->hide();
        _level13->show();
        _level13->Level1again(map3);
        _level13->startRecord();
        _level13->initStep();
    });
        //响应关卡3“菜单”中“重新开始”页面，重置关卡3地图
    connect(_level13,&Level1::sLevel1again,this,[=](){
        _level13->Level1again(map3);
    });
        //响应关卡3“菜单”中“帮助”页面，跳出帮助
    connect(_level13,&Level1::tohelp,this,[=](){
        _help->show();
    });
        //响应关卡1“菜单”中“返回”页面，跳转关卡选择
    connect(_level13,&Level1::backtolevel,this,[=]()
    {
        _gamelevel1->show();
        _level13->close();
    });
        //响应关卡3“菜单”中“一键通关”页面，一键通关
    connect(_level13,&Level1::quickend,this,[=]()
    {
        _level13->Level1again(qmap3);
    });
    //创建关卡3的结算页面 _level3finished
    _level3finished=new Level1Finished(3);
        //响应捕捉关卡3通关条件发出的信号ok，显示结算页面and选择关卡页面关卡4得能
    connect(_level13,&Level1::ok,[=](int step,QTime *timeRecord){
        _level3finished->show();
        _level3finished->setText(step,timeRecord);
        _level13->endRecord();
        _gamelevel1->Level3Finished();
    });
        //响应关卡3结算页面点击按钮“返回”，跳转到选择关卡页面and关闭关卡3
    connect(_level3finished,&Level1Finished::backtogamelevel,this,[=](){
        _level13->close();
        _level3finished->close();
        _gamelevel1->show();
    });
        //响应关卡3结算页面点击按钮“再来一次”，关闭结算页面，并展示关卡3后重置地图
    connect(_level3finished,&Level1Finished::level1again,this,[=](){
        _level3finished->close();
        _level13->show();
        _level13->Level1again(map3);
    });



    //创建关卡4 _level14
    _level14=new Level1(map4,4);
    //关卡4响应信息模块
        //响应关卡3结算页面点击按钮“下一关”，跳转到关卡4and关闭关卡3
    connect(_level3finished,&Level1Finished::level1next,this,[=](){
        _level13->close();
        _level3finished->close();
        _level14->show();
        _level14->Level1again(map4);
        _level14->startRecord();
        _level14->initStep();
    });
        //响应选择关卡页面点击“关卡四”按钮，跳转到关卡4界面
    connect(_gamelevel1,&Gamelevel::toLevel4,this,[=](){
        _gamelevel1->hide();
        _level14->show();
        _level14->Level1again(map4);
        _level14->startRecord();
        _level14->initStep();
    });
        //响应关卡4“菜单”中“重新开始”页面，重置关卡4地图
    connect(_level14,&Level1::sLevel1again,this,[=](){
        _level14->Level1again(map4);
    });
        //响应关卡4“菜单”中“帮助”页面，跳出帮助
    connect(_level14,&Level1::tohelp,this,[=](){
        _help->show();
    });
        //响应关卡4“菜单”中“返回”页面，跳转关卡选择
    connect(_level14,&Level1::backtolevel,this,[=]()
    {
        _gamelevel1->show();
        _level14->close();
    });
        //响应关卡4“菜单”中“一键通关”页面，一键通关
    connect(_level14,&Level1::quickend,this,[=]()
    {
        _level14->Level1again(qmap4);
    });
    //创建关卡4的结算页面 _level4finished
    _level4finished=new Level1Finished(4);
        //响应捕捉关卡4通关条件发出的信号ok，显示结算页面and选择关卡页面关卡5得能
    connect(_level14,&Level1::ok,[=](int step,QTime *timeRecord){
        _level4finished->show();
        _level4finished->setText(step,timeRecord);
        _level14->endRecord();
        _gamelevel1->Level4Finished();
    });
        //响应关卡4结算页面点击按钮“返回”，跳转到选择关卡页面and关闭关卡4
    connect(_level4finished,&Level1Finished::backtogamelevel,this,[=](){
        _level14->close();
        _level4finished->close();
        _gamelevel1->show();
    });
        //响应关卡4结算页面点击按钮“再来一次”，关闭结算页面，并展示关卡4后重置地图
    connect(_level4finished,&Level1Finished::level1again,this,[=](){
        _level4finished->close();
        _level14->show();
        _level14->Level1again(map4);
    });



    //创建关卡5 _level15
    _level15=new Level1(map5,5);
    //关卡5响应信息模块
        //响应关卡4结算页面点击按钮“下一关”，跳转到关卡5and关闭关卡4
    connect(_level4finished,&Level1Finished::level1next,this,[=](){
        _level14->close();
        _level4finished->close();
        _level15->show();
        _level15->Level1again(map5);
        _level15->startRecord();
        _level15->initStep();
    });
        //响应选择关卡页面点击“关卡五”按钮，跳转到关卡5界面
    connect(_gamelevel1,&Gamelevel::toLevel5,this,[=](){
        _gamelevel1->hide();
        _level15->show();
        _level15->startRecord();
        _level15->initStep();
    });
        //响应关卡5“菜单”中“重新开始”页面，重置关卡5地图
    connect(_level15,&Level1::sLevel1again,this,[=](){
        _level15->Level1again(map5);
    });
        //响应关卡5“菜单”中“帮助”页面，跳出帮助
    connect(_level15,&Level1::tohelp,this,[=](){
        _help->show();
    });
        //响应关卡5“菜单”中“返回”页面，跳转关卡选择
    connect(_level15,&Level1::backtolevel,this,[=]()
    {
        _gamelevel1->show();
        _level15->close();
    });
        //响应关卡5“菜单”中“一键通关”页面，一键通关
    connect(_level15,&Level1::quickend,this,[=]()
    {
        _level15->Level1again(qmap5);
    });
    //创建关卡5的结算页面 _level5finished
    _level5finished=new Level1Finished(5);
        //响应捕捉关卡5通关条件发出的信号ok，显示结算页面and选择关卡页面关卡6得能
    connect(_level15,&Level1::ok,[=](int step,QTime *timeRecord){
        _level5finished->show();
        _level5finished->setText(step,timeRecord);
        _level15->endRecord();
        _gamelevel1->Level5Finished();
    });
        //响应关卡5结算页面点击按钮“返回”，跳转到选择关卡页面and关闭关卡5
    connect(_level5finished,&Level1Finished::backtogamelevel,this,[=](){
        _level15->close();
        _level5finished->close();
        _gamelevel1->show();
    });
        //响应关卡5结算页面点击按钮“再来一次”，关闭结算页面，并展示关卡5后重置地图
    connect(_level5finished,&Level1Finished::level1again,this,[=](){
        _level5finished->close();
        _level15->show();
        _level15->Level1again(map5);
    });


    //创建关卡6 _level16
    _level16=new Level1(map6,6);
    //关卡6响应信息模块
        //响应关卡5结算页面点击按钮“下一关”，跳转到关卡6and关闭关卡5
    connect(_level5finished,&Level1Finished::level1next,this,[=](){
        _level15->close();
        _level5finished->close();
        _level16->show();
        _level16->Level1again(map6);
        _level16->startRecord();
        _level16->initStep();
    });
        //响应选择关卡页面点击“关卡六”按钮，跳转到关卡6界面
    connect(_gamelevel1,&Gamelevel::toLevel6,this,[=](){
        _gamelevel1->hide();
        _level16->show();
        _level16->startRecord();
        _level16->initStep();
    });
        //响应关卡6“菜单”中“重新开始”页面，重置关卡6地图
    connect(_level16,&Level1::sLevel1again,this,[=](){
        _level16->Level1again(map6);
    });
        //响应关卡6“菜单”中“帮助”页面，跳出帮助
    connect(_level16,&Level1::tohelp,this,[=](){
        _help->show();
    });
        //响应关卡6“菜单”中“返回”页面，跳转关卡选择
    connect(_level16,&Level1::backtolevel,this,[=]()
    {
        _gamelevel1->show();
        _level16->close();
    });
        //响应关卡6“菜单”中“一键通关”页面，一键通关
    connect(_level16,&Level1::quickend,this,[=]()
    {
        _level16->Level1again(qmap6);
    });
    //创建关卡6的结算页面 _level6finished
    _level6finished=new Level1Finished(6);
        //响应捕捉关卡6通关条件发出的信号ok，显示结算页面and选择关卡页面关卡7得能
    connect(_level16,&Level1::ok,[=](int step,QTime *timeRecord){
        _level6finished->show();
        _level6finished->setText(step,timeRecord);
        _level16->endRecord();
        _gamelevel1->Level6Finished();
    });
        //响应关卡6结算页面点击按钮“返回”，跳转到选择关卡页面and关闭关卡6
    connect(_level6finished,&Level1Finished::backtogamelevel,this,[=](){
        _level16->close();
        _level6finished->close();
        _gamelevel1->show();
    });
        //响应关卡6结算页面点击按钮“再来一次”，关闭结算页面，并展示关卡6后重置地图
    connect(_level6finished,&Level1Finished::level1again,this,[=](){
        _level6finished->close();
        _level16->show();
        _level16->Level1again(map6);
    });



    //创建关卡7 _level17
    _level17=new Level1(map7,7);
    //关卡7响应信息模块
        //响应关卡6结算页面点击按钮“下一关”，跳转到关卡7and关闭关卡6
    connect(_level6finished,&Level1Finished::level1next,this,[=](){
        _level16->close();
        _level6finished->close();
        _level17->show();
        _level17->Level1again(map7);
        _level17->startRecord();
        _level17->initStep();
    });
        //响应选择关卡页面点击“关卡七”按钮，跳转到关卡7界面
    connect(_gamelevel1,&Gamelevel::toLevel7,this,[=](){
        _gamelevel1->hide();
        _level17->show();
        _level17->startRecord();
        _level17->initStep();
    });
        //响应关卡7“菜单”中“重新开始”页面，重置关卡7地图
    connect(_level17,&Level1::sLevel1again,this,[=](){
        _level17->Level1again(map7);
    });
        //响应关卡7“菜单”中“帮助”页面，跳出帮助
    connect(_level17,&Level1::tohelp,this,[=](){
        _help->show();
    });
        //响应关卡7“菜单”中“返回”页面，跳转关卡选择
    connect(_level17,&Level1::backtolevel,this,[=]()
    {
        _gamelevel1->show();
        _level17->close();
    });
        //响应关卡7“菜单”中“一键通关”页面，一键通关
    connect(_level17,&Level1::quickend,this,[=]()
    {
        _level17->Level1again(qmap7);
    });
    //创建关卡7的结算页面 _level7linished
    _level7finished=new Level1Finished(7);
        //响应捕捉关卡7通关条件发出的信号ok，显示结算页面and选择关卡页面关卡8得能
    connect(_level17,&Level1::ok,[=](int step,QTime *timeRecord){
        _level7finished->show();
        _level7finished->setText(step,timeRecord);
        _level17->endRecord();
        _gamelevel1->Level7Finished();
    });
        //响应关卡7结算页面点击按钮“返回”，跳转到选择关卡页面and关闭关卡7
    connect(_level7finished,&Level1Finished::backtogamelevel,this,[=](){
        _level17->close();
        _level7finished->close();
        _gamelevel1->show();
    });
        //响应关卡7结算页面点击按钮“再来一次”，关闭结算页面，并展示关卡7后重置地图
    connect(_level7finished,&Level1Finished::level1again,this,[=](){
        _level7finished->close();
        _level17->show();
        _level17->Level1again(map7);
    });


    //创建关卡8 _level18
    _level18=new Level1(map8,8);
    //关卡8响应信息模块
        //响应关卡7结算页面点击按钮“下一关”，跳转到关卡8and关闭关卡7
    connect(_level7finished,&Level1Finished::level1next,this,[=](){
        _level17->close();
        _level7finished->close();
        _level18->show();
        _level18->Level1again(map8);
        _level18->startRecord();
        _level18->initStep();
    });
        //响应选择关卡页面点击“关卡八”按钮，跳转到关卡8界面
    connect(_gamelevel1,&Gamelevel::toLevel8,this,[=](){
        _gamelevel1->hide();
        _level18->show();
        _level18->Level1again(map8);
        _level18->startRecord();
        _level18->initStep();
    });
        //响应关卡8“菜单”中“重新开始”页面，重置关卡8地图
    connect(_level18,&Level1::sLevel1again,this,[=](){
        _level18->Level1again(map8);
    });
        //响应关卡8“菜单”中“帮助”页面，跳出帮助
    connect(_level18,&Level1::tohelp,this,[=](){
        _help->show();
    });
        //响应关卡8“菜单”中“返回”页面，跳转关卡选择
    connect(_level18,&Level1::backtolevel,this,[=]()
    {
        _gamelevel1->show();
        _level18->close();
    });
        //响应关卡8“菜单”中“一键通关”页面，一键通关
    connect(_level18,&Level1::quickend,this,[=]()
    {
        _level18->Level1again(qmap8);
    });
    //创建关卡8的结算页面 _level8Flinished
    _level8finished=new Level1Finished(8);
        //响应捕捉关卡8通关条件发出的信号ok，显示结算页面
    connect(_level18,&Level1::ok,[=](int step,QTime *timeRecord){
        _level8finished->show();
        _level8finished->setText(step,timeRecord);
        _level18->endRecord();
        _gamelevel1->Level8Finished();
    });
        //响应关卡8结算页面点击按钮“返回”，跳转到选择关卡页面and关闭关卡8
    connect(_level8finished,&Level1Finished::backtogamelevel,this,[=](){
        _level18->close();
        _level8finished->close();
        _gamelevel1->show();
    });
        //响应关卡8结算页面点击按钮“再来一次”，关闭结算页面，并展示关卡8后重置地图
    connect(_level8finished,&Level1Finished::level1again,this,[=](){
        _level8finished->close();
        _level18->show();
        _level18->Level1again(map8);
    });

    _help=new Help;
    connect(_gamelevel1,&Gamelevel::tohelp,this,[=](){
       _help->show();
    });



    //创建关卡9 _level19
    _level19=new Level1(map9,9);
    //关卡9响应信息模块
        //响应关卡8结算页面点击按钮“下一关”，跳转到关卡9and关闭关卡8
    connect(_level8finished,&Level1Finished::level1next,this,[=](){
        _level18->close();
        _level8finished->close();
        _level19->show();
        _level19->Level1again(map9);
        _level19->startRecord();
        _level19->initStep();
    });
        //响应选择关卡页面点击“关卡九”按钮，跳转到关卡9界面
    connect(_gamelevel1,&Gamelevel::toLevel9,this,[=](){
        _gamelevel1->hide();
        _level19->show();
        _level19->Level1again(map9);
        _level19->startRecord();
        _level19->initStep();
    });
        //响应关卡9“菜单”中“重新开始”页面，重置关卡9地图
    connect(_level19,&Level1::sLevel1again,this,[=](){
        _level19->Level1again(map9);
    });
        //响应关卡9“菜单”中“帮助”页面，跳出帮助
    connect(_level19,&Level1::tohelp,this,[=](){
        _help->show();
    });
        //响应关卡9“菜单”中“返回”页面，跳转关卡选择
    connect(_level19,&Level1::backtolevel,this,[=]()
    {
        _gamelevel1->show();
        _level19->close();
    });
        //响应关卡9“菜单”中“一键通关”页面，一键通关
    connect(_level19,&Level1::quickend,this,[=]()
    {
        _level19->Level1again(qmap9);
    });
    //创建关卡9的结算页面 _level9Flinished
    _level9finished=new Level1Finished(9);
        //响应捕捉关卡9通关条件发出的信号ok，显示结算页面
    connect(_level19,&Level1::ok,[=](int step,QTime *timeRecord){
        _level9finished->show();
        _level9finished->setText(step,timeRecord);
        _level19->endRecord();
        _gamelevel1->Level9Finished();
    });
        //响应关卡9结算页面点击按钮“返回”，跳转到选择关卡页面and关闭关卡9
    connect(_level9finished,&Level1Finished::backtogamelevel,this,[=](){
        _level19->close();
        _level9finished->close();
        _gamelevel1->show();
    });
        //响应关卡9结算页面点击按钮“再来一次”，关闭结算页面，并展示关卡9后重置地图
    connect(_level9finished,&Level1Finished::level1again,this,[=](){
        _level9finished->close();
        _level19->show();
        _level19->Level1again(map9);
    });



    //创建关卡10 _level110
    _level110=new Level1(map10,10);
    //关卡10响应信息模块
        //响应关卡10结算页面点击按钮“下一关”，跳转到关卡10and关闭关卡9
    connect(_level9finished,&Level1Finished::level1next,this,[=](){
        _level19->close();
        _level9finished->close();
        _level110->show();
        _level110->Level1again(map10);
        _level110->startRecord();
        _level110->initStep();
    });
        //响应选择关卡页面点击“关卡十”按钮，跳转到关卡10界面
    connect(_gamelevel1,&Gamelevel::toLevel10,this,[=](){
        _gamelevel1->hide();
        _level110->show();
        _level110->Level1again(map10);
        _level110->startRecord();
        _level110->initStep();
    });
        //响应关卡10“菜单”中“重新开始”页面，重置关卡10地图
    connect(_level110,&Level1::sLevel1again,this,[=](){
        _level110->Level1again(map10);
    });
        //响应关卡10“菜单”中“帮助”页面，跳出帮助
    connect(_level110,&Level1::tohelp,this,[=](){
        _help->show();
    });
        //响应关卡10“菜单”中“返回”页面，跳转关卡选择
    connect(_level110,&Level1::backtolevel,this,[=]()
    {
        _gamelevel1->show();
        _level110->close();
    });
        //响应关卡10“菜单”中“一键通关”页面，一键通关
    connect(_level110,&Level1::quickend,this,[=]()
    {
        _level110->Level1again(qmap10);
    });
    //创建关卡10的结算页面 _level10Flinished
    _level10finished=new Level1Finished(10);
        //响应捕捉关卡10通关条件发出的信号ok，显示结算页面
    connect(_level110,&Level1::ok,[=](int step,QTime *timeRecord){
        _level10finished->show();
        _level10finished->setText(step,timeRecord);
        _level110->endRecord();
        _gamelevel1->Level10Finished();
    });
        //响应关卡10结算页面点击按钮“返回”，跳转到选择关卡页面and关闭关卡10
    connect(_level10finished,&Level1Finished::backtogamelevel,this,[=](){
        _level110->close();
        _level10finished->close();
        _gamelevel1->show();
    });
        //响应关卡10结算页面点击按钮“再来一次”，关闭结算页面，并展示关卡10后重置地图
    connect(_level10finished,&Level1Finished::level1again,this,[=](){
        _level10finished->close();
        _level110->show();
        _level110->Level1again(map10);
    });



    //创建关卡11 _level111
    _level111=new Level1(map11,11);
    //关卡11响应信息模块
        //响应关卡11结算页面点击按钮“下一关”，跳转到关卡11and关闭关卡10
    connect(_level10finished,&Level1Finished::level1next,this,[=](){
        _level110->close();
        _level10finished->close();
        _level111->show();
        _level111->Level1again(map11);
        _level111->startRecord();
        _level111->initStep();
    });
        //响应选择关卡页面点击“关卡十一”按钮，跳转到关卡11界面
    connect(_gamelevel1,&Gamelevel::toLevel11,this,[=](){
        _gamelevel1->hide();
        _level111->show();
        _level111->Level1again(map11);
        _level111->startRecord();
        _level111->initStep();
    });
        //响应关卡11“菜单”中“重新开始”页面，重置关卡11地图
    connect(_level111,&Level1::sLevel1again,this,[=](){
        _level111->Level1again(map11);
    });
        //响应关卡11“菜单”中“帮助”页面，跳出帮助
    connect(_level111,&Level1::tohelp,this,[=](){
        _help->show();
    });
        //响应关卡11“菜单”中“返回”页面，跳转关卡选择
    connect(_level111,&Level1::backtolevel,this,[=]()
    {
        _gamelevel1->show();
        _level111->close();
    });
        //响应关卡11“菜单”中“一键通关”页面，一键通关
    connect(_level111,&Level1::quickend,this,[=]()
    {
        _level111->Level1again(qmap11);
    });
    //创建关卡11的结算页面 _level11Flinished
    _level11finished=new Level1Finished(11);
        //响应捕捉关卡11通关条件发出的信号ok，显示结算页面
    connect(_level111,&Level1::ok,[=](int step,QTime *timeRecord){
        _level11finished->show();
        _level11finished->setText(step,timeRecord);
        _level111->endRecord();
        _gamelevel1->Level11Finished();
    });
        //响应关卡11结算页面点击按钮“返回”，跳转到选择关卡页面and关闭关卡11
    connect(_level11finished,&Level1Finished::backtogamelevel,this,[=](){
        _level111->close();
        _level11finished->close();
        _gamelevel1->show();
    });
        //响应关卡11结算页面点击按钮“再来一次”，关闭结算页面，并展示关卡11后重置地图
    connect(_level11finished,&Level1Finished::level1again,this,[=](){
        _level11finished->close();
        _level111->show();
        _level111->Level1again(map11);
    });



    //创建关卡12 _level112
    _level112=new Level1(map12,12);
    //关卡12响应信息模块
        //响应关卡11结算页面点击按钮“下一关”，跳转到关卡12and关闭关卡11
    connect(_level11finished,&Level1Finished::level1next,this,[=](){
        _level111->close();
        _level11finished->close();
        _level112->show();
        _level112->Level1again(map12);
        _level112->startRecord();
        _level112->initStep();
    });
        //响应选择关卡页面点击“关卡十二”按钮，跳转到关卡12界面
    connect(_gamelevel1,&Gamelevel::toLevel12,this,[=](){
        _gamelevel1->hide();
        _level112->show();
        _level112->Level1again(map12);
        _level112->startRecord();
        _level112->initStep();
    });
        //响应关卡12“菜单”中“重新开始”页面，重置关卡12地图
    connect(_level112,&Level1::sLevel1again,this,[=](){
        _level112->Level1again(map12);
    });
        //响应关卡12“菜单”中“帮助”页面，跳出帮助
    connect(_level112,&Level1::tohelp,this,[=](){
        _help->show();
    });
        //响应关卡12“菜单”中“返回”页面，跳转关卡选择
    connect(_level112,&Level1::backtolevel,this,[=]()
    {
        _gamelevel1->show();
        _level112->close();
    });
        //响应关卡12“菜单”中“一键通关”页面，一键通关
    connect(_level112,&Level1::quickend,this,[=]()
    {
        _level112->Level1again(qmap12);
    });
    //创建关卡12的结算页面 _level12Flinished
    _level12finished=new AllFinished;
        //响应捕捉关卡12通关条件发出的信号ok，显示结算页面
    connect(_level112,&Level1::ok,[=](int step,QTime *timeRecord){
        _level12finished->show();
        _level12finished->setText(step,timeRecord);
        _level112->endRecord();
    });
        //响应关卡12结算页面点击按钮“返回”，跳转到选择关卡页面and关闭关卡12
    connect(_level12finished,&AllFinished::backtogamelevel,this,[=](){
        _level112->close();
        _level12finished->close();
        _gamelevel1->show();
    });
        //响应关卡12结算页面点击按钮“再来一次”，关闭结算页面，并展示关卡12后重置地图
    connect(_level12finished,&AllFinished::level1again,this,[=](){
        _level12finished->close();
        _level112->show();
        _level112->Level1again(map12);
    });



    //创建自定义关卡页面并响应关卡选择页面“自定义关卡”页面
    _custom=new Custom;
    connect(_gamelevel1,&Gamelevel::tocustom,this,[=]()
    {
        _custom->show();
        _custom->cleartext();
    });
    //响应点击“点击创建”按钮，保存地图
    connect(_custom,&Custom::create,this,[=](){
        _custom->setmap(tmap);
    });
    _tlevel=new Level1(tmap,0);
    //响应点击“进入游戏”按钮，进入自定义的游戏界面
    connect(_custom,&Custom::toclevel,this,[=](){
        _gamelevel1->hide();
        _custom->hide();
        _tlevel->show();
        _tlevel->Level1again(tmap);
        _tlevel->startRecord();
    });
        //响应自定义关卡“菜单”中“重新开始”页面，重置自定义关卡地图
    connect(_tlevel,&Level1::sLevel1again,this,[=](){
        _tlevel->Level1again(tmap);
    });
        //响应自定义关卡“菜单”中“帮助”页面，跳出帮助
    connect(_tlevel,&Level1::tohelp,this,[=](){
        _help->show();
    });
        //响应自定义关卡“菜单”中“返回”页面，跳转关卡选择
    connect(_tlevel,&Level1::backtolevel,this,[=]()
    {
        _gamelevel1->show();
        _tlevel->close();
    });
    //创建自定义关卡的结算页面 _tlevelFlinished
    _tlevelfinished=new Level1Finished(0);
        //响应捕捉自定义通关条件发出的信号ok，显示结算页面(结算页面“下一关”失能）
    connect(_tlevel,&Level1::ok,[=](int step,QTime *timeRecord){
        _tlevelfinished->show();
        _tlevelfinished->setbtn();
        _tlevelfinished->setText(step,timeRecord);
        _tlevel->endRecord();
    });
        //响应自定义结算页面点击按钮“返回”，跳转到选择关卡页面and关闭自定义关卡
    connect(_tlevelfinished,&Level1Finished::backtogamelevel,this,[=](){
        _tlevel->close();
        _tlevelfinished->close();
        _gamelevel1->show();
    });
        //响应自定义结算页面点击按钮“再来一次”，关闭结算页面，并展示自定义关卡后重置地图
    connect(_tlevelfinished,&Level1Finished::level1again,this,[=](){
        _tlevelfinished->close();
        _tlevel->show();
        _tlevel->Level1again(tmap);
    });

}

Start::~Start()
{
    delete ui;
}



void Start::on_btnstart_clicked()
{
    this->hide();
    _gamelevel1->show();
}

void Start::on_help_triggered()
{
    _help->show();
}

void Start::on_start_triggered()
{
    this->hide();
    _gamelevel1->show();
}

void Start::on_settings_triggered()
{
    _music->show();
}
