/*
    条件变量的类型pthread_cond_t

    int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);

    int pthread_cond_destroy(pthread_cond_t *cond);

    int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_cond_t *restrict mutex);
        - 阻塞函数，调用该函数，线程会阻塞

    int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_cond_t *restrict mutex, const struct timespec *restrict abstime);
        - 等待多长时间，调用了这个函数，线程会阻塞，直到指定的时间结束

    int pthread_cond_signal(pthread_cond_t *cond);
        - 唤醒一个或者多个等待的线程
    int pthread_cond_broadcast(pthread_cond_t *cond);
        - 唤醒所有等待的线程
*/

/*
    生产者消费者模型

*/
#include <stdio.h>
#include <pthread.h>
#define __USE_MISC 1
#include <unistd.h>
#include <stdlib.h>

#define ProdThreadNum 5
#define CustThreadNum 5

void * prodWork(void * arg);
void * custWork(void * arg);

// 创建一个互斥量
pthread_mutex_t mutex;

// 创建条件变量  
pthread_cond_t cond;

struct Node
{
    uint num;
    struct Node * next; 
};

struct Node * head = NULL;

int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
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
    pthread_cond_destroy(&cond);

    pthread_exit(NULL);
    return 0;
}

void * prodWork(void * arg)
{
    // 不断地创建新的节点，添加到链表当中
    while (1)
    {
        // 加锁
        pthread_mutex_lock(&mutex);
        // 头插法
        struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000;
        //  头插法
        
        // printf("add node, num : 0x%x, tid : %ld\n", newNo de->num, pthread_self());
        // printf("add node, num : cc%d, tid : %ld\n", newNode->num, pthread_self());
        printf("add node, num : %d, tid : %ld\n", newNode->num, pthread_self());
        // 只要生产一个，就通知消费者消费
        pthread_cond_signal(&cond);
        // 解锁
        pthread_mutex_unlock(&mutex);
        usleep(100);

    }
    
    return NULL;
}
void * custWork(void * arg)
{
    while (1)
    {
        // 加锁
        pthread_mutex_lock(&mutex);
        struct Node *tmp = head;

        // 判断是否有数据
        if(head != NULL)
        {
            // 有数据

            head = head->next;
            // printf("del node, num : 0x%x, tid : %ld\n", tmp->num, pthread_self());
            // printf("del node, num : cc%d, tid : %ld\n", tmp->num, pthread_self());
            printf("del node, num : %d, tid : %ld\n", tmp->num, pthread_self());
            free(tmp);
            // 解锁
            pthread_mutex_unlock(&mutex);

            usleep(100);
        }
        else
        {
            // 没有数据，需要等待
            // **********当这个函数阻塞的时候，会解锁互斥锁，不阻塞的时候继续向下执行，会重新加锁**************
            pthread_cond_wait(&cond, &mutex);
            pthread_mutex_unlock(&mutex);

        }
        


    }
    
    return NULL;
}
