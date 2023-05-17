/*
    使用多线程实现买票的案例
    有3个窗口，一共100张票

*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#define __USE_MISC 1
#include <unistd.h>

#define ThreadNum 3

void * sellTickets(void * arg);

int main()
{
    // 创建三个子线程
    pthread_t tid[ThreadNum];
    for(int i = 0; i < ThreadNum; i++)
    {
        int ret = pthread_create(&tid[i], NULL, sellTickets, NULL);
        if(ret != 0)
        {
            char * error = strerror(ret );
            printf("error: %s\n", error); 
        }
    }

    // 回收子线程资源
    for (int i = 0; i < ThreadNum; i++)
    {
        pthread_join(tid[i], NULL);
    }
    
    // 设置线程分离
    for(int i = 0; i < ThreadNum; i++)
    {
        pthread_detach(tid[i]);
    }


    pthread_exit(NULL); // 退出主线程
    
    return 0;
}

void * sellTickets(void * arg)
{
    // 买票
    static int tickets = 100;
    
    while(tickets>0)
    {
        usleep(5000);
        printf("%ld 正在卖第 %d 张门票\n", pthread_self(), tickets);
        tickets--;
    }
    return NULL; 
}