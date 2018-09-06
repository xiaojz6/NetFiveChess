#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QAction>
#include "usertype.h"
#include "fivechessboard.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
    void closeEvent(QCloseEvent *);//窗口关闭事件

private slots:
    void on_btnLogin_clicked();
    void on_btnLogout_clicked();
    void on_btnSend_clicked();
    void sendPos(POINT point);//发送落子坐标

    void slotDataReceived();//处理接收数据
    void slotConnected();//处理已连接
    void slotDisconnected();//处理已断开

    void RestartNew();
    void UpdateChess(QString);//更新走棋的步数
signals:
    void Login(bool netPlayer);

private:
    Ui::Dialog *ui;

private:
    void InitCtrls();//初始化控件
    void InitGame();//初始化游戏

    bool m_bConnectStatus;//连接状态

    int  m_nPort;//端口
    QHostAddress *m_pServerIP;//服务器地址
    QString     m_userName;//账号(用户名)
    QTcpSocket *m_pSocket;

    //游戏数据
    FiveChessBoard    *m_FiveChessWnd;
    QVBoxLayout* layout;
    QMenuBar* menuBar;
    QAction* actionNew;//重新开始
    QAction* actionExit;//退出

private:
    void NetReceive(NET_PACK *pPack);//处理网络接收数据
    void HandleLogOK(NET_PACK *pPack);//处理登录成功
    void HandleLogErr(NET_PACK *pPack);//处理登录错误
    void HandleTransmit(NET_PACK *pPack);//处理数据转发
    void HandleGamerun(NET_PACK *pPack);//处理游戏数据
    void HandleSrvStop(NET_PACK *pPack);//处理服务器关闭

};

#endif // DIALOG_H
