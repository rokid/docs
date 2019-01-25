## File System Setup {#file-system-setup}

Rootfs is setup as ubifs read-only. Corresponding mount command is setup in uboot as below：

$(K18DIR)/uboot/include/configs/leo_common.h

/* Extra Environment */

#define CONFIG_EXTRA_ENV_SETTINGS \

…

&quot;mtdargs=ubi.mtd=&quot;__stringify(CONFIG_ROOTFS_POS) &quot;,2048 root=ubi0:rootfs rootwait &quot; \

&quot;rootfstype=ubifs ro loglevel=6 mem=&quot;__stringify(CONFIG_MEM_SIZE)&quot;M\0&quot; \

…

In order to debug system easily，sometimes we need change rootfs as R/W partition. There are two ways as below:

*   Method 1，in uboot command line, run the below commands：

LEO#editenv mtdargs

LEO#ubi.mtd=9,2048 root=ubi0:rootfs rootwait rootfstype=ubifs rw loglevel=6

LEO#save

*   Method 2，in adb shell, run the below command：

mount -o remount rw /