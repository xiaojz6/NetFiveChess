#include "dialog.h"
#include "ui_dialog.h"

#include <QMessageBox>
#include <QDateTime>

#include <QSettings>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_pSocket = NULL;

    QSettings IniRead("Client.ini", QSettings::IniFormat);

    //服务器端口号
    m_nPort = IniRead.value("/NET/Port").toInt();

    QString strAddress = IniRead.value("/NET/ServerIp").toString();

    //服务器地址
    this->m_pServerIP = new QHostAddress();
    this->m_pServerIP->setAddress(strAddress);

    ui->lineEditUId->setText("UserName");

    this->m_bConnectStatus = false;


    InitCtrls();
    InitGame();
}

Dialog::~Dialog()
{
    delete ui;
}

//初始化控件
void Dialog::InitCtrls()
{
    this->setWindowTitle("五子棋");
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->btnLogout->setEnabled(false);
    ui->btnSend->setEnabled(false);

    m_userName = ui->lineEditUId->text();
}

//初始化游戏
void Dialog::InitGame()
{
    layout = new QVBoxLayout(this);
    menuBar = new QMenuBar(this);
    menuBar->setGeometry(QRect(0, 0, 200, 24));
    QMenu* menu = menuBar->addMenu(tr("系统"));
    actionNew = menu->addAction(tr("重新开始"));

    //设置信号和槽
    //connect(actionNew, &QAction::triggered, this, Dialog::RestartNew);
    connect(actionNew, SIGNAL(triggered()), this, SLOT(RestartNew()));

    actionExit = menu->addAction(tr("退出"));
    connect(actionExit,SIGNAL(triggered()),qApp,SLOT(quit()));

    layout->setMenuBar(menuBar);
    setLayout(layout);


    m_FiveChessWnd = new FiveChessBoard(this);
    m_FiveChessWnd->setGeometry(0,24,600,600);

    //设置信号和槽
    connect(m_FiveChessWnd,SIGNAL(notifyChess(QString)),this,SLOT(UpdateChess(QString)));
    connect(m_FiveChessWnd,SIGNAL(curPos(POINT)),this,SLOT(sendPos(POINT)));
    connect(this,SIGNAL(Login(bool)),m_FiveChessWnd,SLOT(netPlay(bool)));
}


//登录
void Dialog::on_btnLogin_clicked()
{
    if(ui->lineEditUId->text().isEmpty())
    {
        QMessageBox::information(this,"系统提示","账号不能为空！");
        return;
    }

    this->m_userName = ui->lineEditUId->text();

    //创建Socket
    this->m_pSocket = new QTcpSocket(this);

    //设置信号和槽
    connect(this->m_pSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
    connect(this->m_pSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));

    //连接服务器
    this->m_pSocket->connectToHost(*this->m_pServerIP,this->m_nPort);

    //发送数据
    NET_PACK pack;
    memset(&pack,0,sizeof(NET_PACK));

    pack.fun = LOGIN;

    strcpy(pack.SenderId,m_userName.toStdString().c_str());

    m_pSocket->write((char*)&pack,sizeof(NET_PACK));


    //等待数据发送
    //m_pSocket->waitForBytesWritten(50);

}

//退出
void Dialog::on_btnLogout_clicked()
{
    m_userName = ui->lineEditUId->text();

    if(NULL != m_pSocket)
    {
        //发送数据
        NET_PACK pack;
        memset(&pack,0,sizeof(NET_PACK));

        pack.fun = LOGOUT;

        strcpy(pack.SenderId,m_userName.toStdString().c_str());

        m_pSocket->write((char*)&pack,sizeof(NET_PACK));

        //等待数据发送
        m_pSocket->waitForBytesWritten(50);


        this->m_pSocket->close();
        this->m_pSocket->disconnectFromHost();


        delete m_pSocket;
        m_pSocket = NULL;
    }

    m_bConnectStatus = false;
    ui->btnLogin->setEnabled(true);
    ui->btnLogout->setEnabled(false);
    ui->btnSend->setEnabled(false);
    emit Login(false);
}


//发送
void Dialog::on_btnSend_clicked()
{
    this->m_userName = ui->lineEditUId->text();

    if(m_userName.isEmpty())
    {
        QMessageBox::information(this,"系统提示","账号不能为空！");
        return;
    }

    //发送数据
    NET_PACK pack;
    memset(&pack,0,sizeof(NET_PACK));

    pack.fun = TRANSMIT;

    strcpy(pack.SenderId,m_userName.toStdString().c_str());
    strcpy(pack.ReceiveId,ui->lineEdit_RUId->text().toStdString().c_str());
    strcpy(pack.Content,ui->textEditSend->toPlainText().toStdString().c_str());

    m_pSocket->write((char*)&pack,sizeof(NET_PACK));

    //等待数据发送
    //m_pSocket->waitForBytesWritten(5);
}

