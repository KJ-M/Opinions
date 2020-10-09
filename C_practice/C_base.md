# C语言内存

## 指针基础

### 指针修饰符
#### const    常量，只读，不能变

- const char *p = char const *p,

    p is a pointer to const char

    p可任意指向，但指向的内容不允许修改，类似于字符串“hello world!”

- char * const p = char *p const

    const p is a pointer to char

    p指向的位置固定，内容可变，一般为硬件资源，寄存器地址等

- const char * const p

    const p is a pointer to const char

    指向内容和位置都不许变,一般为ROM设备

## 数组

原理：另外一种对内存的操作方式，本质上跟指针是一样的

- int a[100]

a是个常量标签，不是指针，出现a = xxx时是错误的，a++也错（相当于a+=1）

