#include "dialog.h"
#include "ui_dialog.h"


#include <QDateTime>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_pSocket = NULL;

    InitCtrls();
}

Dialog::~Dialog()
{
    delete ui;
}


//启动
void Dialog::on_btnStart_clicked()
{
    if(ui->txtPort->text() == "")
    {
        QMessageBox::information(this,tr("程序提示"),tr("端口号不能为空 ! "));
    }

    //端口号
    int nPort = ui->txtPort->text().toInt();

    //创建Socket
    if(NULL == m_pSocket)
    {
        m_pSocket =new ListenSocket(this,nPort);

        connect(m_pSocket,SIGNAL(updateServer(int*,int *)),this,SLOT(updateServer(int*,int *)));
    }

    //设置按钮
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);

    InsertLogs("服务器","服务器监听中......");
}

//停止
void Dialog::on_btnStop_clicked()
{

    NET_PACK pack;
    memset(&pack,0,sizeof(NET_PACK));

    pack.fun = SRVSTOP;

    QString strMsg = "服务器维护中......";
    strcpy(pack.Content,strMsg.toStdString().c_str());

    ClientSocket* pSocket = NULL;

    QList<ClientSocket*>::iterator  iter = ListenSocket::m_listClient.begin();

    for(;iter!=ListenSocket::m_listClient.end();++iter)
    {
        pSocket = *iter;

        //发数据
        pSocket->write((char*)&pack,sizeof(NET_PACK));

        pSocket->waitForBytesWritten(20);

        pSocket->close();

        pSocket->deleteLater();
        pSocket = NULL;
    }

    //清空链表
    ListenSocket::m_listClient.clear();

    //关闭Socket,并清空资源
    if(NULL != m_pSocket)
    {
        m_pSocket->close();

        m_pSocket->deleteLater();
        m_pSocket = NULL;
    }

    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);

    InsertLogs("服务器","服务器已停止......");
}

//初始化
void Dialog::InitCtrls()
{
    this->setWindowTitle("五子棋服务器");
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->txtPort->setText("5500");

    //QTableWidget
    ui->tableWidgetLogs->setColumnCount(4);
    //ui->tableWidgetLogs->setRowCount(10);

    //设置列宽度
    ui->tableWidgetLogs->setColumnWidth(0,50);
    ui->tableWidgetLogs->setColumnWidth(1,80);
    ui->tableWidgetLogs->setColumnWidth(2,150);
    ui->tableWidgetLogs->setColumnWidth(3,150);

    ui->tableWidgetLogs->verticalHeader()->setVisible(false);

    QStringList headers;
    headers << tr("序号") <<tr("用户名") << tr("时间")<< tr("事件");
    ui->tableWidgetLogs->setHorizontalHeaderLabels(headers);
}

//插入日志
void Dialog::InsertLogs(const QString& strUID,const QString& strLogs)
{
    int nRow = ui->tableWidgetLogs->rowCount();

    ui->tableWidgetLogs->insertRow(nRow);

    ui->tableWidgetLogs->setItem(nRow, 0, new QTableWidgetItem(QString::number(nRow+1)));
    ui->tableWidgetLogs->setItem(nRow, 1, new QTableWidgetItem(strUID));

    QDateTime time=QDateTime::currentDateTime();//获取当前时间
    QString strTime=time.toString("yyyy-MM-dd hh:mm:ss");//设置系统时间显示格式

    ui->tableWidgetLogs->setItem(nRow, 2, new QTableWidgetItem(strTime));
    ui->tableWidgetLogs->setItem(nRow, 3, new QTableWidgetItem(strLogs));
}


void Dialog::updateServer(int *pData,int *pClient)
{
    NET_PACK *pPack = (NET_PACK *)pData;
    ClientSocket *pSocket = (ClientSocket *)pClient;


    switch(pPack->fun)
    {
    case LOGIN://处理登录
        HandleLogin(pPack,pSocket);
        break;
    case LOGOUT://处理客户端退出
        HandleLogout(pPack);
        break;
    case TRANSMIT://数据转发
        HandleTransmit(pPack);
        break;
    case GAMERUN:
        HandleGamerun(pPack);
        break;
    }

    if(NULL != pPack)
    {
        delete pPack;
        pPack = NULL;
    }
}

//处理用户登录
void Dialog::HandleLogin(NET_PACK *pPack,ClientSocket *pSocket)
{
    QString strUid(pPack->SenderId);
    ClientSocket *pClient = FindClient(strUid);


    NET_PACK pack;
    memset(&pack,0,sizeof(NET_PACK));

    if(NULL != pClient)
    {//已登录

        pack.fun = LOGERR;

        QString strMsg = "该用户已登录！";
        strcpy(pack.Content,strMsg.toStdString().c_str());

        //发数据
        pSocket->write((char*)&pack,sizeof(NET_PACK));

        //pSocket->waitForBytesWritten(5);


        pSocket->deleteLater();
        pSocket = NULL;

    }
    else
    {//未登录
        pack.fun = LOGOK;

        //发数据
        pSocket->write((char*)&pack,sizeof(NET_PACK));


        //保存用户名
        pSocket->m_strUID = strUid;

        //存入链表
        ListenSocket::m_listClient.append(pSocket);
        InsertLogs(strUid,"在线......");
    }
}

//处理游戏数据
void Dialog::HandleGamerun(NET_PACK *pPack)
{
    QString strUid(pPack->ReceiveId);

    ClientSocket *pSocket = FindClient(strUid);

    if(NULL != pSocket)
    {
        pSocket->write((char*)pPack,sizeof(NET_PACK));
    }
}

//查找账号是否登录
ClientSocket*  Dialog::FindClient(QString& strUID,bool bFlag)
{
    ClientSocket* pSocket = NULL;

    QList<ClientSocket*>::iterator  iter = ListenSocket::m_listClient.begin();

    for(;iter!=ListenSocket::m_listClient.end();++iter)
    {
        pSocket = *iter;

        //找到
        if(strUID.compare(pSocket->m_strUID) == 0)
        {
            //是否删除
            if(bFlag)
            {
                ListenSocket::m_listClient.erase(iter);
            }

            return pSocket;
        }
    }


    return NULL;
}

//处理用户退出
void Dialog::HandleLogout(NET_PACK *pPack)
{
    QString strUid(pPack->SenderId);

    ClientSocket *pSocket = FindClient(strUid,true);

    if(NULL != pSocket)
    {
        pSocket->deleteLater();
        pSocket = NULL;

        InsertLogs(strUid,"下线......");
    }
}

//处理用户数据转发
void Dialog::HandleTransmit(NET_PACK *pPack)
{
    QString strUid(pPack->ReceiveId);

    ClientSocket *pSocket = FindClient(strUid);

    if(NULL != pSocket)
    {
        pSocket->write((char*)pPack,sizeof(NET_PACK));
    }
}
