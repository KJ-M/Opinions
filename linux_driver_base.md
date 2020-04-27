```c
module_init(iii)	//模块入口函数注册iii入口函数名
module_exit(ooo)	//模块出口函数注册ooo出口函数名
```

参考其他驱动模块的驱动入口出口格式，写自己的驱动

```Makefile
KERNELDIR := /home/mkj/linux/linux_nxp_to_alientek/linux-imx-rel_imx_4.1.15_2.1.0_ga
CURRENT_PATH := $(shell pwd)
obj-m := chrdevbase.o
build: kernel_modules
kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean
```

# 字符设备开发过程

## 新建工程

vscode建立工程，新建.vscode文件夹，添加对应linux目录-三个：

```c
"/home/mkj/linux/linux_nxp_to_alientek/linux-imx-rel_imx_4.1.15_2.1.0_ga/include",
"/home/mkj/linux/linux_nxp_to_alientek/linux-imxrel_imx_4.1.15_2.1.0_ga/arch/arm/include",
"/home/mkj/linux/linux_nxp_to_alientek/linux-imx-rel_imx_4.1.15_2.1.0_ga/arch/arm/include/generated"
```

## 驱动编写

### 模块加载卸载

```c
static int __init chrdev_init(void)		//驱动入口出口函数

static void __exit chrdev_exit(void)	

module_init(chrdev_init);				//驱动模块加载卸载函数

module_exit(chrdev_exit);
```

以上四个函数完成即可在开发板测试模块的加载和卸载

## Makefile

```Makefile
KERNELDIR := /home/mkj/linux/linux_nxp_to_alientek/linux-imx-rel_imx_4.1.15_2.1.0_ga
CURRENTPATH := $(shell pwd)
obj-m := chrdev.o
build: kernel_modules
kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENTPATH) modules	
clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENTPATH) clean
```

以上，-C表示将当前工作目录切换到指定源码目录中去，M表示模块源码目录，“make modules”命令中加入M=dir程序会自动到指定dir中读取模块源码并将其编译成.ko文件，生成.ko文件即可下载到开发板中测试

## 测试模块加载和卸载

### 模块相关的命令

- lsmod 将已经加载的模块列出来
- rmmod 卸载已经加载的模块
- modprobe加载现有的模块（insmod也可，但没这个功能强大）
- depmod自动生成modules.dep文件

将.ko文件拷贝到/lib/modules/4.1.15中执行以上命令即可完成模块的加载与卸载，本质是通过模块相关命令调用模块加载和卸载函数进而调用驱动入口和出口函数

## 字符设备的注册与注销

字符设备的注册和注销函数：

```c
static inline int register_chrdev(unsigned int major, const char *name,
const struct file_operations *fops)
static inline void unregister_chrdev(unsigned int major, const char *name)
```

major：主设备号，name：设备名字，fops：file_operations类型的结构体指针[^1]

file_operations结构体里定义了设备驱动函数的集合，在驱动入口和出口函数中调用字符设备注册和注销函数

```c
static int __init chrdev_init(void)
{
/* 入口函数具体内容 */
    int ret = 0;
    ret = register_chrdev(MAJOR,name,&chrdev_fops);
    if (ret < 0){/*注册失败*/ }
    return 0;
}
static void __exit chrdev_exit(void)
{
 /* 出口函数具体内容 */
    unregister_chrdev(MAJOR,name);
}
```

注册成功后可以在`/proc/devices`中查看注册的设备号

## 字符设备操作的具体实现

```c
static int chrdev_release (struct inode * inode, struct file *file)
{
    printk("chrdev release~\r\n");
    return 0;
}
static ssize_t chrdev_read (struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    return 0;
}
static ssize_t chrdev_write (struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    return 0;
}

static int chrdev_open (struct inode *inode, struct file *file)
{
    printk("chrdev open~\r\n");
    return 0;
}

static const struct file_operations chrdev_fops = {
    .owner  = THIS_MODULE,
     .read   = chrdev_read,
     .write = chrdev_write,
     .open   = chrdev_open,
    .release = chrdev_release,
};
```



## 添加license和作者信息

```C
MODULE_LICENSE("GPL");
MODULE_AUTHOR("MKJ");
```

## 完善字符设备读写操作

```c
char writebuf[100];
char writeoutbuf[] = "things write to user";

static int chrdev_release (struct inode * inode, struct file *file)
{
  //  printk("chrdev release~\r\n");
    return 0;
}
static ssize_t chrdev_read (struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    int ret = 0;
    ret = copy_to_user(buf,writeoutbuf,count);
    if(ret != 0){
        printk("copy_to_user failed!\r\n");
    }
    return 0;
}
static ssize_t chrdev_write (struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    int ret = 0;
    ret = copy_from_user(writebuf,buf,count);
    if(ret != 0){
        printk("copy_from_user failed!\r\n");
    }else{
        printk("write data are :%s\r\n",writebuf);
    }
    return 0;
}

static int chrdev_open (struct inode *inode, struct file *file)
{
   // printk("chrdev open~\r\n");
    return 0;
}
```

读写操作用到了函数`static inline long copy_to_user(void __user *to, const void *from, unsigned long n)`和函数`copy_from_user()`,来完成内核数据和用户数据的传递，因为用户内核数据不能直接被对方操作。

## 测试APP的编写

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char writetodev[] = "write things to dev!";
char writebuf[100];
char readbuf[100];

/* argc : argv数组元素个数
   return ：0成功，其他失败
 */
int main(int argc, char *argv[])
{
    int ret = 0,fd =0;
    if(argc != 3){
        printf("para input wrong!");
        return 0;
    }
    ret = open(argv[1],O_RDWR); //new file descriptor
    if(ret == -1){
        printf("open file error!\r\n");
        return 0;
    }
    fd = ret;
    if(atoi(argv[2]) == 1){
    ret = write(fd,writetodev,50);
    if(ret == -1){
        printf("write error!\r\n");
    }
    }
    if(atoi(argv[2]) == 2){
    ret = read(fd,readbuf,50);
    if(ret == -1){
        printf("read error!\r\n");
    }else{
        printf("read words are:%s\r\n",readbuf);
    }
    }
    ret = close(fd);
    if(ret == -1){
        printf("close file error!\r\n");
        return 0;
    }
}
```

- `int main(int argc, char *argv[]){}`argc为参数个数，argv为参数，如使用时：

  `./chrdevAPP /dev/chrdev 1`argc为3，即参数三个，`argv[0]="chrdevAPP",argv[1]="/dev/chrdev",argv[2]="1"`,都为字符串类型

- 测试APP使用了系统调用函数read,write,open,close,这些函数可使用man (1/2/3) read/write命令查看具体使用方法，使用了`atoi(argv[2])`函数将字符串类型转换为整形

## 最终测试

1. 加载模块：

   - `depmod `

   - `modprobe chrdev.ko`

2. 查看设备号是否正常：`cat/proc/devices`

3. 注册设备节点：

   - `mknod /dev/chrdev c 200 0`		//c代表字符设备，200 0代表主次设备号
   - `ls /dev`										//查看设备节点是否注册成功

4. 运行测试命令：

   - `./chrdevAPP /dev/chrdev 1		//读`
   - `./chrdevAPP /dev/chrdev 2		//写`





[^1]: 此结构体见以下字符设备操作具体实现