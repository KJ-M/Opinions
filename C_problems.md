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

  