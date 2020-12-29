#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
/*thread_join测试，pthread_join只会在线程退出的时候继续运行
主函数后面的代码段，不会因为线程中的sleep()而暂时退出运行主函数后面，
此处的表现为：printf("thread %d\n", i);10个运行完毕才运行主函数中的东西
若把pthread_join(pth, NULL);注释掉，则会出现主函数和线程同时运行的情况，
主函数退出，则线程一块退出
*/
void *create(void *arg)
{
    int i;
    for(i = 0; i < 10; ++i)
    {
        sleep(2);
        printf("thread %d\n", i);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t pth;
    int i;
    int ret = pthread_create(&pth, NULL, create, NULL);
    
    pthread_join(pth, NULL);
    printf("123\n");
    for ( i = 0; i < 10; i++)
    {
        sleep(1);
        printf("main : %d\n", i);
    }
    
    return 0;
}