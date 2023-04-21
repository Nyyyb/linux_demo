/*
    #include <unistd.h>

    int dup2(int oldfd, int newfd);
        作用：重定向文件描述符
        oldfd指向a.txt，newfd也指向b.txt
        调用函数成功后：newfd和b.txt做close，newfd指向a.txt
        oldfd必须是一个有效的文件描述符
        oldfd和newfd值相同的话，相当于什么都没有做


*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd = open("1.txt", O_RDWR | O_CREAT, 0777);
    if(fd == -1)
    {
        perror("open error");
        return -1;
    }

    int fd1 = open("2.txt", O_RDWR | O_CREAT, 0777);
    if(fd1 == -1)
    {
        perror("open error");
        return -1;
    }

    printf("fd: %d, fd1: %d\n", fd, fd1);

    int fd2 = dup2(fd, fd1);
    if(fd2 == -1)
    {
        perror("dup2 error");
        return -1;
    }

    // 通过fd1去写数据，实际上操作的是1.txt，而不是2.txt
    char * str = "hello, world";
    int len = write(fd, str, strlen(str));

    if(len == -1)
    {
        perror("write error");
        return -1;
    }

    printf("fd: %d, fd1: %d, fd2: %d\n", fd, fd1, fd2);

    close(fd);
    close(fd1);


    return 0;
}