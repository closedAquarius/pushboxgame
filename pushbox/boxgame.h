#ifndef BOXGAME_H
#define BOXGAME_H
#include <QPainter>
#include <QEvent>
#include <QKeyEvent>
#include <memory.h>
#include <QString>
#include <QImage>
#include <QRect>
#include <QPixmap>
#include <QVector>


class BoxGame
{
public:
    BoxGame();
    ~BoxGame();
    void InitMap(int (*maps)[8]);
    void drawMap(QPainter *draw);//绘图机制
    void keyDown(QKeyEvent *eventmint);//按键处理机制
    int getRow();
    int getCols();
    bool gameOver();
    void initmaps();
    void back();
    void dewall();
protected:
    int map1[8][8];
    int map2[8][8];
    int map3[8][8];
    int map[8][8];
    QVector<int(*)[8]> maps;
};

#endif // BOXGAME_H
