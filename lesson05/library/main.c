#include "./inc/head.h"
// #include "./src/add.c"
// #include "./src/sub.c"
// #include "./src/mul.c"
// #include "./src/div.c"

int main()
{
    int a = 10;
    int b = 5;
    printf("a+b=%d\n", add(a,b));
    printf("a-b=%d\n", sub(a,b));
    printf("a*b=%d\n", mul(a,b));
    printf("a/b=%f\n", div(a,b));
}