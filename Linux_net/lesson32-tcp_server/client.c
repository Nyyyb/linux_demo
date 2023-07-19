#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    /* 1. 创建套接字 */
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd == -1)
    {
        perror("socket");
        exit(-1);
    }

    /* 2. 连接服务器 */
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &(server.sin_addr.s_addr));
    server.sin_port = htons(9999);
    int ret = connect(cfd, (struct sockaddr *)&server, sizeof(server));
    if (ret == -1)
    {
        perror("connect");
        exit(-1);
    }
    /* 3. 通信 */
    char *buf = "hello, i am client";
    while (1)
    {

        /* 给服务端发送数据 */
        write(cfd, buf, strlen(buf));

        char recvBuf[1024] = {0};
        int len = read(cfd, recvBuf, sizeof(recvBuf));
        if (len == -1)
        {
            perror("read");
            exit(-1);
        }
        else if (len > 0)
        {
            printf("recv server data: %s\n", recvBuf);
        }
        else if (len == 0)
        {
            /* 服务端断开连接 */
            printf("server closed\n");
            break;
        }
    }

    /* 关闭连接 */
    close(cfd);
    return 0;
}