#ifndef USERTYPE
#define USERTYPE

typedef enum{LOGIN=1,LOGOUT,LOGOK,LOGERR,TRANSMIT,SRVSTOP,GAMERUN}FUN;//功能号

typedef struct
{
    int x;
    int y;
}POINT;

//数据格式
typedef struct
{
    FUN   fun;//功能号
    char  SenderId[32];//发送者ID
    char  ReceiveId[32];//发送者ID
    char  Content[256];//内容
    POINT Point;

}NET_PACK;

#endif // USERTYPE

