#include "hinder.h"

hinder::hinder()
{
    hX=0;
    hY=0;

    pixHind.load(":res/hinder.png");

    hRect.setWidth(CELL_SIZE*2);
    hRect.setHeight(CELL_SIZE*4);
    hRect.moveTo(hX,hY);

}

void hinder::setPosition(int x, int y)
{
    hX=x;
    hY=y;

    hRect.moveTo(hX,hY);
}
