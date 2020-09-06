#include "widget.h"
#include "ui_widget.h"
#include <QIcon>
#include <QPixmap>
#include <QMouseEvent>
#include <algorithm>
#include <vector>
#include <random>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>

#include <QLabel>
//#include <windows.h>

using namespace std;


Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    this->initWidget();
    ui->setupUi(this);

    timer= new QTimer(this);   //初始化定时器
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));   //计时器用来触发更新
    connect(timer,&QTimer::timeout,[=]()
    {
        updateView();
    });
    timer->start(20);   //更新画布。刷新时间太快CPU占用会过高，20ms比较适宜

    //重新开始按钮
    QPushButton *reset=new QPushButton(this);
    reset->setText("重新开始");
    reset->move(CELL_BEGIN_X+CELL_SIZE*CELL_NUM_N+45,50);
    connect(reset,&QPushButton::clicked,this,&Widget::initWidget);
    //退出按钮
    QPushButton *exit=new QPushButton(this);
    exit->setText("退出");
    exit->move(CELL_BEGIN_X+CELL_SIZE*CELL_NUM_N+160,50);
    connect(exit,&QPushButton::clicked,[=](){
        int button;
        button = QMessageBox::question(this, tr("退出游戏"),
                                       QString(tr("确认退出游戏?")),
                                       QMessageBox::Yes | QMessageBox::No);
        if(button==QMessageBox::Yes)
        {
            this->close();
        }
    });

    //当前棋子编号
    QLabel *label=new QLabel(this);
    label->setText("当前棋子编号：");
    label->setGeometry(CELL_BEGIN_X+CELL_SIZE*CELL_NUM_N+45,100,150,40);
    label->show();

    id=new QLineEdit(this);
    id->setText(QString("null"));
    id->setGeometry(CELL_BEGIN_X+CELL_SIZE*CELL_NUM_N+160,110,40,25);
    id->setReadOnly(true);
    id->show();


    //当前棋子生命值
    QLabel *label2=new QLabel(this);
    label2->setText("当前棋子生命值：");
    label2->setGeometry(CELL_BEGIN_X+CELL_SIZE*CELL_NUM_N+45,150,150,40);
    label2->show();

    nowLife=new QLineEdit(this);
    nowLife->setText(QString("null"));
    nowLife->setGeometry(CELL_BEGIN_X+CELL_SIZE*CELL_NUM_N+160,160,40,25);
    nowLife->setReadOnly(true);
    nowLife->show();

    //当前棋子位置
    QLabel *label3=new QLabel(this);
    label3->setText("当前棋子位置：");
    label3->setGeometry(CELL_BEGIN_X+CELL_SIZE*CELL_NUM_N+45,200,150,40);
    label3->show();

    location=new QLineEdit(this);
    location->setText(QString("null"));
    location->setGeometry(CELL_BEGIN_X+CELL_SIZE*CELL_NUM_N+160,210,100,25);
    location->setReadOnly(true);
    location->show();
}


