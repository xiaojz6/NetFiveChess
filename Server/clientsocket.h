#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>

/*
负责和客户端通信的socket
*/
class ClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    ClientSocket(QObject *parent = 0);
    ~ClientSocket();

signals://自定义信号
    void updateClients(int*,int*);
    void disconnected(int);

public slots:
    void dataReceived();
    void slotDisconnected();

public:
    QString    m_strUID;//客户端ID号
};

#endif // CLIENTSOCKET_H
