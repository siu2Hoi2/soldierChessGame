#ifndef CHESS_H
#define CHESS_H
#include <QPoint>
#include <QString>
#include <QPixmap>
#include <QRect>
#include <QLineEdit>

class Chess
{
public:
    Chess();
    Chess(int x,int y);    //初始化
    void setPosition(int x,int y); //修改位置

public:
    QPixmap pixChess;  //棋子图标
    int cX;    //x坐标
    int cY;    //y坐标
    QRect cRect;    //棋子边框，用于检测碰撞和绘图
    QLineEdit lifeShow;    //显示生命值
    int life;      //棋子生命值
    bool isArrive=false;    //当前棋子是否到达


};

#endif // CHESS_H
