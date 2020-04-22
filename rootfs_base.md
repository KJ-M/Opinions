# 根文件系统

## 使用BUSYBOX创建

1. 官网`https://busybox.net`下载1.29.0版本`busybox-1.29.0.tar.bz2`

2. 开发时使用`nfs`挂载根文件系统，在nfs服务器目录下创建rootfs目录

   `mkdir ~/linux/nfs/rootfs`

3. 修改Markfile文件

   `CROSS_COMPILE ?= /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-`

   `ARCH ?= arm`

   CROSS_COMPILE使用绝对路径为了防止编译出错

4. 修改源码使其支持中文字符

   `busybox-1.29.0/libbb/printable_string.c`，修改函数 `printable_string`

   `busybox-1.29.0/libbb/unicode.c`

5. 配置busybox

   有以下配置选项：

   - defconfig，默认
   - allyesconfig 全选配置
   - allnoconfig 最小配置

   此处使用默认配置`make defconfig`

   详细配置可打开图形化配置界面`make menuconfig`

6. 编译busybox

   `make install CONFIG_PREFIX=/home/mkj/linux/nfs/rootfs`
   
7. 添加lib库

   - 在rootfs中创建目录lib

   - 将`/usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/lib`中的××so××，.a文件(库文件)拷贝到lib中

     `cp *so* *.a ~/linux/nfs/rootfs/lib/ -d`	-d表示拷贝符号链接（相当与win下的快捷方式）

     其中以下为`ld-linux-armhf.so.3`文件的特殊处理（先删除再用不带-d的命令拷贝一遍）

     ```shell
     ~/linux/nfs/rootfs/lib$ ls ld-linux-armhf.so.3 -l
     lrwxrwxrwx 1 mkj mkj 24 4月  19 15:35 ld-linux-armhf.so.3 -> ld-2.19-2014.08-1-git.so
     mkj@mkj-Inspiron-5557:~/linux/nfs/rootfs/lib$ rm ld-linux-armhf.so.3 
     mkj@mkj-Inspiron-5557:~/linux/nfs/rootfs/lib$ cd /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/lib
     mkj@mkj-Inspiron-5557:/usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/lib$ cp ld-linux-armhf.so.3 ~/linux/nfs/rootfs/lib
     mkj@mkj-Inspiron-5557:/usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/lib$ cd ~/linux/nfs/rootfs/lib/
     mkj@mkj-Inspiron-5557:~/linux/nfs/rootfs/lib$ ls ld-linux-armhf.so.3 -l
     -rwxr-xr-x 1 mkj mkj 724392 4月  19 15:41 ld-linux-armhf.so.3
     ```

   - 将`/usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/lib`中的××so××，.a文件(库文件)拷贝到lib中

8. 向 rootfs 的“usr/lib”目录添加库文件

   将`/usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/usr/lib`目录下的so和.a文件拷贝到rootfs/usr/lib中
   
   ```shell
   /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/usr/lib$ cp *so* *.a /home/mkj/linux/nfs/rootfs/usr/lib/ -d
	```
   拷贝完毕后库文件即添加完成，拷贝的文件共124M

9. 在rootfs中添加其他文件夹：dev、proc、mnt、sys、tmp 和 root 等

## 测试根文件系统

linux内核中目录Documentation/filesystems/nfs/nfsroot.txt文件讲解如何通过nfs挂载根文件系统，格式为`root=/dev/nfs nfsroot=[<server-ip>:]<root-dir>[,<nfs-options>] ip=<client-ip>:<server-ip>:<gw-ip>:<netmask>:<hostname>:<device>:<autoconf>:<dns0-ip>:<dns1-ip>`各参数见驱动开发指南，可设置bootargs环境变量参考如下

`setenv bootargs 'console=ttymxc0,115200 root=/dev/nfs rw nfsroot=192.168.1.250:
/home/zuozhongkai/linux/nfs/rootfs ip=192.168.1.251:192.168.1.250:192.168.1.1:255.255.255.0::eth0:off' `

设置完之后即可启动linux，使用ls即可查看挂载的根文件系统，但会出现`can't run '/etc/init.d/rcS': No such file or directory`这样的错误，所以根文件系统还需要完善

## 完善根文件系统

1. 创建/etc/init.d/rcS文件并赋予可执行权限，规定内核启动之后启动哪些文件，如挂载文件系统，管理热插拔设备，导出环境变量...
2. 创建/etc/fstab文件，定义系统启动该挂载哪些文件
3. 创建/etc/inittab文件，关机、重启、按下ctrl+alt+del、关机等特殊情况下执行特殊process

## 测试根文件系统

### 软件运行测试

1. 测试文件的编写：

   在rootfs/drivers下创建一个hello.c测试文件，编写测试程序完成后用`arm-linux-gnueabihf-gcc hello.c -o hello`编译为可执行文件hello，查看hello文件类型和编码格式命令如下：

   ```shell
   ~/linux/nfs/rootfs/drivers$ file hello
   hello: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpret...
   ```

   可以看出hello为32位，ARM架构，动态链接的文件

2. 将测试文件在开发板终端运行

   - 在开发板中输入`./hello` 运行，使用ctrl+c终止
   - 输入`./hello &`后台运行，后台运行关闭方法：输入

   `ps`查看后天运行进程PID，使用`kill -9 PID`关闭

### 中文字符测试

在rootfs创建一个“中文测试”文件夹，进入，使用touch创建“中文测试.txt”，使用vi编辑内容：“这是一个中文测试文件！”在开发板中打开，看文件夹和文件中文是否显示正常，使用cat命令查看文件

### 开机自启动测试

在etc/init.d/rcS文件最下面输入要开机运行的命令，开机即可自动运行，可以输入

```shell
cd drivers
./hello &
cd /
```

即可开机运行hello测试程序，并回到主目录

### 外网连接测试

略。。。