/*
    信号量的类型sem_t
    int sem_init(sem_t *sem, int pshared, unsigned int value);
        - 初始化
        - 参数：
            - sem：信号量变量地址
            - pshared：
                - 0：用在线程间
                - 非0：用在进程间
                - value：信号量的初始值
    int sem_destroy(sem_t *sem);
        - 释放资源
    int sem_wait(sem_t *sem);
        - 信号量加锁，调用一次，信号量的值-1，如果为0则阻塞
    int sem_trywait(sem_t *sem)
    int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
    int sem_post(sem_t *sem);
        - 对信号量解锁，调用一次，信号量的值+1
        If the semaphore's value consequently becomes greater than zero, then another process or thread
       blocked in a sem_wait(3) call will be woken up and proceed to lock the semaphore.
       - 如果加一后值大于零，唤醒其他被该信号量阻塞的线程
    int sem_getvalue(sem_t *sem, int *sval);


    生产消费模型伪代码
    sem_t psem;
    sem_t csem
    init(psem, 0, 8);
    init(csem, 0, 0);

    producer()
    {
        sem_wait(&psem);
        // 生产


        sem_post(&csem);
    }
    customer()
    {
        sem_wait(&csem);
        // 消费


        sem_post(&psem);
    }

*/

#include <stdio.h>
#include <pthread.h>
#define __USE_MISC 1
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

#define ProdThreadNum 5
#define CustThreadNum 5

void * prodWork(void * arg);
void * custWork(void * arg);

// 创建一个互斥量
pthread_mutex_t mutex;
sem_t psem, csem;

struct Node
{
    uint num;
    struct Node * next; 
};

struct Node * head = NULL;

int main()
{
    sem_init(&psem, 0, 8);
    sem_init(&csem, 0, 0);
    pthread_mutex_init(&mutex, NULL);

//    创建5个生产者线程和5个消费者线程
    pthread_t ptids[ProdThreadNum], ctids[CustThreadNum];
    for (int i = 0; i < ProdThreadNum; ++i) {
        pthread_create(&ptids[i], NULL, prodWork, NULL);
    }
    for (int i = 0; i < CustThreadNum; ++i) {
        pthread_create(&ctids[i], NULL, custWork, NULL);
    }

//    线程分离
    for (int i = 0; i < ProdThreadNum; ++i) {
        pthread_detach(ptids[i]);
    }
    for (int i = 0; i < CustThreadNum; ++i) {
        pthread_detach(ctids[i]);
    }

    // detach 之后，主线程不能继续走下去销毁互斥量
    while (1)
    {
        sleep(10);
    }

    pthread_mutex_destroy(&mutex);

    pthread_exit(NULL);
    return 0;
}

void * prodWork(void * arg)
{
    // 不断地创建新的节点，添加到链表当中
    while (1)
    {
        sem_wait(&psem);
        // 加锁
        pthread_mutex_lock(&mutex);
        // 头插法
        struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000;
        //  头插法，而且从头开始删除
        
        // printf("add node, num : 0x%x, tid : %ld\n", newNo de->num, pthread_self());
        // printf("add node, num : cc%d, tid : %ld\n", newNode->num, pthread_self());
        printf("add node, num : %d, tid : %ld\n", newNode->num, pthread_self());
        // 只要生产一个，就通知消费者消费
       
        // 解锁
        pthread_mutex_unlock(&mutex);
        sem_post(&csem);
        // usleep(100);

    }
    
    return NULL;
}
void * custWork(void * arg)
{
    while (1)
    {
        sem_wait(&csem);
        // 加锁
        pthread_mutex_lock(&mutex);
        struct Node *tmp = head;

        // 有数据

        head = head->next;
        // printf("del node, num : 0x%x, tid : %ld\n", tmp->num, pthread_self());
        // printf("del node, num : cc%d, tid : %ld\n", tmp->num, pthread_self());
        printf("del node, num : %d, tid : %ld\n", tmp->num, pthread_self());
        free(tmp);
        // 解锁
        pthread_mutex_unlock(&mutex);
        sem_post(&psem);
        // usleep(100);


    }
    
    return NULL;
}