void Widget::initWidget()
{

    this->setFixedSize(WINDOWS_X,WINDOWS_Y);
    this->setWindowTitle("兵棋进攻 v1.6");
    this->setWindowIcon(QIcon(":/res/title.ico"));
    for(int i=0;i<5;i++)
    {
        mChess[i].lifeShow.setParent(this);
    }

    srand((unsigned int)time(NULL));   //以时间为随机数种子

    //构造0-CELL_NUM_M-1的不重复的随机数
    vector<int> temp;
    vector<int> temp2;
    for(int i=0;i<CELL_NUM_M;i++)
    {
        temp.push_back(i);
    }

    random_shuffle(temp.begin(),temp.end());
    //随机生命值
    int randomLife=(rand() % 10) + 1;

    //初始化棋子
    for(int i=0;i<5;i++)
    {
        //生成随机坐标
        int randomX=(CELL_NUM_N-1)*CELL_SIZE+CELL_BEGIN_X;
        int randomY=temp[i]*CELL_SIZE+CELL_BEGIN_Y;
        //设置棋子坐标
        mChess[i].setPosition(randomX,randomY);
        //设置棋子生命值
        mChess[i].life=randomLife;
        //刷新棋子生命值
        mChess[i].lifeShow.setText(QString::number(mChess[i].life));
        //刷新生命值背景色
        mChess[i].lifeShow.setStyleSheet("background-color:rgba(225,225,225,1)");
        mChess[i].lifeShow.show();
        //设置棋子图标
        mChess[i].pixChess.load(":res/chess.png");
        //刷新
        update();
    }


    temp.clear();
    for(int i=10;i<=CELL_NUM_N-3;i++)
    {
        temp.push_back(i);
    }

    random_shuffle(temp.begin(),temp.end());

    temp2.clear();
    for(int i=0;i<=CELL_NUM_M-4;i++)
    {
        temp2.push_back(i);
    }

    random_shuffle(temp2.begin(),temp2.end());

    //初始化障碍
    for(int i=0;i<6;i++)
    {
        int randomX=temp[i]*CELL_SIZE+CELL_BEGIN_X;
        int randomY=temp2[i]*CELL_SIZE+CELL_BEGIN_Y;
        mHinder[i].setPosition(randomX,randomY);
    }

    temp.clear();
    for(int i=3;i<=7;i++)
    {
        temp.push_back(i);
    }
    random_shuffle(temp.begin(),temp.end());

    temp2.clear();
    for(int i=0;i<=17;i++)
    {
        temp2.push_back(i);
    }
    random_shuffle(temp2.begin(),temp2.end());

    //初始化防守点
    for(int i=0;i<5;i++)
    {
        grd[i].setPosition(CELL_SIZE*temp[i]+CELL_BEGIN_X,CELL_SIZE*temp2[i]+CELL_BEGIN_Y);
    }

    for (int j=0;j<=5;j++)
    {
        for(int i=0; i<BUL_NUM;i++)
        {
            grd[j].bulletPnt[i].bgx=grd[j].bulletPnt[i].x;
            grd[j].bulletPnt[i].bgy=grd[j].bulletPnt[i].y;
        }
    }

    //初始化进攻目标区
    temp.clear();
    for (int y=0;y<CELL_NUM_M;y++)
    {
        temp.push_back(y);
    }
    random_shuffle(temp.begin(),temp.end());
    tar.setPosition(CELL_BEGIN_X,CELL_BEGIN_Y+CELL_SIZE*temp[0]);
}


Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent *)
{

    int endX=CELL_BEGIN_X+CELL_SIZE*CELL_NUM_N;  //x轴终止位置
    int endY=CELL_BEGIN_Y+CELL_SIZE*CELL_NUM_M;  //y轴终止位置

    QPainter *paint=new QPainter(this);

    //设置棋盘背景图
    QPixmap pix;
    pix.load(":res/backgrounds.png");
    paint->drawPixmap(CELL_BEGIN_X,CELL_BEGIN_Y,endX-CELL_BEGIN_X,endY-CELL_BEGIN_Y,pix);

    //设置画笔
    paint->setPen(QPen(Qt::black,3,Qt::SolidLine));
    paint->setBrush(QBrush(Qt::white,Qt::SolidPattern));

    //画横线
    for(int i=0;i<=CELL_NUM_M;i++)
    {
        paint->drawLine(CELL_BEGIN_X,CELL_BEGIN_Y+CELL_SIZE*i,endX,CELL_BEGIN_Y+CELL_SIZE*i);
    }

    //画竖线
    for(int i=0;i<=CELL_NUM_N;i++)
    {
        paint->drawLine(CELL_BEGIN_X+CELL_SIZE*i,CELL_BEGIN_Y,CELL_BEGIN_X+CELL_SIZE*i,endY);
    }

    //画棋子
    for(int i=0;i<5;i++)
    {
        paint->drawPixmap(mChess[i].cX+4,mChess[i].cY+2,CELL_SIZE-8,CELL_SIZE-4,mChess[i].pixChess);
        for (int k=0;k<5;k++)
        {
            for(int j=0;j<BUL_NUM;j++)
            {
                if((abs(mChess[i].cX-grd[k].bulletPnt[j].x)==0)
                        &&(abs(mChess[i].cY-grd[k].bulletPnt[j].y)==0)
                        &&(mChess[i].life>0))
                {
                    mChess[i].life--;
                }
            }
        }
        // 检查棋子是否达到目的点
        if((abs(tar.tx-mChess[i].cX)<10)&&(abs(tar.ty-mChess[i].cY)<10))
        {
            mChess[i].isArrive=true;
        }

    }

    //画路障
    for(int i=0;i<6;i++)
    {
        paint->drawPixmap(mHinder[i].hX+2,mHinder[i].hY,mHinder[i].hRect.width(),
                          mHinder[i].hRect.height(),mHinder[i].pixHind);
    }

    //画防守点
    for(int i=0;i<5;i++)
    paint->drawPixmap(grd[i].gX+2,grd[i].gY+2,grd[i].gRect.width(),grd[i].gRect.height(),grd[i].pixGrd);

    for (int j=0;j<5;j++)
    {
        for(int i=0;i<BUL_NUM;i++)
        {
            paint->setPen(QPen(Qt::blue,10,Qt::SolidLine));
            paint->drawPoint(grd[j].bulletPnt[i].x+CELL_SIZE*0.5,grd[j].bulletPnt[i].y+CELL_SIZE*0.5);
        }
    }

    //画目标点
    paint->drawPixmap(tar.tx+2,tar.ty+2,CELL_SIZE-4,CELL_SIZE-4,tar.pixTar);


}

