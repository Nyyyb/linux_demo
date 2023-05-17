/*
    #include <pthread.h>

    void pthread_exit(void *retval);
        - 功能：终止调用的线程
        参数：
            retval: 需要传递一个指针，作为一个返回值，可以在pthread_join中获取到
        返回值：无

    pthread_t pthread_self(void);
        - 功能：obtain ID of the calling thread

    int pthread_equal(pthread_t t1, pthread_t t2);
        - 功能：比较两个线程ID是否相等
            不同的操作系统的pthread实现不同，有的是结构体，像目前是long unsigned int

*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void * thread_start(void * arg)
{
    printf("child thread id: %lu\n", pthread_self());
    printf("child thread id: %ld\n", pthread_self());
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
    pthread_exit(NULL);

    return 0;
}