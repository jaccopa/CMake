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
#define MAX_LEN 1000

class MessageRecver
{
public:
    MessageRecver()
    {

    }

    int Init(char* ip,int port)
    {
        bzero(&src_addr, sizeof(src_addr));
        src_addr.sin_family         = AF_INET;
        src_addr.sin_addr.s_addr    = htonl(INADDR_ANY);                //作为服务器，可能有多块网卡，设置INADDR_ANY，表示绑定一个默认网卡进行监听
        src_addr.sin_port           = htons(port);
        src_addr_len                = sizeof(src_addr);
        cli_addr_len                = sizeof(cli_addr);

        sk = socket(AF_INET, SOCK_DGRAM, 0);
        if(sk < 0)
            return sk;
        ret = bind(sk, (struct sockaddr*)&src_addr, src_addr_len);
        if(sk < 0)
            return sk;
        return sk;
    }

    void RecvLoop()
    {
        while (true)
        {
            printf("Waiting for data from sender \n");
            count = recvfrom(sk, message, MAX_LEN, 0, (struct sockaddr*)&cli_addr, &cli_addr_len);
            if(count == -1)
            {
                printf("receive data failure\n");
                return;
            }
            addr.s_addr = cli_addr.sin_addr.s_addr;
            printf("Receive info: %s from %s %d\n", message,inet_ntoa(addr),cli_addr.sin_port);
            sendto(sk, message, count, 0, (struct sockaddr*)&cli_addr, cli_addr_len);
        }
    }

    ~MessageRecver()
    {
        if(sk > 0)
        {
            close(sk);
        }
    }

private:
    char message[MAX_LEN];
    int sk = -1;
    struct sockaddr_in src_addr;    //用于指定本地监听信息
    struct sockaddr_in cli_addr;    //獲取客戶端地址信息
    int src_addr_len;
    socklen_t cli_addr_len;
    int count,ret;
    struct in_addr addr;
};