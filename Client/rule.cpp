#include "rule.h"
#include <QtGlobal>

Rule::Rule()
{

}

Rule::~Rule()
{

}

// <summary>
// 判断下棋位置是否有子
// </summary>
// <param name="m"></param>
// <param name="n"></param>
// <param name="arrchessboard"></param>
// <returns></returns>
bool Rule::IsExist(int m, int n, int arrchessboard[][15])
{
    if (arrchessboard[m][n] < 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// <summary>
// 返回结果（1：双三禁手失败/2：双四禁手失败/3：长连禁手失败/4：胜利/5：平局/6：继续）
// </summary>
// <param name="m"></param>
// <param name="n"></param>
// <param name="arrchessboard"></param>
// <returns></returns>
int Rule::Result(int m, int n, int arrchessboard[][15])
{
    //m,n点四个方向的连子数，依次正东正西，正南正北方，西北东南，西南东北
    int arrf[4];
    arrf[0] = Xnum(m,n,arrchessboard);
    arrf[1] = Ynum(m,n,arrchessboard);
    arrf[2] = YXnum(m,n,arrchessboard);
    arrf[3] = XYnum(m,n,arrchessboard);

    //测试
    //return Ynum(m,n,arrchessboard);

    //检查是否失败
    if (IsFail(arrf, arrchessboard[m][n]) > 0)
    {
        return IsFail(arrf, arrchessboard[m][n]);
    }
    else
    {
        //检查是否胜利
        if (IsWin(arrf))
        {
            return 4;
        }
        else
        {
            //检查是否平局
            if (IsTie(arrchessboard))
            {
                return 5;
            }
            else
            {
                return 6;
            }
        }
    }
}


// <summary>
// 是否失败（0：没有失败/1：双三禁手/2：双四禁手/3：长连禁手）
// </summary>
// <param name="arr"></param>
// <param name="stoneflag">是黑棋还是白棋</param>
// <returns>没有失败：0/双三禁手：1/双四禁手：2/长连禁手：3</returns>
int Rule::IsFail(int arr[], int stoneflag)
{
    if (stoneflag == 1)
    {
        //如果是白棋不验证因为白棋无禁手
        return 0;
    }
    else
    {
        //验证双三禁手（该处的双三因该是活的双三吧）
        int num = 0;		//活的3子相连的个数
        for (int i=0;i<4;i++)
        {
            if (arr[i] == 3)
            {
                num++;
            }
        }
        if (num > 1)
        {
            return 1;
        }
        //验证双四禁手（该处的双四因该是活的双四吧）
        num = 0;		//活的4子相连的个数
        for (int i=0;i<4;i++)
        {
            if (arr[i] == 4)
            {
                num++;
            }
        }
        if (num > 1)
        {
            return 2;
        }
        //验证长连禁手
        for (int i=0;i<4;i++)
        {
            if (qAbs(arr[i]) > 5)
            {
                return 3;
            }
        }
        return 0;
    }
}

// <summary>
// 是否胜利
// </summary>
// <param name="arr"></param>
// <returns>胜利：true</returns>
bool Rule::IsWin(int arr[])
{
    for (int i=0;i<4;i++)
    {
        if (qAbs(arr[i]) == 5)
        {
            return true;
        }
    }
    return false;

}


// <summary>
// 是否平局
// </summary>
// <param name="arrchessboard"></param>
// <returns>平局：true</returns>
bool Rule::IsTie(int arrchessboard[][15])
{
    //当所有位置都有子时为平局
    for (int i=0;i<15;i++)
    {
        for (int j=0;j<15;j++)
        {
            if (arrchessboard[i][j] == 2)
                return false;
        }
    }
    return true;
}


// <summary>
// 正东正西检测与m，n点棋子相同的棋子个数
// </summary>
// <param name="m"></param>
// <param name="n"></param>
// <param name="arrchessboard"></param>
// <returns>如果返回负值则表示改方向在无子可下</returns>
int Rule::Xnum(int m, int n, int arrchessboard[][15])
{
    //检查是否无子可下（当flag=2时表示无子可下）
    int flag = 0;
    //连子个数
    int num = 1;

    //正东方向检查(x+)
    int i = m+1;
    //不超出棋格
    while(i < 15)
    {
        //前方的棋子与m,n点不同时跳出循环
        if (arrchessboard[i][n] == arrchessboard[m][n])
        {
            num++;
            i++;
        }
        else
        {
            break;
        }
    }
    //正东方向超出棋格
    if (i==15)
    {
        flag++;
    }
    else
    {
        //正东方向有别的子不可在下
        if(arrchessboard[i][n] != 2)
        {
            flag++;
        }
    }

    //正西方向检查(x-)
    i = m-1;
    while(i >= 0)
    {
        //前方的棋子与m,n点不同时跳出循环
        if (arrchessboard[i][n] == arrchessboard[m][n])
        {
            num++;
            i--;
        }
        else
        {
            break;
        }
    }
    //正西方向超出棋格
    if (i == -1)
    {
        flag++;
    }
    else
    {
        //正西方向有别的子不可在下
        if(arrchessboard[i][n] != 2)
        {
            flag++;
        }
    }


    if (flag == 2)
    {
        return -num;
    }
    else
    {
        if (flag == 1 && num == 3 )
        {
            //连子数为3时有一边不能下就不是活三
            return -num;
        }
        else
        {
            return num;
        }
    }
}

// <summary>
// 正南正北方向检测
// </summary>
// <param name="m"></param>
// <param name="n"></param>
// <param name="arrchessboard"></param>
// <returns>如果返回负值则表示改方向在无子可下</returns>
int Rule::Ynum(int m, int n, int arrchessboard[][15])
{
    //检查是否无子可下（当flag=2时表示无子可下）
    int flag = 0;
    //连子个数
    int num = 1;
    //正南方向检查(y+)
    int i = n+1;
    while(i<15)
    {
        //前方的棋子与m,n点不同时跳出循环
        if (arrchessboard[m][i] == arrchessboard[m][n])
        {
            num++;
            i++;
        }
        else
        {
            break;
        }
    }
    //正南方向超出棋格
    if (i==15)
    {
        flag++;
    }
    else
    {
        //正南方向有别的子不可在下
        if(arrchessboard[m][i] != 2)
        {
            flag++;
        }
    }

    //正北方向检查(y-)
    i = n-1;
    while(i >= 0)
    {
        //前方的棋子与m,n点不同时跳出循环
        if (arrchessboard[m][i] == arrchessboard[m][n])
        {
            num++;
            i--;
        }
        else
        {
            break;
        }
    }
    //正北方向超出棋格
    if (i == -1)
    {
        flag++;
    }
    else
    {
        //正北方向有别的子不可在下
        if(arrchessboard[m][i] != 2)
        {
            flag++;
        }
    }

    if (flag == 2)
    {
        return -num;
    }
    else
    {
        if (flag == 1 && num == 3 )
        {
            //连子数为3时有一边不能下就不是活三
            return -num;
        }
        else
        {
            return num;
        }
    }
}

// <summary>
// 西北东南方向检查
// </summary>
// <param name="m"></param>
// <param name="n"></param>
// <param name="arrchessboard"></param>
// <returns>如果返回负值则表示改方向在无子可下</returns>
int Rule::YXnum(int m, int n, int arrchessboard[][15])
{
    //检查是否无子可下（当flag=2时表示无子可下）
    int flag = 0;
    //连子个数
    int num = 1;

    //东南方向(x+,y+)
    int i = m+1;
    int j = n+1;
    //不超出棋格
    while(i < 15 && j < 15)
    {
        //前方的棋子与m,n点不同时跳出循环
        if (arrchessboard[i][j] == arrchessboard[m][n])
        {
            num++;
            i++;
            j++;
        }
        else
        {
            break;
        }
    }
    //东南方向超出棋格
    if (i==15 || j==15)
    {
        flag++;
    }
    else
    {
        //东南方向有别的子不可在下
        if(arrchessboard[i][j] != 2)
        {
            flag++;
        }
    }

    //西北方向(x-,y-)
    i = m-1;
    j = n-1;
    //不超出棋格
    while(i >= 0 && j >= 0)
    {
        //前方的棋子与m,n点不同时跳出循环
        if (arrchessboard[i][j] == arrchessboard[m][n])
        {
            num++;
            i--;
            j--;
        }
        else
        {
            break;
        }
    }
    //西北方向超出棋格
    if (i == -1 || j == -1)
    {
        flag++;
    }
    else
    {
        //西北方向有别的子不可在下
        if(arrchessboard[i][j] != 2)
        {
            flag++;
        }
    }

    if (flag == 2)
    {
        return -num;
    }
    else
    {
        if (flag == 1 && num == 3 )
        {
            //连子数为3时有一边不能下就不是活三
            return -num;
        }
        else
        {
            return num;
        }
    }
}

// <summary>
// 西南东北方向检查
// </summary>
// <param name="m"></param>
// <param name="n"></param>
// <param name="arrchessboard"></param>
// <returns>如果返回负值则表示改方向在无子可下</returns>
int Rule::XYnum(int m, int n, int arrchessboard[][15])
{
    //检查是否无子可下（当flag=2时表示无子可下）
    int flag = 0;
    //连子个数
    int num = 1;

    //西南方向(x-,y+)
    int i = m-1;
    int j = n+1;
    //不超出棋格
    while(i >= 0 && j < 15)
    {
        //前方的棋子与m,n点不同时跳出循环
        if (arrchessboard[i][j] == arrchessboard[m][n])
        {
            num++;
            i--;
            j++;
        }
        else
        {
            break;
        }
    }
    //西南方向超出棋格
    if (i == -1 || j == 15)
    {
        flag++;
    }
    else
    {
        //西南方向有别的子不可在下
        if(arrchessboard[i][j] != 2)
        {
            flag++;
        }
    }

    //东北方向(x+,y-)
    i = m+1;
    j = n-1;
    //不超出棋格
    while(i < 15 && j >= 0)
    {
        //前方的棋子与m,n点不同时跳出循环
        if (arrchessboard[i][j] == arrchessboard[m][n])
        {
            num++;
            i++;
            j--;
        }
        else
        {
            break;
        }
    }
    //东北方向超出棋格
    if (i == 15 || j == -1)
    {
        flag++;
    }
    else
    {
        //东北方向有别的子不可在下
        if(arrchessboard[i][j] != 2)
        {
            flag++;
        }
    }

    if (flag == 2)
    {
        return -num;
    }
    else
    {
        if (flag == 1 && num == 3 )
        {
            //连子数为3时有一边不能下就不是活三
            return -num;
        }
        else
        {
            return num;
        }
    }
}






