#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    /* 1. 创建socket套接字（用于监听） */
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1)
    {
        perror("socket");
        exit(-1);
    }
    /* 2. 绑定 */
    struct sockaddr_in saddr;
    saddr.sin_family = PF_INET;
    int buf;
    // inet_pton(AF_INET, "192.168.123.27", &buf);
    // saddr.sin_addr.s_addr = buf;
    // saddr.sin_addr.s_addr = 0;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(9999);

    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1)
    {
        perror("bind");
        exit(-1);
    }
    /* 3. 监听 */
    ret = listen(lfd, 5);
    if (ret == -1)
    {
        perror("listen");
        exit(-1);
    }
    /* 4. 接收客户端的连接 */
    struct sockaddr_in client;
    socklen_t sockLen = sizeof(client);
    int cfd = accept(lfd, (struct sockaddr *)&client, &sockLen);
    if (cfd == -1)
    {
        perror("accept");
        exit(-1);
    }

    /* 输出客户端信息 */
    char clientIP[16];
    inet_ntop(AF_INET, &(client.sin_addr.s_addr), clientIP, sizeof(clientIP));
    uint16_t clientPORT = ntohs(client.sin_port);
    printf("client IP: %s, port: %d\n", clientIP, clientPORT);

    /* 5.  */
    /* 获取客户端的数据 */
    char recvBuf[1024];
    while (1)
    {

        int len = read(cfd, recvBuf, sizeof(recvBuf)); /* 阻塞 */
        if (len == -1)
        {
            perror("read");
            exit(-1);
        }
        else if (len > 0)
        {
            printf("recv client data: %s\n", recvBuf);
        }
        else if (len == 0)
        {
            /* 客户端断开连接 */
            printf("client closed\n");
            break;
        }
        /* 给客户端发送数据 */
        // char *data = "hello, i am server\n";
        write(cfd, recvBuf, strlen(recvBuf));
        sleep(1);
    }

    /* 关闭文件描述符 */
    close(cfd);
    close(lfd);
    return 0;
}