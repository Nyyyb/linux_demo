/*
    #include <pthread.h>

    int pthread_detach(pthread_t thread);
        - 功能：分离一个线程
            1. 不能多次分离，会产生不可预料的行为
            2. 不能连接join一个已经分离的线程，会报错
        - 参数
            tid：需要分离的线程ID
        - 返回值：
            - 0 成功
            - 错误号 失败
*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>

void * start_routine(void * arg)
{
    printf("child thread id: %lu\n", pthread_self());
    return NULL;
}   

int main()
{
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, start_routine, NULL);
    if(ret != 0)
    {
        char * error = strerror(ret);
        printf("error: %s\n", error);
    }

    // 输出主线程和子线程的id
    printf("tid : %ld\nmain thread id : %ld\n", tid, pthread_self());

    // 设置子线程分离，子线程分离后，子线程结束时对应的资源就不需要主线程释放了
    pthread_detach(tid);

    // 设置分离后，对分离的子线程进行连接pthread_join()
    ret = pthread_join(tid, NULL);
    if(ret != 0)
    {
        char * error = strerror(ret);
        printf("error1: %s\n", error);
    }

    // for (int i = 0; i < 5; i++)
    // {
        // printf("%d\n", i);
    // }
    pthread_exit(NULL);
    
    return 0;
}