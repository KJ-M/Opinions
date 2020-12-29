#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

//传递参数型线程创建测试，注意只能传递指针，需要进行类型转换
void *create(void *arg)
{
    int *num;
    num = (int *)arg;
    printf("create parameter is %d\n", *num);
    return (void *)0; //之前未见过，可参考借鉴
}

int main(int argc, char *argv[])
{
    pthread_t tidp;
    int error;

    int test = 4;
    int *attr = &test;

    error = pthread_create(&tidp, NULL, create, (void *)attr);
    if(error)
    {
        printf("thread not create\n");
        return -1;
    }
    sleep(1);
    printf("pthread_create is created...\n");
    return 0;
}