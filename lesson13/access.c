/*
    #include <unistd.h>
    int access(const char *pathname, int mode);
        作用：判断某个文件是否有某个权限，或者判断是否存在
        参数：
            - pathname：判断的文件的路径
            - mode：
                F_OK
                    判断文件是否存在
                R_OK
                    判断文件是否可读
                W_OK
                    判断文件是否可写
                X_OK
                    判断文件是否可执行
        返回：
            成功：0
            失败：-1，errno
                

*/

#include <unistd.h>
#include <stdio.h>

int main()
{
    int ret = access("a.txt", F_OK);
    if(ret == -1)
    {
        perror("access");
        return -1;
    }
    printf("文件存在\n"); 
    return 0;
}