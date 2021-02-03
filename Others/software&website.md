# Windows&Linux下常用软件
## Obsidian
### 安装
软件下载地址：https://github.com/obsidianmd
Windows下直接安装
Linux下下载AppImage文件，chmod+x，对该文件双击即可运行
### 配置
用该软件打开目录后自动生成.obsidian文件夹，内有配置文件，保存了此目录下的个人设置，复制到另外的地方可直接使用
个人配置如下：
- 打开大纲视图，可预览目录
- 打开链接预览，鼠标放上即可简单浏览
- alt+1,2,3对应打开左右边栏，切换编辑浏览模式
- alt+,.前进后退
- 打开vim编辑

## picocom
使用`ls /dev/ttyUSB*`可查看当前正在使用的串口
使用命令
`sudo picocom -b 115200 /dev/ttyUSB0`打开串口

## 谷歌浏览器
安装扩展插件.crx文件，需将后缀.crx改成.zip然后解压，在浏览器扩展中开启开发者模式，然后打开该文件夹，即可安装插件
安装谷歌访问助手后可访问应用商店，即可下载安装其他插件，主题等
谷歌访问助手破解版百度网盘里有一份

## Markdown
[[Markdown_test]]

## Vim
[[use_of_vim]]

## Git
[[git]]

## Source Insight


- 可设置外部命令，如按下F12打开git bash等
在Tools下有Custom Commands，点击add添加，选keys可设置快捷键，输入内容如
"C:\Program Files (x86)\Vim\vim81\gvim.exe" +%l %f 使用vim打开当前文件（%l %f对应当前行，当前文件
"D:\git\Git\git-bash.exe"	打开git bash
"D:\git\Git\cmd\git-gui.exe"	打开git gui
可使用：ShellExecute Commands，调用ShellExecute函数，用于打开程序，目录，文件等功能
详情：https://www.sourceinsight.com/doc/v4/userguide/index.html#t=Manual%2FCommand_Reference%2FCustom_Commands1.htm&rhsearch=custom%20commands&rhsyns=%20&rhhlterm=custom%20commands
个人目前使用：
ShellExecute open %j	打开工程所在目录（%j，%l也可查阅以上网站）
ShellExecute open C:\DCRABBIT_9.62	打开目录C:\DCRABBIT_9.62

- 左侧函数大纲预览可通过alt+F8关闭打开
- 可预先设置好几种不同的窗口布局保存在layoutA，B,C，D中，随时切换布局方便查看

## Vscode 
- 使用vscode插件Remote-SSH（open a forder on a remote........）连接远程服务器即可相当于在该服务器上进行开发，文件可以右键点击下载即可下载到本地
- 主题Slack Theme
- 

## Windows下看图
JPEGView

## gcc,gdb调试
### 产生调试信息:
gcc -g

### 断点：
b+行数/函数名，
b xxx if i==n:当i=n时在xxx处断点
info b，
del/del n
watch b：调试过程中，如某函数有一局部变量b，当执行过程中b被改变就断掉
### 执行：
run/r开始，s/step单步，n/next一次一个函数，c/continue继续到结束或下个断点
### 查看：
p/print+变量/{变量1,2...}：断点处查看一次该变量，
display+变量/{变量1,2...}每次断点处都查看，undisplay解除查看，
bt full：查看栈帧+所有局部变量
info display/b/watch：查看输入的调试信息
### 调试过程改变变量值：
set variable a=n:把a现有的值换成n