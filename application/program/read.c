#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
    int from_fd;
    char read_buf[30];
    if ((from_fd = open("a.txt", O_RDWR)) == -1)
    {
        printf("open error!\n");
       exit(1);
    }
    //write(from_fd, "abcde", 6);
    //write(from_fd, "fg", 3);
    memset(read_buf, 0, sizeof(read_buf));
    read(from_fd, read_buf, 10);
    printf("read from a.txt is %s\n", read_buf);
}
