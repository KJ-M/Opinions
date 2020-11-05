#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main(void)
{
    int cut = 0;
    pid_t pid;
    pid = vfork();
    cut++;
    printf("count = %d\n", cut);
    _exit(0);
    return 0;
}