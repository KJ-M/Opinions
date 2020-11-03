#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 1024
/******************************************
 * 系统调用方式读写文件练习示例
 * 打开读写关闭函数综合
 * 实现打开一个现有文件，打开第二个文件，没有第二个则创建，将
 * 第一个文件内容拷贝到第二个文件中
 * *****************************************/
int main(int argc, char **argv)
{
   int from_fd,to_fd;
   int bytes_read,bytes_write;
   char buffer[BUFFER_SIZE];
   char *ptr;
   if (argc != 3)
   {
       fprintf(stderr, "Usage:%s fromfile tofile/n/a", argv[0]);
       exit(1);
   }
   /* 打开源文件 */
   if ((from_fd = open(argv[1], O_RDONLY)) == -1)
   {
       fprintf(stderr, "Open %s Error:%s/n", argv[1], strerror(errno));
       exit(1);
   }

   /*创建目的文件*/
  // if ((to_fd = open(argv[2], O_CREAT, 0777)) == -1)  //使用此方式后续打开文件无法写入
   if ((to_fd = open(argv[2], O_RDWR|O_CREAT, 0777)) == -1) //使用此方法后续文件可以写入
   //if((to_fd = open(argv[2], O_RDWR)) == -1)
   {
       fprintf(stderr, "Open %s Error: %s/n", argv[2], strerror(errno));
       exit(1);
   }

   /* 以下代码是一个经典拷贝代码*/

   while(bytes_read = read(from_fd, buffer, BUFFER_SIZE))
   {
       /*一个致命错误发生了*/
       if((bytes_read == -1)&&(errno != EINTR))
       {
           //printf("1\n");
           break;
       }
        else if(bytes_read > 0)
        {
            //printf("read bytes is : %d\n", bytes_read);
            ptr = buffer;
            while(bytes_write = write(to_fd, ptr, bytes_read))
            {
                /* 一个致命错误发生了 */
                if((bytes_write == -1) && (errno != EINTR))
                {
                    printf("1:%d %d\n", from_fd, bytes_write);                   
                    break;
                }
                /*  写完了所有读的字节 */
                else if(bytes_write == bytes_read) break;
                /* 之写了一部分，继续写 */
                else if(bytes_write > 0)
                {
                    ptr += bytes_write;
                    bytes_read -= bytes_write;
                }
            }
            /* 写的时候发生致命错误 */
            if(bytes_write == -1) break;
        }
   }
   close(from_fd);
   close(to_fd);
   exit(0);
}