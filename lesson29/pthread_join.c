/*
    #include <pthread.h>

    int pthread_join(pthread_t thread, void **retval);
        - 功能：和一个已经终止的线程连接
            回收子线程的资源
            特点：阻塞函数，和wait一样，调用一次回收一个子线程
            一般在主线程使用
        - 参数：
            - thread：需要回收的子线程ID
            - retval：用于接收子线程的返回值，如果不关心，可以写NULL
        - 返回值
            0 成功
            非零 错误号
*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
// int value = 100; // 全局变量

void * thread_start(void * arg)
{
    printf("child thread id: %lu\n", pthread_self());
    // printf("child thread id: %ld\n", pthread_self());
    // sleep(3);
    // return NULL;
    // int value = 10; // 局部变量
    static int value = 10; // 静态变量
    pthread_exit((void *)&value);
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, thread_start, NULL);
    if(ret != 0)
    {
        char * error = strerror(ret);
        printf("error: %s\n", error); 
    }
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", i);
    }
    printf("tid: %lu\n main thread id: %lu\n", tid, pthread_self());

    // 主线程调用pthread_join回收子线程资源 
    int * thread_retval;
    ret = pthread_join(tid, (void**)&thread_retval);
    if(ret != 0)
    {
        char * error = strerror(ret);
        printf("error: %s\n", error); 
    }
    printf("exit data : %d\n", *thread_retval);
    printf("回收子线程资源成功\n");

    pthread_exit(NULL);

    return 0;
}