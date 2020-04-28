# LED驱动基础

此部分主题驱动框架参考linux_driver_base的框架

需要添加以下部分：

## 寄存器物理地址映射为虚拟地址

```c
/* 寄存器物理地址 */
#define CCM_CCGR1_BASE 0X020C406C
#define GPIO1_DR_BASE 0X0209C000        //OUTPUT_LEVEL:0/1
#define GPIO1_GDIR_BASE 0X0209C004      //INPUT/OUTPUT
#define IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03_BASE 0X020E0068
#define IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03_BASE 0X020E02F4

/* 映射后寄存器虚拟地址指针声明！！！！！！！！！！ */
static void __iomem* CCM_CCGR1;
static void __iomem* GPIO1_DR;
static void __iomem* GPIO1_GDIR;
static void __iomem* SW_MUX_GPIO1_IO03;
static void __iomem* SW_PAD_GPIO1_IO03;
```

**以上部分在驱动最开始出定义，在驱动入口函数中调用映射函数：**

```c
 /* 地址映射 */
    CCM_CCGR1 = ioremap(CCM_CCGR1_BASE,4);
    GPIO1_DR = ioremap(GPIO1_DR_BASE,4);
    GPIO1_GDIR = ioremap(GPIO1_GDIR_BASE,4);
    SW_MUX_GPIO1_IO03 = ioremap(IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03_BASE,4);
    SW_PAD_GPIO1_IO03 = ioremap(IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03_BASE,4);
```

**有映射就有解除映射，在驱动出口函数中调用iounmap函数**

```c
static void __exit led_exit(void)
{
    /* 取消映射！！！！！！！！！！ */
    iounmap(CCM_CCGR1);
    iounmap(GPIO1_DR);
    iounmap(GPIO1_GDIR);
    iounmap(SW_MUX_GPIO1_IO03);
    iounmap(SW_PAD_GPIO1_IO03);
    /* 注销字符设备led */
    unregister_chrdev(MAJORR, NAME);
}
```

## 外设初始化部分

**外设初始化使用的地址为以上的虚拟地址，初始化定义在在驱动入口函数中**

```c
/* 使能时钟 */
    val = readl(CCM_CCGR1);
    val |= 3 << 26;
    writel(val,CCM_CCGR1);
    /* 设置复用为GPIO */
    writel(5,SW_MUX_GPIO1_IO03);
    /* 设置IO电气属性 */
    writel(0X10B0,SW_PAD_GPIO1_IO03);
    /* 设置为输出功能 */
    val = readl(GPIO1_GDIR);
    val &= ~(1<<3);  //清除以前的设置
    val |= (1<<3);  //设置为输出
    writel(val,GPIO1_GDIR);
    /* 设置默认关闭led */
    val = readl(GPIO1_DR);
    val |= (1<<3);
    writel(val,GPIO1_DR);
```

此部分为外设初始化，跟裸机开发不同的是，内核不建议直接访问寄存器，使用专用函数对寄存器内存进行读写操作

```c
//8位，16位，32位读操作函数
u8 readb(const volatile void __iomem *addr)
u16 readw(const volatile void __iomem *addr)
u32 readl(const volatile void __iomem *addr)
//8位，16位，32位写操作函数
void writeb(u8 value, volatile void __iomem *addr)
void writew(u16 value, volatile void __iomem *addr)
void writel(u32 value, volatile void __iomem *addr)
```

初始化完成之后即可调用字符设备注册函数：

```c
 ret = register_chrdev(MAJORR,NAME,&led_fops);
    if(ret < 0){
        printk("retist failed!\r\n");
        return -EIO;
    }
```

**<u>注意：此处return -EIO为linux特殊的return值，暂时先记住就行，慢慢总结使用规律</u>**

## 控制led亮灭函数（.write函数）

```c
static ssize_t led_write (struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    int ret = 0;
    unsigned char databuf[1];
    unsigned char ledstat;
    ret = copy_from_user(databuf,buf,count);
    if(ret < 0){
        printk("kernel write failed!\r\n");
        return -EFAULT;
    }
    ledstat = databuf[0];
    if(ledstat == LEDON){
        led_switch(LEDON);
    }else if(ledstat == LEDOFF){
        led_switch(LEDOFF);
    }
    return 0;
}
```

此处的return -EFAULT跟上面的return一样效果，led_switch()切换LED亮灭

```c
/* 切换led状态 */
void led_switch(u8 sta)
{
    u32 val = 0;
    if(sta == LEDON){
        val = readl(GPIO1_DR);
        val &= ~(1 << 3);
        writel(val,GPIO1_DR);
    }else if(sta == LEDOFF){
        val = readl(GPIO1_DR);
        val |= (1 << 3);
        writel(val,GPIO1_DR);
    }
}
```



## 测试APP的编写

```c
int main(int argc,char *argv[])
{
    int ret = 0,fd = 0;
    char *filename;
    unsigned char databuf[1];
    if(argc != 3){
        printf("param input error!\r\n");
        return -1;				//!!!!!!!!!!!!!!!!!!!!!!!
    }
    filename = argv[1];
    fd = open(filename,O_RDWR);
    if(fd < 0){
        printf("open file error!\r\n");
        return -1;				//!!!!!!!!!!!!!!!!!!!!
    }
    databuf[0] = atoi(argv[2]);//!!!!!!!!!!!!!!!!!!!!!!!!
    ret = write(fd,databuf,sizeof(databuf));
    if(ret < 0){
        printf("led control fialed!\r\n");
        close(fd);
        return -1;				//!!!!!!!!!!!!!!!!
    }
    ret = close(fd);
    if(ret < 0){
        printf("closefileerror!\r\n");
        return -1;				//!!!!!!!!!!!1
    }
    return 0;
}
```

**注意：**

- **return -1的使用**
- **`databuf[0] = atoi(argv[2]);`中，`atoi()`是将字符串类型转为int类型，databuf为unsigned char类型，所以说int和unsigned char通用？？？**