
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    // 1. 创建一个共享内存
    int shmid = shmget(100, 4096, IPC_CREAT | IPC_EXCL | 0664);
    printf("shmid = %d\n", shmid);
    // 2. 和当前进程进行关联
    void * ptr = shmat(shmid, NULL, 0);
    // 3. 写数据
    memcpy(ptr, "hello world", strlen("hello world")+1);

    printf("按任意键继续");
    getchar();

    // 4. 解除关联
    shmdt(ptr);
    // 5. 删除共享内存
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}