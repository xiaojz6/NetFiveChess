#ifndef COMPUTER_H
#define COMPUTER_H

#include "rule.h"

//电脑类。计算电脑下棋的位置
class Computer
{
public:
    Computer(bool flag);
    ~Computer();

    //电脑下棋
    void Down(int arrchessboard[][15]);

    //找出权值最大点
    void MaxQZ(int qz[][15]);

    // 检查m，n点的权值
    int Check(int m, int n, int arrchessboard[][15]);

    int X();
    int Y();
private:
    bool mflag;	//区别电脑是下黑棋还是下白棋
    int x;		//电脑下子的位置
    int y;		//电脑下子的位置
};

#endif // COMPUTER_H
