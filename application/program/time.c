#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    pid_t pc,pr;
    pc = fork();
    if(pc == 0)
    {
        printf("This is the child process, pid is %d\n", getpid());
        sleep(10);
    }
    else if(pc > 0)
    {
        pr = wait(NULL);
        printf("folllow child process with pid of %d\n", pr);
    }
    exit(0);
    //execlp("ls", "ls", "-al", "/home/mkj", (char *)0);
    //execl("/bin/ls", "ls", "-al", "/home/mkj", (char *)0);
    //char *argv[] = {"ls", "-al", "/home/mkj", (char *)0};
    //execv("/bin/ls", argv);
    //int cut = 0;
    //pid_t pid;
    //pid = vfork();
    //cut++;
    //printf("count = %d\n", cut);
    //_exit(0);
    //return 0;
}