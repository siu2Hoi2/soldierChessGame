#ifndef GUARD_H
#define GUARD_H
#include "config.h"
#include <QPixmap>
#include <QRect>
#include "bulletpnt.h"


class guard
{
public:
    guard();

    void setPosition(int x,int y);

    QPixmap pixGrd;
    int gX;
    int gY;
    QRect gRect;

    //弹匣
    bulletPnt bulletPnt[BUL_NUM];

};

#endif // GUARD_H
