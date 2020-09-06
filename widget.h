#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QGraphicsItem>
#include "chess.h"
#include "hinder.h"
#include "config.h"
#include <QMouseEvent>
#include "guard.h"
#include "bulletpnt.h"
#include "target.h"

#include <QTime>
#include <QTimer>

#include <QCloseEvent>

namespace Ui
{
class Widget;
}


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);

    void initWidget();   //初始化函数

    void paintEvent(QPaintEvent *);   //绘图函数

    void mousePressEvent(QMouseEvent *);   //鼠标点击事件

    void updateView();  //判断是否发起进攻

    bool isWin();

    bool isLose();

    int whichSelect(int mx,int my);  //根据鼠标坐标确定选中的棋子

    int select=999;  //选中的棋子编号

    QLineEdit *id;   //显示棋子id编号
    QLineEdit *nowLife; //显示棋子生命
    QLineEdit *location; //显示棋子位置

    ~Widget();

private:
    Ui::Widget *ui;

    Chess mChess[5];   //棋子

    QTimer *timer;   //声明计时器

    hinder mHinder[6];  //障碍

    guard grd[5]; //防守点

    target tar;  //进攻目标区

signals:   // 自定义信号

};

#endif // WIDGET_H