void Widget::mousePressEvent(QMouseEvent *event)
{
    select=this->whichSelect(event->x(),event->y());
    //qDebug()<<"select="<<select;
    if (select<5)
    {

        int devX=0,devY=0,xx=0,yy=0;  //绘图偏移量
        bool hind=true;               //障碍物检测
        bool isLean=false;            //斜走检测
        bool isDead=(mChess[select].life<=0);  //生命值检测
        for(int i=0;i<5;i++)
        {
            hind=hind&&(!(mHinder[i].hRect.intersects(QRect(event->x(),event->y(),CELL_SIZE * 0.3,CELL_SIZE * 0.3))));
        }

        if(!isDead)
        {
            devX=mChess[select].cRect.width()*0.5;
            devY=mChess[select].cRect.height()*0.5;

            xx=event->x()-devX;
            yy=event->y()-devY;

            xx=(xx/CELL_SIZE)*CELL_SIZE+CELL_SIZE*0.5+5;
            yy=(yy/CELL_SIZE)*CELL_SIZE+CELL_SIZE*0.5+5;

            //检测是否斜走
            isLean=(abs(xx-mChess[select].cX)>0?true:false)&&(abs(yy-mChess[select].cY)>0?true:false);

            if (hind&&!isLean)
            {
                mChess[select].setPosition(xx,yy);
            }
        }

        //更新生命值
        mChess[select].lifeShow.setText(QString::number(mChess[select].life));
        //当棋子生命耗尽时,生命值设为红色
        if(mChess[select].life==0)
        {
            mChess[select].lifeShow.setStyleSheet("background-color:rgba(225,106,106,1)");
            mChess[select].pixChess.load(":res/delete_chess.jpg");
            update();
            mChess[select].lifeShow.hide();
            select=999;
        }
    }

    if(isWin())
    {
        QMessageBox msg(QMessageBox::Information,
                        "恭喜，你赢了！","还玩吗？",
                        QMessageBox::Yes|QMessageBox::No);

        int w=msg.exec();
        if(w==QMessageBox::Yes)
        {
            this->initWidget();
        }
        else if (w==QMessageBox::No)
        {
            this->close();
        }
    }

    if(isLose())
    {
        QMessageBox msg(QMessageBox::Information,
                        "很遗憾，你输了！","还玩吗？",
                        QMessageBox::Yes|QMessageBox::No);

        int w=msg.exec();
        if(w==QMessageBox::Yes)
        {
            this->initWidget();
        }
        else if (w==QMessageBox::No)
        {
            this->close();
        }
    }


    //同步信息显示控件
    if(select==999)
        id->setText(QString("null"));
    else
        id->setText(QString::number(select));

    if(select==999)
        nowLife->setText(QString("null"));
    else
        nowLife->setText(QString::number(mChess[select].life));



    if(select==999)
        location->setText(QString("null"));
    else
        {
            QString str=QString::number(mChess[select].cX)+QString(",")+QString::number(mChess[select].cY);
            location->setText(str);
        }

    // 检查棋子是否达到目的点
    if(select<6)
    {
        if((abs(tar.tx-mChess[select].cX)<10)&&(abs(tar.ty-mChess[select].cY)<10))
        {
            tar.life--;
        }
    }

    qDebug()<<"目标点生命值："<<tar.life;

}


void Widget::updateView()
{
    //棋子是否进入攻击区域
    bool isClose=false;
    for(int chCount=0;chCount<5;chCount++)
    {
        if(mChess[chCount].cX<CELL_BEGIN_X+CELL_SIZE*CELL_NUM_N*0.5)
        {
            isClose=true;
            break;
        }
    }

    if(isClose)
    {
        for (int j=0;j<5;j++)
        {
            for(int i=0;i<BUL_NUM;i++)
            {
                grd[j].bulletPnt[i].updatePosition();
            }
        }
    }
    else
    {
        for (int j=0;j<5;j++)
        {
            for(int i=0;i<BUL_NUM;i++)
            {
                grd[j].bulletPnt[i].resetPosition();
            }
        }
    }
}


bool Widget::isWin()
{
    bool win=false;
    for (int i=0;i<5;i++)
    {
        if(mChess[i].isArrive==true)
        {
            win=true;
            break;
        }

    }
    return win;
}


int Widget::whichSelect(int mx, int my)
{
    int select=999;
    for(int i=0;i<5;i++)
    {
        // 未达到目标点且未死亡的棋子可被选中
        if(!mChess[i].isArrive)
        {
            if(abs(mChess[i].cX+CELL_SIZE*0.5-mx)<CELL_SIZE*1.5&&abs(mChess[i].cY+CELL_SIZE*0.5-my)<CELL_SIZE*1.5)
            {
                select=i;
                break;
            }
        }
    }

    return select;
}


bool Widget::isLose()
{
    int sum=0;
    for (int i=0;i<5;i++)
    {
        sum=sum+mChess[i].life;
    }

    if(sum==0)
        return true;
    else
        return false;
}
