#include "guard.h"


guard::guard()
{
    gX=0;
    gY=0;

    pixGrd.load(":res/guard.png");

    gRect.setWidth(CELL_SIZE-4);
    gRect.setHeight(CELL_SIZE-4);
    gRect.moveTo(gX,gY);

    for (int i=0;i<BUL_NUM;i++)
    {
        bulletPnt[i].x=gX;
        bulletPnt[i].y=gY;
    }

}

void guard::setPosition(int x,int y)
{
    gX=x;
    gY=y;

    for(int i=0;i<BUL_NUM;i++)
    {
        this->bulletPnt[i].x=x;
        this->bulletPnt[i].y=y;
    }

    gRect.moveTo(gX,gY);
}


