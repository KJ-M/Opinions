pinctrl和gpio子系统是为了简化gpio配置步骤，直接使用现成的函数配置io，类似于stm32中的库函数功能，可以在驱动中省去寄存器的配置，此处省去了原理性分析，直接应用

pinctrl子系统用来配置引脚属性

gpio子系统用来将配置好的引脚和设备联系起来，并提供引脚操作函数如读、写等等

## 遇到问题：

### 1、释放IO

**一定记得在卸载驱动时释放IO！！！！！**

### 2、

```c
static ssize_t beep_write (struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    int ret = 0;
    unsigned char databuf[1];
    unsigned char beepstat;
    struct beep_dev *dev = file->private_data;
    ret = copy_from_user(databuf, buf, count);
    if(ret < 0) {
        printk("kernel write failed!\r\n");
        return -EFAULT;
    }
    beepstat = databuf[0];//非常重要,不使用beepstat直接读databuf会出错
    if(beepstat == 1) {
        gpio_set_value(dev->beep_gpio, 0);
    }else if(beepstat == 0) {
        gpio_set_value(dev->beep_gpio, 1);
    }
    return 0;
}
```

在write函数中，必须要用beepstat变量，不知为什么

## 设备树的修改

**在配置gpio前一定要检查以下引脚是否已经被使用！！！！！**

在iomuxc子节点中添加节点：

```dts
pinctrl_beep: beepgrp {
			fsl,pins = <
				MX6ULL_PAD_SNVS_TAMPER1__GPIO5_IO01	0X10B0 /*BEEP*/	
			>;
		};
```

注意：添加的节点命名方式要规范，`MX6ULL_PAD_SNVS_TAMPER1__GPIO5_IO01`在设备树目录下`imx6ul-pinfunc.h`和`imx6ull-pinfunc.h`中寻找，

```c
#define MX6ULL_PAD_SNVS_TAMPER1__GPIO5_IO01    0x000C 0x0050 0x0000 0x5 0x0
```

后面5个数字的含义分别是各寄存器偏移地址，具体见文档，可根据这些值判断是否为对应的引脚，一般不需要特地检查，官方配置好的，子节点属性中0x10b0是引脚电气属性

在根节点/中添加设备子节点（照猫画虎）：

```dts
beep {
		#address-cells = <1>;
		#size-cells = <1>;
		compatible = "atkalpha-beep";
		pinctrl-names = "default";
		pinctrl-0 = <&pinctrl_beep>;
		beep-gpio = <&gpio5 1 GPIO_ACTIVE_HIGH>;
		status = "okay";
	};
```

设备树修改完毕，**记得编译并更新设备树文件即可**

## 驱动文件修改

**先创建一个字符设备驱动框架，包括自动创建模块部分，编译并测试可以成功加载模块即可进行下一步**

在设备结构体中添加所操作的gpio编号`int beep_gpio;`

在驱动入口函数中添加初始化设备代码（使用gpio子系统初始化而不是以前的寄存器配置）

```c
/* 初始化beep */
    beep.nd = of_find_node_by_path("/beep");//获取节点
    if(beep.nd == NULL){
        ret = -EINVAL;
        goto fail_nd;
    }
    beep.beep_gpio = of_get_named_gpio(beep.nd, "beep-gpio", 0);//获取gpio编号
    if(beep.beep_gpio < 0) {
        ret = EINVAL;
        goto fail_nd;
    }
    
    ret = gpio_request(beep.beep_gpio,"beep_gpio");//提交对应编号的gpio申请（被其他设备使用过得话就会申请失败）
    if(ret) {
        printk("can't request beep gpio\r\n");
        goto fail_nd;
    }
    
    gpio_direction_output(beep.beep_gpio, 1);//设置gpio默认输出为1
    if(ret < 0){
        goto fail_set;
    }
```

在驱动出口函数最后添加释放gpio编号函数`gpio_free(beep.beep_gpio);`



## 驱动规范源码：

