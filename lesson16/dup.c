/*
    #include <unistd.h>     
    int dup(int oldfd);
        作用：复制一个新的文件描述符
        fd=3, int fd1 = dup(fd);
        fd指向的是a.txt，fd1也指向a.txt
        从空闲的文件描述符表找一个最小的，作为新的拷贝的文件描述符
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd = open("a.txt", O_RDWR | O_CREAT, 0777);
    int fd1 = dup(fd);
    
    if(fd1 == -1)
    {
        perror("dup error");
        return -1;
    }

    printf("fd: %d, fd1: %d\n", fd, fd1);
    close(fd);
    char * str = "hello, world";
    int ret = write(fd1, str, strlen(str));
    if(ret == -1)
    {
        perror("write");
        return -1;
    }
    printf("number of write: %d\n", ret);
    printf("strlen of str: %ld\n", strlen(str));
    printf("sizeof of str: %ld\n", sizeof(str));
    printf("sizeof(str)/sizeof(str[0]): %ld\n", sizeof(str)/sizeof(str[0]));

    close(fd1);

    return 0;

}