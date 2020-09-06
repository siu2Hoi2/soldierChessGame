#include "target.h"

target::target()
{
    tx=0;
    ty=0;

    pixTar.load(":res/target.png");

    life=5;

}

void target::setPosition(int x,int y)
{
    tx=x;
    ty=y;

}

