/*
    字节在内存中存储的顺序
    大端：数据的高位字节存储在内存的低位地址，即先存高位字节
    小端
 */

// 通过代码检测当前主机的字节序

#include <stdio.h>

int main()
{

    union
    {
        short value;               // 两字节
        char bytes[sizeof(short)]; /* char[2] */
    } test;
    test.value = 0x0102;
    if (test.bytes[0] == 1)
    {
        printf("big order\n");
    }
    else if (test.bytes[0] == 2)

    {
        printf("short order\n");
    }
    return 0;
}