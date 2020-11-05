# Linux移植

教程简单复制相关文件重命名即可启动，以下为其余要修改的参数

## 主频相关

### 查看主频信息

`cat /proc/cpuinfo		#查看CPU信息，参数BogoMIPS越大主频越大`
`cd /sys/bus/cpu/devices/cpu0/cpufreq/		#该目录下文件保存CPU详细信息`

通过设置`imx_alientek_emmc_defconfig.h`中的`CPU_FREQ`相关来设置模式，调整主频

## 使能8线EMMC驱动

用到设备树相关知识，修改相关`.dts`文件即可

## 网络驱动修改

修改设备树文件即可

<u>修改完后网口2可以使用，即eth0可用，eth1能检测到，但是无法ping通电脑，查一下解决方法，看是不是哪里配置错了。</u>

## 保存图形界面的配置

网络驱动修改部分使用到了图形化界面配置，清理工程之后配置就会消失，可以将`.config`文件直接保存为对应板子的`defconfig`文件。（在uboot中defconfig文件只有少量内容，但linux中有很多内容，且可以直接用编译生成的`.config`文件重命名直接取代）