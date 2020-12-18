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
## 排序算法
```
int cacl(int *n, int num)	//冒泡排序
			{
				int i,j;
				for(i = 0; i < num-1; ++i)
				{
					for(j = 0;j < num-1; ++j)
					{
						if (n[j]<n[j+1])
							{
							n[j] = n[j] ^ n[j+1];
							n[j+1] = n[j] ^ n[j+1];
							n[j] = n[j]^n[j+1];
							}
					}
				}
				return 0;
			}
int cal(int *n, int num)	//选择排序

		{
			int i,j;
			for (i = 0; i < num -1; ++i)
				{
				for (j = i+1; j < num; ++j)
					{
					if (n[i]>n[j])
						{
						n[i] = n[i] ^ n[j];
						n[j] = n[i] ^ n[j];
						n[i] = n[i] ^ n[j];
						}
					}
				}
			return 0;
		}
```
## 交换量数值最简单可靠方法
```
^:异或，相同为1
a = a^b;
b = a^b;
a = a^b;
```
## 二分法查找
```
int find(int *arry, int nu, int find_nu)
{
	int start,end,mid;
	start = 0;
	end = nu;
	mid = (start+end)/2;
	while((start < end)&&(arry[mid] != find_nu))
	{
		if(arry[mid] > find_nu)
		{
			start = mid + 1;
			mid = (start+end)/2;
		}
		else
		{
			end = mid -1;
			mid = (start + end)/2;
		}
	}
	if(arry[mid] != find_nu)
	{
		printf("no match!\n");
		return 0;
	}
	else
	{
		printf("find OK, num is:%d\n", mid);
		return mid;
	}
		
}	
```	