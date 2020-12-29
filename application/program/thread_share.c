#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

//线程内存共享测试，共享数据段，但是主函数中栈中的数据还是要通过
//pthread_create函数的最后一个参数传递进去，不能直接在线程函数中使用b
//但是可以在线程中直接使用全局变量a，
int a = 1;

void *create (void *arg)
{
    int *b;
    b = (int *)arg;
    printf("thread a = %d \n", a);
    printf("thread b = %d \n", *b);
    a++;
    (*b)++;
    return (void *)0;
}

int main(int argc,  char *argv[])
{
    pthread_t tidp;
    int error;

    int b = 5;
    printf("main 1 a = %d\n", a);
    printf("main 1 b = %d\n", b);

    error = pthread_create(&tidp, NULL, create, (void *)&b);
    //error = pthread_create(&tidp, NULL, create, NULL);

    if(error != 0)
    {
        printf("new thread is not create\n");
        return -1;
    }

    sleep(3);
    printf("main 2 a = %d\n", a);
    printf("main 2 b = %d\n", b);
    return 0;
}