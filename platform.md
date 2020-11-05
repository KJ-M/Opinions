## platform总线基础

linux内核总线结构体：**bus_type**,在include/linux/device.h中

->platform总线是bus_type的一个具体实例，在 drivers/base/platform.c中:

```c
struct bus_type platform_bus_type = {
	.name = "platform",
	.dev_groups = platform_dev_groups,
    .match = platform_match,
    .uevent = platform_uevent,
	.pm = &platform_dev_pm_ops,
}
```

->可见platform_match为设备和驱动匹配函数，定义在 drivers/base/platform.c 中

```c
static int platform_match(struct device *dev, struct device_driver *drv)
{
    struct platform_device *pdev = to_platform_device(dev);
    struct platform_driver *pdrv = to_platform_driver(drv);

    /* When driver_override is set, only bind to the matching driver */
    if (pdev->driver_override)
        return !strcmp(pdev->driver_override, drv->name);

    /* Attempt an OF style match first */
    if (of_driver_match_device(dev, drv))	//1
        return 1;

    /* Then try ACPI style match */
    if (acpi_driver_match_device(dev, drv))	//2
        return 1;

    /* Then try to match against the id table */
    if (pdrv->id_table)
        return platform_match_id(pdrv->id_table, pdev) != NULL;	//3

    /* fall-back to driver name match */
    return (strcmp(pdev->name, drv->name) == 0);	//4
}
```

四种匹配方式：

1. OF类型匹配，设备树采取的匹配方式
2. ACPI匹配
3. id_table匹配
4. 比较驱动和设备的name字段（比第三种更常用）

## platform驱动

platform_driver,定义在include/linux/platform_device.h



## 网上资料（待整理）

在这里我简单说一下match方法何时被调用(理解这一点对于理解整个设备驱动模型起到一定的帮助)。当一个驱动挂接到该总线的时候，该总线的match方法被调用，在这里，platform总线的match方法被赋值为platform_match，也就是说platform_match将被调用，platform_match将会帮驱动找到匹配的设备。同样的，当一个设备挂接到该总线时，platform_match也会被调用，platform_match也会帮该设备找到匹配的驱动。用一句话来说就是，platform_match既帮驱动找对象，也帮设备找对象。当驱动和对象匹配上了，platform_match可是会收两家的媒婆钱，黑心的很。

　　那么对于platform总线来说，驱动和设备如何挂接到该总线上呢。platform总线分别提供了两个函数给驱动和设备使用。如下所示：

　　int platform_driver_register(struct platform_driver *drv)

　　int platform_device_register(struct platform_device *pdev)

　　很显然platform_driver_register 是给驱动使用的，platform_device_register 是给设备用的。