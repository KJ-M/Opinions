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
## 国标212CRC计算
```c
unsigned int CRC16_Checkout ( unsigned char *puchMsg, unsigned int usDataLen ) 
{ 
unsigned int i,j,crc_reg,check; 
crc_reg = 0xFFFF; 
for(i=0;i<usDataLen;i++) 
{ 
	crc_reg = (crc_reg>>8) ^ puchMsg[i]; 
	for(j=0;j<8;j++) 
	{ 
	check = crc_reg & 0x0001; 
	crc_reg >>= 1; 
	if(check==0x0001) 
		{ 
			crc_reg ^= 0xA001; 
		} 
	} 
} 
return crc_reg; 
}
/************************************************
crc
QN=20160801085857223;ST=32;CN=1062;PW=100000;MN=010000A8900016F000169DC0;Flag=5;CP=&&RtdInterval=30&&
crc：1C80
 
1) CRC16 校验寄存器赋值为 0xFFFF； 
2) 取被校验串的第一个字节赋值给临时寄存器； 
3) 临时寄存器与 CRC16 校验寄存器的高位字节进行“异或”运算，赋值给 CRC16 校验寄存器； 
4) 取 CRC16 校验寄存器最后一位赋值给检测寄存器； 
5) 把 CRC16 校验寄存器右移一位； 
6) 若检测寄存器值为 1，CRC16 校验寄存器与多项式 0xA001 进行“异或”运算，赋值给 CRC16校验寄存器； 
7) 重复步骤 4~6，直至移出 8 位； 
8) 取被校验串的下一个字节赋值给临时寄存器； 
9) 重复步骤 3~8，直至被校验串的所有字节均被校验； 
10) 返回 CRC16 校验寄存器的值。 
校验码按照先高字节后低字节的顺序存放。
******************************************************/
```