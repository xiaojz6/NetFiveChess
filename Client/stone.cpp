#include "stone.h"

Stone::Stone()
{
    //读取黑子，白子图片
    //从资源中获取
    imgBlackStone.load(":/Images/blackstone.gif");
    imgWhiteStone.load(":/Images/whitestone.gif");
    imgRedTriangle.load(":/Images/redtriangle.gif");
}

Stone::~Stone()
{

}


// <summary>
// 绘制棋子
// </summary>
// <param name="m"></param>
// <param name="n"></param>
// <param name="flag">判断是黑棋(true)还是白棋(false)</param>
void Stone::DrawStone(QPainter *pDC,int m, int n, bool flag, int lm, int ln)
{
    if (flag)
    {
        //覆盖上一子的标识
        pDC->drawPixmap(lm*40,ln*40,imgWhiteStone.width(),imgWhiteStone.height(),imgWhiteStone);
        //写当前子
        pDC->drawPixmap(m*40,n*40,imgBlackStone.width(),imgBlackStone.height(),imgBlackStone);
       // pDC->drawPixmap(m*40,n*40,imgRedTriangle);
    }
    else
    {
        //覆盖上一子的标识
        pDC->drawPixmap(lm*40,ln*40,imgBlackStone.width(),imgBlackStone.height(),imgBlackStone);
        //写当前子
        pDC->drawPixmap(m*40,n*40,imgWhiteStone.width(),imgWhiteStone.height(),imgWhiteStone);
        //pDC->drawPixmap(m*40,n*40,imgRedTriangle);
    }
}

//绘制标识
void Stone::DrawStoneFlag(QPainter *pDC, int m, int n)
{
     pDC->drawPixmap(m*40,n*40,imgRedTriangle);
}

