#include "fivechessboard.h"

#include <QMessageBox>
#include <QtMath>

FiveChessBoard::FiveChessBoard(QWidget *parent,bool netplayer) : QWidget(parent)
{
    //判断当前棋子是黑(true)是白(false)
    stoneflag = true;

    m_bNetplayer = netplayer;

    QPixmap imgChessboard(":/Images/chessboard.gif");  //棋盘图片 大小600*600像素

    int nWidth = imgChessboard.width();
    int nHeight = imgChessboard.height();

    this->setFixedSize(nWidth,nHeight);

    //设置鼠标跟踪
    this->setMouseTracking(true);


    Initialization();

    //初始载入默认玩家先
    if(!m_bNetplayer)
    {
        Start(false);
    }

}

FiveChessBoard::~FiveChessBoard()
{

}

//联机游戏开始
void FiveChessBoard::netPlay(bool flg)
{
    m_bNetplayer = flg;
    this->Start(false);
}

void FiveChessBoard::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);

    Draw(&painter);
}

void FiveChessBoard::mouseMoveEvent(QMouseEvent *e)
{
    int m = (int)qFloor((double)e->x()/40);
    int n = (int)qFloor((double)e->y()/40);

}

void FiveChessBoard::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //人下棋子
        PersonDownStone(e->x(),e->y());
    }
}

// <summary>
// 历史记录属性
// </summary>
QStack<QString> FiveChessBoard::StarckHistory()
{
    return mStarckHistory;
}

// <summary>
// 画棋盘
// </summary>
void FiveChessBoard::Draw(QPainter* pDC)
{
    //读取棋盘图像
    //从资源中获取
    QPixmap imgChessboard(":/Images/chessboard.gif");  //棋盘图片 大小600*600像素

    pDC->drawPixmap(0,0,imgChessboard.width(),imgChessboard.height(),imgChessboard);

    //绘制棋子
    for (int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            if (arrchessboard[i][j] == 0)
            {
                stone->DrawStone(pDC,i,j,true,-1,-1);
            }
            if (arrchessboard[i][j] == 1)
            {
                stone->DrawStone(pDC,i,j,false,-1,-1);
            }
        }
    }

    QPoint pt = GetCurrentPoint();

    stone->DrawStoneFlag(pDC,pt.x(),pt.y());
}


// <summary>
// 下棋
// </summary>
// <param name="m"></param>
// <param name="n"></param>
void FiveChessBoard::DownStone(int m, int n)
{

    int lm = -1,ln = -1;//上一落子点

    if (mStarckHistory.count() > 0)
    {
        //分解上一落子点
        QString lstr = mStarckHistory.top().replace("黑：","").replace("白：","");

        QStringList arr = lstr.split(',');

        lm = arr[0].toInt();
        ln = arr[1].toInt();
    }


    //记录情况
    if (stoneflag)
    {
        arrchessboard[m][n] = 0;
    }
    else
    {
        arrchessboard[m][n] = 1;
    }

    //test(重绘)
    this->update();

    //记录历史记录
    if (stoneflag)
    {
        mStarckHistory.push("黑："+QString::number(m)+","+QString::number(n));

        emit  notifyChess("黑："+QString::number(m)+","+QString::number(n));
    }
    else
    {
        mStarckHistory.push("白："+QString::number(m)+","+QString::number(n));

        emit notifyChess("白："+QString::number(m)+","+QString::number(n));
    }
    //判断结果
    if (Rule::Result(m,n,arrchessboard) < 6)
    {
        switch(Rule::Result(m,n,arrchessboard))
        {
        case 1:
            QMessageBox::information(0,"系统温馨提示","黑棋双三禁手失败！");
            break;
        case 2:
            QMessageBox::information(0,"系统温馨提示","黑棋双四禁手失败！");
            break;
        case 3:
            QMessageBox::information(0,"系统温馨提示","黑棋长连禁手失败！");
            break;
        case 4:
            if (stoneflag)
            {
                QMessageBox::information(0,"系统温馨提示","黑棋胜利！");
            }
            else
            {
                QMessageBox::information(0,"系统温馨提示","白棋胜利！");
            }
            break;
        case 5:
            QMessageBox::information(0,"系统温馨提示","平局！");
            break;
        }

        //重新开始！
        Start();
    }
    else
    {
        //交换当前棋子颜色
        stoneflag = !stoneflag;
    }
}


// <summary>
// 人下棋
// </summary>
// <param name="x"></param>
// <param name="y"></param>
void FiveChessBoard::PersonDownStone(int x, int y)
{
    if(m_bNetplayer && !opntdown)//对手未落子
    {
        return;
    }
    if (x < 600 && y < 600)
    {
        //取下棋点
        int m = (int)qFloor((double)x/40);
        int n = (int)qFloor((double)y/40);
        if (!Rule::IsExist(m,n,arrchessboard))
        {

            if(m_bNetplayer)//联机
            {
                //发信号
                emit curPos(POINT({m,n}));
                DownStone(m,n);
                opntdown = false;
            }
            else//单机
            {
                DownStone(m,n);
                ComputerDownStone();
            }
        }
    }

}

// <summary>
// 电脑下棋
// </summary>
void FiveChessBoard::ComputerDownStone(POINT point)
{
    int m,n,count=0;
    if(!m_bNetplayer)//单机
    {
        do
        {
            computer->Down(arrchessboard);
            m = computer->X();
            n = computer->Y();
            count++;
            if (count > 100)
            {
                QMessageBox::information(0,"系统温馨提示","异常！");
                Start();
                return;
            }
        }
        while(Rule::IsExist(m,n,arrchessboard));

    }
    else//联机
    {
        //从网络数据中获取坐标
        m = point.x;
        n = point.y;
        opntdown = true;
    }
    DownStone(m,n);
}

// <summary>
// 开始（是电脑(true)还是人(false)）
// </summary>
// <param name="playfirstflag">判断先手玩家（是电脑(true)还是人(false)，先手下黑棋）</param>
void FiveChessBoard::Start(bool playfirstflag)
{
    mplayfirstflag = playfirstflag;
    Start();
}

// <summary>
// 开始
// </summary>
void FiveChessBoard::Start()
{
    Initialization();

    //发射信号
    emit  notifyChess("新开局");

    //构造电脑对象
    computer = new Computer(mplayfirstflag);


    if (mplayfirstflag)
    {
        ComputerDownStone();
    }

    this->update();
}

//获取最后落子的位置
QPoint FiveChessBoard::GetCurrentPoint()
{
    QPoint pt(-1,-1);

    if (mStarckHistory.count() > 0)
    {
        //分解上一落子点
        QString lstr = mStarckHistory.top().replace("黑：","").replace("白：","");

        QStringList arr = lstr.split(',');

        pt.rx() = arr[0].toInt();
        pt.ry() = arr[1].toInt();
    }

    return pt;
}

// <summary>
// 初始化
// </summary>
void FiveChessBoard::Initialization()
{
    opntdown = true;
    //置当前要走的棋为黑棋（黑棋先走）
    stoneflag = true;
    //把棋盘所有位置置为空（未下子）
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            arrchessboard[i][j] = 2;
        }
    }
    //清空历史记录堆栈
    mStarckHistory.clear();

    //构造棋子对象
    stone = new Stone();
}

