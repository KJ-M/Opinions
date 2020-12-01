#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//signal函数简单测试，使用ps aux命令查看pid，使用kill -s SIGINT pid来给
//本程序发送信号，接到信号从睡眠状态唤醒然后继续运行
void my_func(int sign_no)
{
    if(sign_no == SIGINT)
        printf("I have got SIGINT\n");
    else if(sign_no == SIGQUIT)
        printf("I have got SIGQUIT\n");
}
int main(void)
{
    printf("Waitting for signal SIGINT or SIGQUIT\n");

    //注册信号处理函数
    signal(SIGINT, my_func);
    signal(SIGQUIT, my_func);
    
    pause();
    exit(0);

}