```c
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/ide.h>
#include <asm/io.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>

#define BEEP_NAME "beep"
#define BEEP_CNT 1

/* beep结构体 */
struct beep_dev {
    dev_t devid;
    struct cdev cdev;
    struct class *class;
    struct device *device;
    int major;
    int minor;
    struct device_node *nd;
    int beep_gpio;
};
struct beep_dev beep;

static int beep_open (struct inode *inode, struct file *file)
{
    file->private_data = &beep; //设置私有数据
    return 0;
}
static int beep_release (struct inode * inode, struct file *file)
{
    return 0;
}
static ssize_t beep_read (struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    return 0;
}
static ssize_t beep_write (struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    int ret = 0;
    unsigned char databuf[1];
    unsigned char beepstat;
    struct beep_dev *dev = file->private_data;
    ret = copy_from_user(databuf, buf, count);
    if(ret < 0) {
        printk("kernel write failed!\r\n");
        return -EFAULT;
    }
    beepstat = databuf[0];//非常重要
    if(beepstat == 1) {
        gpio_set_value(dev->beep_gpio, 0);
    }else if(beepstat == 0) {
        gpio_set_value(dev->beep_gpio, 1);
    }
    return 0;
}
static const struct file_operations beep_fops = {
    .owner = THIS_MODULE,
    .read = beep_read,
    .open = beep_open,
    .write = beep_write,
    .release = beep_release,
};
/* 驱动入口函数 */
static int __init beep_init(void)
{
    int ret = 0;
    /* 注册字符设备驱动 */
    beep.major = 0;
    if(beep.major) {
        beep.devid = MKDEV(beep.major, 0);
        ret = register_chrdev_region(beep.devid, BEEP_CNT, BEEP_NAME);
    }else {
        ret = alloc_chrdev_region(&beep.devid, 0, BEEP_CNT, BEEP_NAME);
        beep.major = MAJOR(beep.devid);
        beep.minor = MINOR(beep.devid);
    }
    if(ret < 0) {
        goto fail_devid;
    }
    printk("major is :%d,minor is:%d\r\n",beep.major,beep.minor);
    /* 初始化cdev结构体 */
    beep.cdev.owner = THIS_MODULE;
    cdev_init(&beep.cdev, &beep_fops);

    /* 添加一个cdev */
    ret = cdev_add(&beep.cdev,beep.devid,BEEP_CNT);
    if(ret){
        goto fail_cdev_add;
    }
    /* 创建类 */
    beep.class = class_create(THIS_MODULE, BEEP_NAME);
    if (IS_ERR(beep.class)) {
        ret = PTR_ERR(beep.class);
        goto fail_class;
    }
    /* 创建设备 */
    beep.device = device_create(beep.class, NULL, beep.devid,NULL, BEEP_NAME);
    if(IS_ERR(beep.device)){
        ret = PTR_ERR(beep.device);
        goto fail_device;
    }
    /* 初始化beep */
    beep.nd = of_find_node_by_path("/beep");
    if(beep.nd == NULL){
        ret = -EINVAL;
        goto fail_nd;
    }
    beep.beep_gpio = of_get_named_gpio(beep.nd, "beep-gpio", 0);
    if(beep.beep_gpio < 0) {
        ret = EINVAL;
        goto fail_nd;
    }
    
    ret = gpio_request(beep.beep_gpio,"beep_gpio");
    if(ret) {
        printk("can't request beep gpio\r\n");
        goto fail_nd;
    }
    
    gpio_direction_output(beep.beep_gpio, 1);
    if(ret < 0){
        goto fail_set;
    }

    return 0;
fail_set:
    gpio_free(beep.beep_gpio);
fail_nd:
    device_destroy(beep.class, beep.devid);

fail_cdev_add:
    unregister_chrdev_region(beep.devid,1);  //注销设备号
fail_class:
    cdev_del(&beep.cdev);  //删除cdev
fail_device:
    class_destroy(beep.class);
fail_devid:
    return ret;
}
/* 驱动出口函数 */
static void __exit beep_exit(void)
{
    /* 关闭蜂鸣器 */
    gpio_set_value(beep.beep_gpio,1);
    /* 注销字符设备beep */
    cdev_del(&beep.cdev);  //删除cdev
    unregister_chrdev_region(beep.devid,1);  //注销设备号
    /* 删除设备 */
    device_destroy(beep.class, beep.devid);
    /* 删除类 */
    class_destroy(beep.class);

    gpio_free(beep.beep_gpio);
}
/* 驱动模块加载卸载 */
module_init(beep_init);
module_exit(beep_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MKJ");
```

