# 设备树下的led驱动

在使用设备树的情况下，可以设备的寄存器地址，通过使用读取设备树节点属性值的of函数完成地址的获取，进而配置相应寄存器配置（本次目次是熟悉设备树的使用）

步骤如下：

## 1、修改设备树文件

打开`imx6ull-alientek-emmc.dts`文件，在根节点/下创建一个子节点如下：

```dts
alphaled {
		#address-cells = <1>;
		#size-cells = <1>;
		compatible = "atkalpha-led";
		status = "okay";
		reg = < 0x020c406c 0x04
				0x020e0068 0x04
				0x020e02f4 0x04
				0x0209c000 0x04
				0x0209c004 0x04 >;
	};
```

reg属性保存了需要配置的寄存器的值，保存后在linux源码根目录使用`make dtbs`命令编译设备树

## 2、程序代码中设备树的引用

在设备结构体中添加一个设备节点变量

```c
struct newchr{
    dev_t devid;             //设备号
    struct cdev cdev;        //cdev
    struct class *class;     //class
    struct device *device;   //device
    int major;
    int minor;  
    struct device_node *nd  //设备节点
};
```

在驱动入口函数中使用新添加的设备节点来操作设备树内容：

```c
	int ret = 0;
    u32 val = 0;
    u32 regdata[14];
    const char *str;
    struct property *proper; 
	/* 获取设备树中的属性数据 */
    /* 1、获取设备节点：alphaled */
    newchrled.nd = of_find_node_by_path("/alphaled");
    if(newchrled.nd == NULL){
        printk("alphaled node can not found!\r\n");
        return -EINVAL;
    }else{
        printk("alphaled node has been found!\r\n");
    }

    /* 2、获取compatible属性内容 */
    proper = of_find_property(newchrled.nd,"compatible",NULL);
    if(proper == NULL){
        printk("compatible property find failed!\r\n");
    }else{
        printk("compatible = %s\r\n",(char*)proper->value);
    }
    /* 3、获取status属性内容 */
    ret = of_property_read_string(newchrled.nd, "status", &str);
    if(ret < 0){
        printk("status read failed!\r\n");
    }else{
        printk("status = %s\r\n",str);
    }
    /* 4、获取reg属性内容 */
    ret = of_property_read_u32_array(newchrled.nd, "reg", regdata, 10);
    if(ret < 0){
        printk("reg property read failed!\r\n");
    }else{
        u8 i = 0;
        printk("reg data:\r\n");
        for(i = 0; i < 10; i++)
            printk("%#X ", regdata[i]);
        printk("\r\n");
    }
```

使用以下两种方式（函数）实现虚拟地址映射：

```c
#if 0
    CCM_CCGR1 = ioremap(regdata[0], regdata[1]);
    SW_MUX_GPIO1_IO03 = ioremap(regdata[2], regdata[3]);
    SW_PAD_GPIO1_IO03 = ioremap(regdata[4],regdata[5]);
    GPIO1_DR = ioremap(regdata[6], regdata[7]);
    GPIO1_GDIR = ioremap(regdata[8],regdata[9]);
    #else
    CCM_CCGR1 = of_iomap(newchrled.nd, 0);
    SW_MUX_GPIO1_IO03 = of_iomap(newchrled.nd, 1);
    SW_PAD_GPIO1_IO03 = of_iomap(newchrled.nd, 2);
    GPIO1_DR = of_iomap(newchrled.nd, 3);
    GPIO1_GDIR = of_iomap(newchrled.nd, 4);
    #endif

注意：
    reg = < 	0x020c406c 0x04
				0x020e0068 0x04
				0x020e02f4 0x04
				0x0209c000 0x04
				0x0209c004 0x04 >
    所以：以上#else前面函数中参数：
    		regdata[0]，regdata[1]
    		regdata[2],regdata[3]
    		regdata[4],......
    	 与reg值一一对应
    else后面函数中参数0 1 2 3 4对应每一行内容
    reg参数两个为一组
```

3、其余部分与之前驱动编写配置完全一样，总之，此处使用设备树只是变了一下寄存器地址的读取方式