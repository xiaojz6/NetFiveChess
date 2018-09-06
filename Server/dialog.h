#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "listensocket.h"

#include "usertype.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_btnStart_clicked();
    void on_btnStop_clicked();
    void updateServer(int *pData,int *pClient);

private:
    Ui::Dialog *ui;

private:
    void InitCtrls();//初始化
    void InsertLogs(const QString& strUID,const QString& strLogs);//插入日志

    void HandleLogin(NET_PACK *pPack,ClientSocket *pSocket);//处理用户登录
    void HandleGamerun(NET_PACK *pPack);//处理游戏数据
    void HandleLogout(NET_PACK *pPack);//处理用户退出
    void HandleTransmit(NET_PACK *pPack);//处理用数据转发


    ClientSocket*  FindClient(QString& strUID,bool bFlag = false );//查找账号是否登录

    ListenSocket *m_pSocket;//监听Socket
};

#endif // DIALOG_H
