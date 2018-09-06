#include "computer.h"
#include <QtGlobal>

Computer::Computer(bool flag)
{
    mflag = flag;
}

Computer::~Computer()
{

}

// <summary>
// 电脑下棋
// </summary>
// <param name="arrchessboard"></param>
void Computer::Down(int arrchessboard[][15])
{
    //权值数组
    int qz[15][15];
    //基本思路：先计算每个点的权值，在权值最高的位置下棋
    for (int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            if (arrchessboard[i][j] < 2)//有子
            {
                qz[i][j] = -1;		//当已有子时标注为-1
            }
            else//无子
            {
                qz[i][j] = Check(i,j,arrchessboard);
            }
        }
    }

    //找出权值最大的点
    MaxQZ(qz);

}

// <summary>
// 找出权值最大点
// </summary>
// <param name="qz"></param>
void Computer::MaxQZ(int qz[][15])
{
    int max = 0;
    for (int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            if (qz[i][j]>max)
            {
                x = i;
                y = j;
                max = qz[i][j];
            }
        }
    }
}

// <summary>
// 检查m，n点的权值
// </summary>
// <param name="m"></param>
// <param name="n"></param>
// <param name="arrchessboard"></param>
// <returns></returns>
int Computer::Check(int m, int n, int arrchessboard[][15])
{
    int qz = 0;
    //找自己的取胜点（1000）
    int w1 = 100000;
    //找对手的取胜点（80）
    int w2 = 50000;
    //找自己的三个相连的点（60）
    int w3 = 10000;
    //找对手的三个相连的点（40）
    int w4 = 5000;
    //找自己的两个相连的点（20）
    int w5 = 1000;
    //找对手的两个相连的点（10）
    int w6 = 500;
    //找自己的相连的点（5）
    int w7 = 100;
    //找对方的相连的点（5）
    int w8 = 50;
    //找自己的失败点
    int w9 = -1000000;

    int arrf[4];
    //如果该位置下我方的子
    if (mflag)
    {
        //我方黑子
        arrchessboard[m][n] = 0;
    }
    else
    {
        //我方白子
        arrchessboard[m][n] = 1;
    }
    arrf[0] = Rule::Xnum(m,n,arrchessboard);
    arrf[1] = Rule::Ynum(m,n,arrchessboard);
    arrf[2] = Rule::YXnum(m,n,arrchessboard);
    arrf[3] = Rule::XYnum(m,n,arrchessboard);
    //中心点权值加1
    if (m==7 && n==7){qz+=1;}

    for (int i=0;i<4;i++)
    {
        if (qAbs(arrf[i]) == 5)
        {
            qz += w1;
        }
        if (arrf[i] == 4)
        {
            qz += w3;
        }
        if (arrf[i] == 3)
        {
            qz += w5;
        }
        if (arrf[i] == 2)
        {
            qz += w7;
        }
        //如果我方为黑棋，还要检查失败点
        if (mflag)
        {
            if (Rule::IsFail(arrf, arrchessboard[m][n])>0)
            {
                qz += w9;
            }
        }
    }
    //如果该位置下对方的子
    if (mflag)
    {
        //对方白子
        arrchessboard[m][n] = 1;
    }
    else
    {
        //对方黑子
        arrchessboard[m][n] = 0;
    }
    arrf[0] = Rule::Xnum(m,n,arrchessboard);
    arrf[1] = Rule::Ynum(m,n,arrchessboard);
    arrf[2] = Rule::YXnum(m,n,arrchessboard);
    arrf[3] = Rule::XYnum(m,n,arrchessboard);

    for (int i=0;i<4;i++)
    {
        if (qAbs(arrf[i]) == 5)
        {
            qz += w2;
        }
        if (arrf[i] == 4)
        {
            qz += w4;
        }
        if (arrf[i] == 3)
        {
            qz += w6;
        }
        if (arrf[i] == 2)
        {
            qz += w8;
        }
    }
    //数组好像是引用传递，探测完后恢复到默认值
    arrchessboard[m][n] = 2;
    return qz;
}

int Computer::X()
{
    return x;
}

int Computer::Y()
{
    return y;
}

