## 读入一个文件，判断文件中字母a的个数

```c
/* 
 * 读入一个文件，判断文件中字母a的个数
 * fgetc函数用于读取文件中的下一个字符，该字符为unsigned char类型，次函数将
 * 其转化为int类型并返回，遇见结束或读取错误时返回EOF(-1)
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int ch;
    int num = 0;
    FILE *fp;

    if((fp = fopen("text.txt", "r")) == NULL)
    {
        printf("open failed!\n");
        return -1;
    }

    while ((ch = fgetc(fp)) != EOF) //注意：fgetc返回值位int类型
    {
        if(ch == 'a')
        num++;
    }
    printf("%d\n", num);
    fclose(fp);
    return 0;
}

```

