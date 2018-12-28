## 文件系统配置

Rootfs文件系统设置成ubifs readonly，相应mount命令在uboot中设置，如下：

$(K18DIR)/uboot/include/configs/leo_common.h

/* Extra Environment */

#define CONFIG_EXTRA_ENV_SETTINGS \

…

&quot;mtdargs=ubi.mtd=&quot;__stringify(CONFIG_ROOTFS_POS) &quot;,2048 root=ubi0:rootfs rootwait &quot; \

&quot;rootfstype=ubifs ro loglevel=6 mem=&quot;__stringify(CONFIG_MEM_SIZE)&quot;M\0&quot; \

…

为了调试系统方便，有时我们需要把rootfs分区变为可读写分区，有两种方法。

*   方法1，在uboot命令行中执行如下命令：

LEO#editenv mtdargs

LEO#ubi.mtd=9,2048 root=ubi0:rootfs rootwait rootfstype=ubifs rw loglevel=6

LEO#save

*   方法2，在adb shell命令行中执行如下命令：

mount -o remount rw /