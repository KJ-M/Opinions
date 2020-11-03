#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main(void)
{
    pid_t pid;
    pid = fork();
    if(pid < 0)
        printf("error in fork!\n");  
    else if(pid == 0)
        printf("child process,ID:%d!\n", getpid());  
    else
        printf("parent process,ID:%d!child ID is %d\n", getpid(),pid);  
    return 0;
}