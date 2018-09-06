#ifndef FIVECHESSBOARD_H
#define FIVECHESSBOARD_H

#include <QObject>
#include <QWidget>

#include "computer.h"
#include "stone.h"
#include "usertype.h"

#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>

#include <QStack>
#include <stack>
using namespace std;

class FiveChessBoard : public QWidget
{
    Q_OBJECT
public:
    explicit FiveChessBoard(QWidget *parent = 0,bool netplayer = false);
    ~FiveChessBoard();

signals:
    void  notifyChess(QString);
    void  curPos(POINT point);

public slots:
    void netPlay(bool flg);
protected:
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

public:
    //历史记录属性
    QStack<QString> StarckHistory();

    //画棋盘
    void Draw(QPainter* pDC);

    //下棋
    void DownStone(int m,int n);

    //人下棋
    void PersonDownStone(int x,int y);

    //电脑下棋
    void ComputerDownStone(POINT point = {0,0});

    //开始（是电脑(true)还是人(false)）
    void Start(bool playfirstflag);

    //开始
    void Start();

private:
    //arrchessboard为棋盘情况数组，arrchessboard[i,j]=2表示此处无子，arrchessboard[i,j]=0表示此处为黑子，arrchessboard[i,j]=1表示此处为白子
    int arrchessboard[15][15];
    //绘制的对象
    QPainter* mg;
    //棋子对象
    Stone *stone;
    //电脑对象
    Computer *computer;
    //判断当前棋子是黑(true)是白(false)
    bool stoneflag;
    //判断先手玩家（是电脑(true)还是人(false)，先手下黑棋）
    bool mplayfirstflag;
    //历史记录堆栈
    //Stack mStarckHistory = new Stack();

    //历史记录堆栈
    QStack<QString> mStarckHistory;

    bool m_bNetplayer;
    bool opntdown;//对手落子标记

    POINT m_Netpos;//网络坐标

private:
    void Initialization();
    QPoint GetCurrentPoint();//获取最后落子的位置
};

#endif // FIVECHESSBOARD_H