//发送落子坐标
void Dialog::sendPos(POINT point)
{
    //发送数据
    NET_PACK pack;
    memset(&pack,0,sizeof(NET_PACK));

    pack.fun = GAMERUN;

    pack.Point = point;
    strcpy(pack.SenderId,m_userName.toStdString().c_str());
    strcpy(pack.ReceiveId,ui->lineEdit_RUId->text().toStdString().c_str());
    strcpy(pack.Content,ui->textEditSend->toPlainText().toStdString().c_str());

    m_pSocket->write((char*)&pack,sizeof(NET_PACK));
}

//处理接收数据
void Dialog::slotDataReceived()
{
    if(m_pSocket->bytesAvailable()>0)
    {
        NET_PACK *pPack = new NET_PACK;
        memset(pPack,0,sizeof(NET_PACK));

        QByteArray qba = m_pSocket->readAll();

        NET_PACK *pPack1 = (NET_PACK *)qba.data();
        memcpy(pPack,pPack1,sizeof(NET_PACK));

        //处理网络数据接收
        NetReceive(pPack);
    }
}

//处理网络接收数据
void Dialog::NetReceive(NET_PACK *pPack)
{

    switch(pPack->fun)
    {
    case LOGOK:
        HandleLogOK(pPack);
        break;
    case LOGERR:
        HandleLogErr(pPack);
        break;
    case TRANSMIT:
        HandleTransmit(pPack);
        break;
    case GAMERUN:
        HandleGamerun(pPack);
        break;
    case SRVSTOP:
        HandleSrvStop(pPack);
        break;
    }

    if(NULL != pPack)
    {
        delete pPack;
        pPack = NULL;
    }
}

//处理已连接
void Dialog::slotConnected()
{
    //设置信号和槽
    connect(this->m_pSocket,SIGNAL(readyRead()),this,SLOT(slotDataReceived()));
}

//处理已断开
void Dialog::slotDisconnected()
{
    //设置连接状态为未连接
    this->m_bConnectStatus = false;
}

void Dialog::RestartNew()
{

    ui->lstHistory->clear();

    //重新开始
    m_FiveChessWnd->Start(false);
}

void Dialog::UpdateChess(QString strInfo)
{
    ui->lstHistory->addItem(strInfo);
}

//处理登录成功
void Dialog::HandleLogOK(NET_PACK *pPack)
{
    m_bConnectStatus = true;

    ui->btnLogin->setEnabled(false);
    ui->btnLogout->setEnabled(true);
    ui->btnSend->setEnabled(true);
    //发送登录信号
    emit Login(true);
}

//处理登录错误
void Dialog::HandleLogErr(NET_PACK *pPack)
{
    QString str(pPack->Content);
    QMessageBox::information(this,"系统提示",str);

    this->m_pSocket->close();
    this->m_pSocket->disconnectFromHost();

    delete m_pSocket;
    m_pSocket = NULL;

    m_bConnectStatus = false;

    ui->btnLogin->setEnabled(true);
    ui->btnLogout->setEnabled(false);
    ui->btnSend->setEnabled(false);
}

//处理数据转发
void Dialog::HandleTransmit(NET_PACK *pPack)
{
    QString strContent;

    QDateTime time=QDateTime::currentDateTime();//获取当前时间
    QString strTime=time.toString("yyyy-MM-dd hh:mm:ss");//设置系统时间显示格式

    strContent = QString("%1  %2 说:\r\n%3").arg(strTime).arg(QString(pPack->SenderId)).arg(QString(pPack->Content));


    ui->textEditReceive->append(strContent);
}

//处理游戏坐标数据
void Dialog::HandleGamerun(NET_PACK *pPack)
{
   m_FiveChessWnd->ComputerDownStone(pPack->Point);
}

//处理服务器关闭
void Dialog::HandleSrvStop(NET_PACK *pPack)
{
    QString str(pPack->Content);
    QMessageBox::information(this,"系统提示",str);

    this->m_pSocket->close();
    this->m_pSocket->disconnectFromHost();

    delete m_pSocket;
    m_pSocket = NULL;

    m_bConnectStatus = false;

    ui->btnLogin->setEnabled(true);
    ui->btnLogout->setEnabled(false);
    ui->btnSend->setEnabled(false);
}

//窗口关闭事件
void Dialog::closeEvent(QCloseEvent *)
{
    if(m_bConnectStatus)
    {
       on_btnLogout_clicked();
    }
}
