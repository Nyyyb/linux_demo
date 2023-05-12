/*
    #include <signal.h>
    int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
        - 功能：将自定义信号集中的数据设置到内核中（设置阻塞，解除阻塞，替换）
        - 参数：
            - how：如何对内核阻塞信号进行处理
                - SIG_BLOCK：将用户设置的阻塞信号添加到内核中，内核中原来的数据不变
                    假设内核中默认的阻塞信号是mask mask | set
                - SIG_UNBLOCK：根据用户设置的数据。对内核中的数据进行解除阻塞
                    信号集中的数据是mask mask & ~set，set中需要解除的设为1，不需要解除的设为0                    
                - SIG_SETMASK：将自定义信号集中的信号设置到内核阻塞信号集中
                    

*/