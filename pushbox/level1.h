#ifndef LEVEL1_H
#define LEVEL1_H

#include "boxgame.h"
#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include "notice.h"
class BoxGame;
class Notice;

namespace Ui {
class Level1;
}

class Level1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Level1(int (*map)[8],int a,QWidget *parent = nullptr);
    ~Level1();
    void keyPressEvent(QKeyEvent* event);
    void paintEvent(QPaintEvent* event);
    void Level1again(int (*map)[8]);
    void initTime();
    void updateTime();
    void startRecord();
    void endRecord();
    void initStep();
    //自定义关卡按钮失能
    void setbtn();



signals:
    void ok(int step,QTime *timeRecord);
    void sLevel1again();
    void tohelp();
    void backtolevel();
    void quickend();

private:
    Ui::Level1 *ui;
    QPainter *qmap;
    BoxGame *box;
    QTimer *timer;
    QTime *timeRecord;
    int step;
    QString sstep;
    int backstep;
    Notice *_notice;

public:


private slots:
    void on_restart_triggered();
    void on_back_triggered();
    void on_help_triggered();
    void on_backtolevel_triggered();
    void on_action1_triggered();
};

#endif // LEVEL1_H
