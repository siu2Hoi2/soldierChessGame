#ifndef BULLETPNT_H
#define BULLETPNT_H
#include "config.h"

class bulletPnt
{
public:
    bulletPnt();

    //更新位置
    void updatePosition();

    //重置位置
    void resetPosition();

    //子弹坐标
    int x;
    int y;
    //发射方向。基于圆的参数方程
    int direction;

    //子弹速度
    int bSpeed;

    //子弹射程
    int rad;

    //起点坐标
    int bgx;
    int bgy;

};

#endif // BULLETPNT_H
