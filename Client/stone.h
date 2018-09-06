#ifndef STONE_H
#define STONE_H

#include <QObject>
#include <QPainter>
#include <QPixmap>

// Stone（棋子类） 的摘要说明。
// 提供棋子相关的属性，方法，事件
class Stone
{
public:
    Stone();
    ~Stone();

private:

    //从文件获取
    QPixmap imgBlackStone;  //黑子图片
    QPixmap imgWhiteStone;  //白子图片
    QPixmap imgRedTriangle; //红三角（用于标识最后一子）

public:
    void DrawStone(QPainter *pDC,int m,int n,bool flag,int lm,int ln);
    void DrawStoneFlag(QPainter *pDC,int m,int n);
};

#endif // STONE_H
