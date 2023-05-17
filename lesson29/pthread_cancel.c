/*
    #include <pthread.h>

    int pthread_cancel(pthread_t thread);
        - 功能：取消线程（让线程终止）
            默认不是立马终止，而是当子线程执行到一个取消点，线程才会终止
            取消点：系统规定好的一些系统调用，不同系统规定的不一样，比如posix，可以粗略的理解为内核去到系统取得切换，这个位置称之为取消点
        - 参数：
            - thread：需要取消的线程ID

*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>

void * start_routine(void * arg)
{
    printf("child thread id: %lu\n", pthread_self());
    for (int i = 0; i < 10; i++)
    {
        printf("child : %d\n", i);  // 也是个取消点，应该是源码做了系统调用
    }
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

    // 取消线程
    pthread_cancel(tid);

    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", i);
    }

    // 输出主线程和子线程的id
    printf("tid : %ld\nmain thread id : %ld\n", tid, pthread_self());
 

    pthread_exit(NULL);
    
    return 0;
}