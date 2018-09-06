#ifndef RULE_H
#define RULE_H

#include <QObject>

//游戏规则类
class Rule
{
public:
    Rule();
    ~Rule();

    //判断下棋位置是否有子
    static bool IsExist(int m, int n, int arrchessboard[][15]);

    static int Result(int m, int n, int arrchessboard[][15]);

    //是否失败（0：没有失败/1：双三禁手/2：双四禁手/3：长连禁手）
    static int IsFail(int arr[], int stoneflag);

    //是否胜利
    static bool IsWin(int arr[]);

    //是否平局
    static bool IsTie(int arrchessboard[][15]);

    //正东正西检测与m，n点棋子相同的棋子个数
    static int Xnum(int m, int n, int arrchessboard[][15]);

    //正南正北方向检测
    static int Ynum(int m, int n, int arrchessboard[][15]);

    //西北东南方向检查
    static int YXnum(int m, int n, int arrchessboard[][15]);

    //西南东北方向检查
    static int XYnum(int m, int n, int arrchessboard[][15]);
};

#endif // RULE_H
