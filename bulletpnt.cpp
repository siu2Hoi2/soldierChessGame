#include "bulletpnt.h"
#include <iostream>
#include <algorithm>
#include <math.h>
#include <time.h>


bulletPnt::bulletPnt()
{
    bSpeed=5;

    //子弹坐标
    this->x=0;
    this->y=0;

    bgx=0;
    bgy=0;

    int dir[270];
    for(int i=0;i<270;i++)
    {
        dir[i]=90+i;
    }

    //srand((unsigned int)time(NULL));

    std::random_shuffle(dir,dir+270);

    direction=dir[0];

    rad=200;

}

void bulletPnt::updatePosition()
{

    this->y=this->y+sin(direction*3.1415/180)*bSpeed;

    this->x=this->x+cos(direction*3.1415/180)*bSpeed;

    if(sqrt(pow((x-bgx),2)+pow((y-bgy),2))>rad)
    //if((abs(this->x-this->bgx)>this->rad))
    {
        x=bgx;
        y=bgy;

    }

    if(this->x<CELL_BEGIN_X)
    {
        x=bgx;
        y=bgy;
    }

    if(this->x>CELL_BEGIN_X+CELL_SIZE*CELL_NUM_N)
    {
        x=bgx;
        y=bgy;
    }

    if(this->y<CELL_BEGIN_Y)
    {
        x=bgx;
        y=bgy;
    }

    if(this->y>CELL_BEGIN_Y+(CELL_SIZE-1)*CELL_NUM_M)
    {
        x=bgx;
        y=bgy;
    }

}


void bulletPnt::resetPosition()
{
    x=bgx;
    y=bgy;
}
