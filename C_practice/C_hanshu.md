## memset()用法

每种类型的变量都有各种初始化的方法，memset()函数为“万能方法”，直接操作内存空间：

```c
#include <string.h>
void *memset(void *s, int c, unsigned long n);
```

函数功能为：将指针s指向的n字节单元内存用一个“整数”c替换，c为int类型，s为void *类型的指针，所以可以为任何类型的数据进行初始化，n一般用**siziof**函数获得

## sizeof()用法

## sprintf()用法

printf用于将信息输出到屏幕等设备，sprintf可将内容输出到指定字符串中

```c
int sprintf(char *buffer, const char *format, [argument]...)
/*
	buffer:指向写入的字符串指针
	format：格式化字符串，即在程序中想要的格式
	argument：可选参数，可为任意类型数据
	返回值：buffer指向字符串长度
*/
```

用法如下

- 格式化数字字符串

  ```c
  sprintf(buffer, "%d", 123456)	//执行后buffer指向字符串123456
  ```

- 连接字符串

  ```c
  #include<stdio.h>
  int main()
  {
   char buffer[10];
   char *a = "1234";
   char *b = "5678";
   sprintf(buffer, "%s%s", a, b);
   printf("%s\n", buffer);
   return 0;
  }
  //输出为123456，将a,b内容连接
  ```

## strcat()

char *strcat(char *dest, const char *src)
/*把 src 所指向的字符串追加到 dest 所指向的字符串的结尾
dest -- 指向目标数组，该数组包含了一个 C 字符串，且足够容纳追加后的字符串。
src -- 指向要追加的字符串，该字符串不会覆盖目标字符串。
该函数返回一个指向最终目标字符串dest的指针
*/
## pow() 
double pow(double x, double y);
//函数用来求 x 的 y 次幂（次方），x、y及函数值都是double型 ，其原型为：

## strstr()
char *strstr(const char *haystack, const char *needle)
/*haystack -- 要被检索的 C 字符串。
needle -- 在 haystack 字符串内要搜索的小字符串。
该函数返回在 haystack 中第一次出现 needle 字符串的位置，如果未找到则返回 null
*/
## strlen()
size_t strlen(const char *str)
com_tlen = strlen(com_tbuf);
//该函数返回字符串的长度

## strcpy()
strcpy(com_tbuf, "%01#RDD0048100488\r");

## sprintf()
sprintf(com_tbuf, " %02d#RDD0048100488\r", addr);
		com_tbuf[0] = '%';
//等效于sprintf(com_tbuf, "%%%02d#RDD0048100488**\r", addr);

## atof()
double atof(const char *str)
/*把str指向的字符串转化为一个浮点数
返回双精度浮点数，有些处理器默认返回float，如果字符串有字母或其他导致转化不成功的，则返回0；
自动检测遇到的空格，识别+-，数字字符，直到数字字符结束，只返回检测到的数字部分，如下：*/
char *str = "  +213.092fjkekfj"
float num = atof(str)	//num = 213.092

## atoi()
int atoi(const char *str)
/*把str指向的字符串转化为一个整数（int）
返回转换后的长整数，若未执行有效转换，则返回0,检测方法同上atof();
*/
## memset()
void *memset(void *str, int c, size_t n)
/*复制字符 c（一个无符号字符）到参数 str 所指向的字符串的前 n 个字符
str -- 指向要填充的内存块。
c --要被设置的值。该值以int形式传递，但是函数在填充内存块时是使用该值的无符号字符形式。
n -- 要被设置为该值的字符数。*/

  