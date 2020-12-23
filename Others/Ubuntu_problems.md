## Ubuntu系统安装
1. 如果系统设置为GPT+UEFI模式，则不用设置/boot分区，直接设置EFI分区512M即可
2. 其他分区：
/: --系统根目录，一定要有，可以只有这个，其他都不要，类似于C盘
/swap: --交换分区，一般为电脑内存一半大小，内存不够用了可以使用，此分区是否要看个人需求
/home:	/usr: --个人文件存放位置，软件存放位置，分区则用，不分区自动在/:分区下生成相应目录，分区好处是系统崩了重装系统的话个人文件软件不会被清除
3. 启动管理器
Windows下：Windows boot manager
Ubuntu下： ubuntu….

## 磁盘挂载相关:
注意：以下说的挂载是指挂载的磁盘分区，如/dev/sdb为sd卡，不是分区，不可挂载，
/dev/sdb1为sd卡的分区之一，就可以挂载
单独的mount命令可查看磁盘挂载点
单独的df命令可查看磁盘分区使用情况和挂载点
使用fdisk-l可最详细的查看系统磁盘信息，包括已分区未分区，但没有挂载信息
以上三者查看磁盘方式可以交替使用
一个磁盘空间可以使用挂载命令挂载许多次，但取消挂载时也要原路返回许多次，类似于入栈出栈，sd卡刚插入的时候默认挂载到media文件夹下，使用umount命令卸载之后使用df或者mount命令就看不到sd卡挂载信息了，取消挂载信息后就可以进行格式化，分区等操作。

![](1.png)
使用fdisk对磁盘分区进行增删，分完区用mkfs进行格式化
对于SD卡，命令sudo fdisk /dev/sdb可进入fdisk设置界面，通过指示输入不同命令可完成对SD卡的分区，显示详细信息，分区type设置，可设置分区大小，分区完成后使用mkfs进行格式化
此处分区type和格式化的文件类型似乎关系不大，所以关注格式化时设置的文件类型，一般使用vfat格式化，即使用下图中的第一行
![](2.png)
格式化完成即可使用mount或者umount进行挂载卸载

## 解决sudo apt-get update命令执行问题:
/etc/apt/sources.list文件里保存了apt-get update对应的源，该命令为参考sources.list中的源更新本地软件库，比如增加新的源，就需要update一下来同步，才能进行安装对应软件，不同步就找不到软件
![](3.png)
![](4.png)

## Ubuntu查看文件夹内存大小：
在文件夹中输du -sh可查看文件夹所占内存

## Ubuntu下常用解压命令：
tar -vxjf uboot-imx-2016.03-2.1.0-g8b546e4.tar.bz2

## U盘拷贝时sync同步
Ubuntu往U盘考文件不显示进度，系统会每隔一段时间同步缓冲区的文件，所以，以防万一，需要在命令行输入sync完成同步
Sync：即synchronize 使同步

## 搜索命令find，grep：
使用命令grep -nR "87800000"可以在uboot目录下递归搜索含有87800000的文件
grep "xxxx" -nr ./dir/*.c
grep "xxxx" -nr ./dir
-n:显示行数；-r递归查找目录
可使用“find -name 文件名 ”命令搜索目录下的文件
find -name "xxx"	//本目录下自动递归查找，不用指定-r
find /etc -name "xxx"	//在/etc目录下递归查找
locate根据事先准备好的数据库查，比较快，但须要更新数据库
## Ubuntu下查看正在运行的软件cpu内存：
top命令
q退出，P按照CPU资源大小排序，M按照内存大小排序

## Ubuntu下安装flathub下的软件
Ubuntu20.04已经安装好flatpak，若需要用到flathub下的软件可以查一下怎么安装，具体有些特定的软件可能需要在flathub下才能安装，也可能flathub下有更丰富的linux软件

## Ubuntu下查看正在运行的软件
ps -aux

## Ubuntu下无挂起后台运行软件命令
nohup command >>a.txt &还不太清楚，不过貌似很有用的样子，以后用到了再深究

## linux输入输出重定向

默认都是从键盘输入，屏幕输出
可能见过2>/dev/null之类的语句，是把输出输出到“黑洞”，目的忽视输出

### linux标准输入输出
执行shell命令时会默认打开以下三个文件
标准输入0	从键盘获得输入 /proc/self/fd/0
标准输出1	输出到屏幕（控制台）	/proc/self/fd/1
错误输出2	输出到屏幕（控制台）	/proc/self/fd/2

/dev/null 代表空设备文件，往这个里面写入都会丢失

可以修改文件描述符的指向实现输入输出的重定向

### 输出重定向>
- command >filename	:把标准输出重定向到新文件中(没有则创建，有则删除重新创建)
- command 1>filename :同上（>前不输入默认指1）
- command >>filename :把标准输出追加到文件中
- command 1>>filename :同上
- command 2>filename :把标准错误重定向到新文件
- command 2>>filename :把标准错误追加到新文件中

### 输入重定向<
- command <filename :以filename文件作为标准输入
- command 0<filename :同上
- command <<delimiter :从标准输入中读入，遇到delimiter分割符
(注意：命令后面的参数可能不算输入，cat函数后面不跟文件的话默认输出键盘输入的内容，这个算是输入，见下面例子)

### 输入输出重定向示例
```shell
$ls a.txt b.txt 2>err
a.txt
$cat err
ls: 无法访问b.txt: 没有那个文件或目录
 $ls a.txt b.txt >out 2>err
 $cat out
a.txt
$cat err
ls: 无法访问b.txt: 没有那个文件或目录

$ cat input
aaa
111
$ cat >out <input
$ cat out
aaa
111

注意以下操作：
$ls >/dev/null 2>&1
$ls 2>&1 >dev/null
2>&1代表将错误输出输出到标准输出处
以上两行2>&1位置不同，输出结果也不同，前者标准，错误输出都会输出到/dev/null
后者错误输出输出到屏幕，标准输出输出到/dev/null，即“黑洞”
```
		
## linux管道 |
管道|前后都是命令，后一个命令的输入是前一个命令的输出

## linux分页显示输出内容
例如：ls -al | less
less命令显示命令，类似于more，可往前或者往后显示

## linux xargs命令
xargs常与管道|结合使用，因为：管道：后一个命令的输入是前一个命令的输出，但是，好多命令，如ls，mkdir等，都不会从标准输入读取内容，而是从参数读取内容，xargs可以把标准输入转化为后一个命令的参数，这样就可以更顺畅使用管道