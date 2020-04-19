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

