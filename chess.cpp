#include "chess.h"
#include "widget.h"
#include "config.h"
#include <QString>


Chess::Chess()
{
    pixChess.load(":res/chess.png");

    cX=CELL_BEGIN_X;
    cY=CELL_BEGIN_Y;

    cRect.setWidth(CELL_SIZE-2);
    cRect.setHeight(CELL_SIZE-2);
    cRect.moveTo(cX,cY);

    life=1;  //默认生命值

    lifeShow.setText(QString::number(life));
    lifeShow.setAlignment(Qt::AlignHCenter);
    lifeShow.setReadOnly(true);
    lifeShow.setGeometry(cX+3,cY-18,25,18);
    lifeShow.setFont(QFont("Timers" ,9, QFont::Bold));

    lifeShow.show();
}

Chess::Chess(int x, int y)
{
    cX=x;
    cY=y;

    life=1;  //默认生命值
}

void Chess::setPosition(int x, int y)
{
    cX=x;
    cY=y;

    //棋子位置边缘检测
    if(cX>=CELL_BEGIN_X+(CELL_NUM_N)*CELL_SIZE)
        cX=CELL_BEGIN_X+CELL_NUM_N*CELL_SIZE-this->cRect.width();
    if(cX<=CELL_BEGIN_X)
        cX=CELL_BEGIN_X;

    if(cY>=CELL_BEGIN_Y+(CELL_NUM_M)*CELL_SIZE)
        cY=CELL_BEGIN_Y+CELL_NUM_M*CELL_SIZE-this->cRect.height();
    if(cY<=CELL_BEGIN_Y)
        cY=CELL_BEGIN_Y;

    cRect.moveTo(cX,cY);

    lifeShow.setText(QString::number(life));
    lifeShow.setGeometry(cX+3,cY-18,25,18);

}


