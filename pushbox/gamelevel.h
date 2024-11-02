#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <QMainWindow>
#include <QPainter>

namespace Ui {
class Gamelevel;
}

class Gamelevel : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gamelevel(QWidget *parent = nullptr);
    ~Gamelevel();
    //十二个关卡结算页面
    void Level1Finished();
    void Level2Finished();
    void Level3Finished();
    void Level4Finished();
    void Level5Finished();
    void Level6Finished();
    void Level7Finished();
    void Level8Finished();
    void Level9Finished();
    void Level10Finished();
    void Level11Finished();
    void Level12Finished();

signals:
    //十二个跳转游戏关卡页面的发出信号
    void toLevel1();
    void toLevel2();
    void toLevel3();
    void toLevel4();
    void toLevel5();
    void toLevel6();
    void toLevel7();
    void toLevel8();
    void toLevel9();
    void toLevel10();
    void toLevel11();
    void toLevel12();
    //跳转帮助页面的发出信号
    void tohelp();
    void tocustom();
    void tosettings();

private slots:
    //十二个响应点击关卡1~8
    void on_choose1_clicked();
    void on_choose2_clicked();

    void on_choose3_clicked();

    void on_choose4_clicked();

    void on_choose5_clicked();

    void on_choose6_clicked();

    void on_choose7_clicked();

    void on_choose8_clicked();

    void on_help_triggered();

    void on_start_triggered();

    void on_choose9_clicked();

    void on_choose10_clicked();

    void on_choose11_clicked();

    void on_choose12_clicked();

    void on_custom_triggered();

    void on_settings_triggered();

public:
    Ui::Gamelevel *ui;

};

#endif // GAMELEVEL_H
