/*
    #include <sys/stat.h>

    int chmod(const char *pathname, mode_t mode);
        修改文件的权限
        参数：
            - pathname：要修改的文件的路径
            - mode：需要修改的权限值，八进制数
        返回：

*/

#include <sys/stat.h>
#include <stdio.h>

int main()
{
    int ret = chmod("a.txt", 0775);
    if(ret == -1)
    {
        perror("chmod");
        return -1;
    }

    return 0;
}