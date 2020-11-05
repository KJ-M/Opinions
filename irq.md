## memset用法

每种类型的变量都有各种初始化的方法，memset()函数为“万能方法”，直接操作内存空间：

```c
#include <string.h>
void *memset(void *s, int c, unsigned long n);
```

函数功能为：将指针s指向的n字节单元内存用一个“整数”c替换，c为int类型，s为void *类型的指针，所以可以为任何类型的数据进行初始化，n一般用**siziof**函数获得