#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//pipe函数练习，父进程创建管道，子进程读，父进程写
int main(void)
{
  int pipe_fd[2];
  pid_t pid;
  char buf_r[100];
  char *p_wbuf;
  int r_num;

  memset(buf_r, 0, sizeof(buf_r));

  //创建管道
  if(pipe(pipe_fd) < 0)
  {
      printf("pipe create error!\n");
      return -1;
  }
  //创建子进程
  if((pid = fork()) == 0)
  {
      printf("\n");
      close(pipe_fd[1]);
      sleep(2);
      if((r_num = read(pipe_fd[0], buf_r, 100)) > 0)
      {
          printf("%d numbers read from pipe is %s\n", r_num, buf_r);
      }
      close(pipe_fd[0]);
      exit(0);
  }
  else if((pid = fork()) > 0)
  {
      close(pipe_fd[0]);
      if(write(pipe_fd[1], "hello", 5) > 0) //此处为什么是5而不是6
            printf("parent write hello\n");
      if(write(pipe_fd[1], "man", 4) > 0)
            printf("parent write man\n");
    close(pipe_fd[1]);
    sleep(3);
    waitpid(pid, NULL, 0);
    exit(0);

  }

}