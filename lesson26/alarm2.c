// a.out >> test.txt

#include <stdio.h>
#include <unistd.h>

int main()
{

    int i = 0;
    int seconds = alarm(1);
    while(1)
    {
        printf("%d\n", ++i);
    }
    return 0;
}