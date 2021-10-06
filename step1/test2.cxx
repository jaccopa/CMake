#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;

class MessageSender
{
public:
    MessageSender()
    {

    }

    int Init(char* ip,int port)
    {
        //配置服务器信息
        bzero(&ser_addr, sizeof(ser_addr));
        ser_addr.sin_family         = AF_INET;                              //设置为IPV4通信
        ser_addr.sin_addr.s_addr    = inet_addr(ip);                        //设置目的ip
        ser_addr.sin_port           = htons(port);                          //设置目的端口去链接服务器
        ser_addr_len                = sizeof(ser_addr);
        sk                          = socket(AF_INET, SOCK_DGRAM, 0);

        if(sk < 0)
        {
            printf("socket create failure\n");
        }
        return sk;
    }

    int Send(char* sendBuf,int len)
    {
        sendto(sk, sendBuf, len, 0, (struct sockaddr*)&ser_addr, ser_addr_len);
    }

    int Recv()
    {
        
    }

    ~MessageSender()
    {
        if(sk > 0)
        {
            close(sk);
        }
    }

private:
    int sk = -1;
    struct sockaddr_in ser_addr;                                //是用于指定对方(目的主机)信息
    struct sockaddr_in loc_addr;                                //可以用来指定一些本地的信息，比如指定端口进行通信，而不是让系统随机分配
    int ser_addr_len,loc_addr_len;
    int ret,count;
    struct in_addr addr;
};