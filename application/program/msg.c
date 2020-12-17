#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    long mtype;     //此处数据类型必须是long，int会出错
    char data[255];
}msg_buf;

int main(void)
{
    key_t key;
    int msgid;
    int ret;
    msg_buf msgbuf;

    key = ftok("/home/mkj/Opinions/application/program/c", 'a');
    printf("key = [%x]\n", key);
    msgid = msgget (key, IPC_CREAT|0666);   //通过文件对应

    if(msgid == -1)
    {
        printf("create error\n");
        return -1;
    }

    msgbuf.mtype = getpid();//mtype是消息类型，int，自己随意指定
    strcpy(msgbuf.data, "test hahaha");
    //msgsnd参数:队列ID，存放消息的结构体地址,size，IPC——NOWAIT发不了的话不会让进程阻塞
    ret = msgsnd(msgid, &msgbuf, sizeof(msgbuf.data), IPC_NOWAIT);
    if(ret == -1)
    {
        printf("send message err\n");
        return -1;
    }
    printf("%s %d\n", msgbuf.data, msgid);
    memset(&msgbuf, 0, sizeof(msgbuf));
    ret = msgrcv(msgid, &msgbuf, sizeof(msgbuf.data), getpid(),IPC_NOWAIT);
    if(ret == -1)
    {
        printf("recv message err\n");//此程序会打印出这个，不知那里除了问题
        return -1;//上面问题已找出，是msg_buf第一个参数设置成了int，应该是long
    }
        printf("recv msg = [%s]\n", msgbuf.data);
        return 0;
}