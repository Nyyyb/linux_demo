/*
    网络通信时，发送端需要将主机字节序转换成网络字节序（大端）
    #include <arpa/inet.h>
    // 转换端口
    uint16_t htons(uint16_t hostshort); // 主机字节序 - 网络字节序
    uint16_t ntohs(uint16_t netshort); // 主机字节序 - 网络字节序
    // 转IP
    uint32_t htonl(uint32_t hostlong); // 主机字节序 - 网络字节序
    uint32_t ntohl(uint32_t netlong); // 主机字节序 - 网络字节序

 */

#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    /* htos 端口 */
    uint16_t a = 0x0102;
    printf("a: %x\n", a);
    uint16_t b = htons(a);
    printf("b: %x\n", b);
    /* htol ip */
    char buf[4] = {192, 168, 1, 100};
    uint32_t host = *(int *)buf;
    uint32_t net = htonl(host);
    // printf("net: %d\n", net);
    unsigned char *ip = (unsigned char *)&net;
    // char *ip = (char *)&net;
    printf("%d %d %d %d\n", *ip, *(ip + 1), *(ip + 2), *(ip + 3));
    printf("%u %u %u %u\n", *ip, *(ip + 1), *(ip + 2), *(ip + 3));
    /*
        for (int i = 0; i < 4; i++)
        {
            printf("%u ", ip[i]);
        }
     */
    printf("%ld\n", sizeof(unsigned long int));
    return 0;
}