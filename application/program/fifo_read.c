#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO "/tmp/myfifo"

int main(int argc, char** argv)
{
    char buf_r[100];
    int fd;
    int nread;

    //创建管道
    if((mkfifo(FIFO, O_CREAT|O_EXCL) < 0) && (errno != EEXIST))
        printf("cannot create fifoserver\n");
    printf("preparing for reading bytes...\n");
    memset(buf_r, 0, sizeof(buf_r));

    //打开管道
    //fd = open(FIFO, O_RDONLY, 0); //使用此行代替下行，程序运行，会卡在此处
    fd = open(FIFO, O_RDONLY|O_NONBLOCK, 0);//使用此行，不会卡住（O_NONBLOCK作用）
    if(fd == -1)
    {
        perror("open");
        exit(1);
    }
    while(1)
    {
        memset(buf_r, 0, sizeof(buf_r));
        if((nread = read(fd, buf_r, 100)) == -1)
        {
            if(errno == EAGAIN)
                printf("no data yet\n");
        }
        printf("read %s from FIFO\n", buf_r);
        sleep(1);
    }
    pause();    //暂停，等待信号
    unlink(FIFO);   //删除文件
}