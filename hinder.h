#ifndef HINDER_H
#define HINDER_H
#include "config.h"
#include <QPixmap>
#include <QRect>


class hinder
{
public:
    hinder();
    void setPosition(int x,int y);

    QPixmap pixHind;
    int hX;
    int hY;
    QRect hRect;



};

#endif // HINDER_H
