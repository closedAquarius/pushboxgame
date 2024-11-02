#include "boxgame.h"
#include <iostream>

BoxGame::BoxGame()
{

}

void BoxGame::InitMap(int (*maps)[8])
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            map[i][j]=maps[i][j];
            //初始化地图容器里的地图
            map1[i][j]=maps[i][j];
            map2[i][j]=maps[i][j];
            map3[i][j]=maps[i][j];
        }
    }
    initmaps();
}

void BoxGame::drawMap(QPainter *draw)//绘图机制
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            QString imgURL;//根据数组中对应的数字来赋值
            /*
             * 0-路
             * 1-强
             * 3-目标地
             * 4-箱子
             * 5|8-人物
             * 7-完成的箱子
             */
            switch (map[i][j])
            {
            case 0:
                break;
            case 1:
                imgURL=":/image/wall.png";
                break;
            case 3:
                imgURL=":/image/home.png";
                break;
            case 4:
                imgURL=":/image/box.png";
                break;
            case 5:
            case 8:
                imgURL=":/image/smallp.png";
                break;
            case 7:
                imgURL=":/image/boxfinished.png";
                break;
            case 9:
                break;
            }
            QImage img;
            img.load(imgURL);
            draw->drawImage(QRect(j*img.width(),i*img.height(),img.width(),img.height()),img);
        }

    }
}

void BoxGame::keyDown(QKeyEvent *event)//按键处理机制
{
    int i = getRow();
    int j = getCols();
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            maps.front()[i][j]=map[i][j];
        }
    }
    int (*tmap)[8]=maps.front();
    maps.pop_front();
    maps.push_back(tmap);
    switch (event->key())
    {
    case Qt::Key_Up:
    case Qt::Key_W:
        if (map[i - 1][j] == 0 || map[i - 1][j] == 3)
        {
            map[i][j] -= 5;
            map[i - 1][j] += 5;
        }
        if (map[i - 1][j] == 4 || map[i - 1][j] == 7)
        {
            if (map[i - 2][j] == 0 || map[i - 2][j] == 3)
            {
                map[i][j] -= 5;
                map[i - 1][j] += 1;
                map[i - 2][j] += 4;
            }
        }
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        if (map[i + 1][j] == 0 || map[i + 1][j] == 3)
        {
            map[i][j] -= 5;
            map[i + 1][j] += 5;
        }
        if (map[i + 1][j] == 4 || map[i+ 1][j] == 7)
        {
            if (map[i + 2][j] == 0 || map[i + 2][j] == 3)
            {
                map[i][j] -= 5;
                map[i + 1][j] += 1;
                map[i + 2][j] += 4;
            }
        }
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        if (map[i][j-1] == 0 || map[i][j-1] == 3)
        {
            map[i][j] -= 5;
            map[i][j-1] += 5;
        }
        if (map[i][j-1] == 4 || map[i][j-1] == 7)
        {
            if (map[i][j-2] == 0 || map[i][j-2] == 3)
            {
                map[i][j] -= 5;
                map[i][j-1] += 1;
                map[i][j-2] += 4;
            }
        }
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        if (map[i][j + 1] == 0 || map[i][j + 1] == 3)
        {
            map[i][j] -= 5;
            map[i][j + 1] += 5;
        }
        if (map[i][j + 1] == 4 || map[i][j + 1] == 7)
        {
            if (map[i][j + 2] == 0 || map[i][j + 2] == 3)
            {
                map[i][j] -= 5;
                map[i][j + 1] += 1;
                map[i][j + 2] += 4;
            }
        }
        break;
    default:
        break;
    }

}

int BoxGame::getRow()//返回人物横坐标
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (map[i][j] == 5 || map[i][j] == 8)
            {
                return i;
            }
        }
    }
    return -1;
}

int BoxGame::getCols()//返回任务纵坐标
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (map[i][j] == 5 || map[i][j] == 8)
            {
                return j;
            }
        }
    }
    return -1;
}

bool BoxGame::gameOver()//检测游戏是否成功
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (map[i][j] == 4)
            {
                return false;
            }
        }
    }
    return true;
}

void BoxGame::initmaps()//初始化容器
{
    maps.clear();
    maps.push_back(map1);
    maps.push_back(map2);
    maps.push_back(map3);
}

//返回操作
void BoxGame::back()
{
    int (*tmap)[8]=maps.back();
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            map[i][j]=tmap[i][j];
        }
    }
    maps.pop_back();
    maps.push_front(tmap);
}
//只需要略微出手，就可以使墙消失
void BoxGame::dewall()
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(map[i][j]==1||map[i][j]==9)
            {
                map[i][j]=0;
            }
        }
    }
}
