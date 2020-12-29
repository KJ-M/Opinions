#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//线程创建测试程序
void *mythread1(void)
{
	int i;
	for(i = 0; i < 100; i++)
	{
		printf("1 thread\n");
		sleep(1);
	}
}
void *mythread2(void)
{
	int i;
	for(i = 0; i < 100; i++)
	{
		printf("2 thread\n");
		sleep(1);
	}
}

int main()
{
	int i = 0, ret = 0;
	pthread_t id1, id2;
	//创建线程1
	ret = pthread_create(&id1, NULL, (void *)mythread1, NULL);
	if(ret)
	{
		printf("create pthread error!\n");
		return 1;
	}
	//创建线程2
	ret = pthread_create(&id2, NULL, (void *)mythread2, NULL);
	if(ret)
	{
		printf("create pthread error!\n");
		return 1;
	}
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);

	return 0;
}

