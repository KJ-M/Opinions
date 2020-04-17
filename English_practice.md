## *NO.1 Thursday, April 2, 2020*

U-Boot readme.txt

Summary[^1]:
This directory contains the source code for U-Boot, a boot loader for Embedded[^2] boards based on PowerPC, ARM, MIPS and several other processors, which can be installed[^3] in a boot ROM and used to initialize[^4] and test the hardware or to download and run application code.
The development of U-Boot is closely related to Linux: some parts of the source code originate in[^5] the Linux source tree, we have some header files in common, and special provision[^6] has been made to support booting of Linux images.
Some attention has been paid to make this software easily configurable and extendable. For instance, all monitor[^7] commands are Implemented[^8] with the same call interface[^9], so that it's very easy to add new commands. Also, instead of permanently[^10] adding rarely[^11] used code (for instance hardware test utilities[^12]) to the monitor, you can load and run it dynamically[^13].	

[^1]:Summary 概括，摘要
[^2]:Embed使嵌入 
[^3]:initialize初始化
[^4]:install安装
[^5]:originate in（源自于）
[^6]:provision（准备，供应）
[^7]:monitor（监控）
[^8]:Implement（实行）
[^9]:interface（界面，接口）
[^10]:permanently（永久地）
[^11]:rarely（少见的）
[^12]:utility（效用）
[^13]:dynamically（动态地）

## *NO.2 Friday,April 3,2020*

U-Boot Makefile 414-420
- To make sure we do not include .config for any of the config targets catch them early, and hand them over to[^14] scripts/kconfig/Makefile
- It is allowed to specify[^15] more targets when calling make, including mixing config targets and build targets.
- For example 'make oldconfig all'.
- Detect when mixed targets is specified, and make a second invocation[^16] of make so .config is not included in this case either (for config).
- Documentation[^17]
- To see a list of typical targets execute[^18] "make help"
- More info can be located in ./README
- Comments[^19] in this file are targeted only to the developer[^20], do not expect to learn how to build the kernel reading this file.
- Do not use make's built-in rules[^21] and variables[^22]
(this increases performance[^23] and avoids hard-to-debug behaviour);
- Look for make include files relative to[^24] root of kernel src[^25]

[^14]:hand them over to（移交给）
[^15]:specify（指明）
[^16]:invocation（调用）
[^17]:documentation（文献资料）
[^18]:execute（执行）
[^19]:comment（评论注解）
[^20]:developer（开发人员）
[^21]:built-in rule（内置规则）
[^22]:variable（变量）
[^23]:performance（表演，性能）
[^24]:relative to（关于，和…比较起来，相对于）
[^25]:look for make include files relative to root of kernel src（寻找跟内核src根目录有关的make包含文件）

## *NO.3 Saturday,April 4,2020*

Uboot/arch/arm/cpu/armv7/lowlevel_init.S

A lowlevel_init function that sets up[^26] the stack to call a C function to perform further init[^27].

8-byte alignment for ABI compliance[^28]

This should do only the absolute bare minimum[^29] to get started.

Try to start a console

Console：a panel[^30] or unit accommodating[^32] a set of[^33] controls for electronic or mechanical equipment[^34].

[^26]:Set up（设置）
[^27]:perform further init（进行更深层次的初始化）
[^28]:8-byte alignment for ABI compliance（8字节对齐以符合ABI承诺（标准））
[^29]:absolute bare minimum（绝对最低限度）,
[^30]:Panel（面板，嵌板）
[^31]:unit（部件）
[^32]:accommodate（为…提供住宿）
[^33]:a set of（一套）
[^34]:Console：a panel or unit accommodating a set of controls for electronic or mechanical equipment.（装有一组用于电子或机械设备的控件的面板或单元。）

## *NO.4 Saturday，April 11,2020*

an empty message aborts[^35] the commit[^36]

Changes not staged[^37] for commit[^38]

Modified[^39]：xxx

Discard[^40] changes

Merge[^41] fatal[^42]

Track[^43]

[^35]:abort（使终止）
[^36]:commit（提交）
[^37]:stage（筹划，集结）
[^38]:Changes not staged for commit（未准备提交的更改）
[^39]:modify（修改）
[^40]:discard（丢弃）
[^41]:merge（合并）
[^42]:fatal（致命的）
[^43]:track (追踪)
