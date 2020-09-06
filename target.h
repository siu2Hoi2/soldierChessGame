#ifndef TARGET_H
#define TARGET_H
#include "config.h"
#include <QPixmap>

class target
{
public:
    target();
    void setPosition(int x,int y);

    QPixmap pixTar;
    int tx;
    int ty;

    int life;
};

#endif // TARGET_H
