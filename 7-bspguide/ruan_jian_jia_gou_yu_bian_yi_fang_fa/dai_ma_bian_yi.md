## 代码编译

### Openwrt编译 {#openwrt}

作为Kamino18 YODAOS的整体编译环境，使用openwrt可以编译出系统正常运行所需的主要image如下：

| **镜像名字** | **镜像运行位置** | **镜像说明** | **镜像生成位置** |
| --- | --- | --- | --- |
| mcu.bin | MCU | The image which run on MCU | $(K18DIR)/openwrt/bin/leo-k18-universal-glibc/mcu.bin |
| u-boot-spl.bin | ARM | Secondary program loader, which is charge of DDR initialization and download u-boot.img into DDR to run | $(K18DIR)/openwrt/bin/leo-k18-universal-glibc/uboot-leo-k18-universal/openwrt-leo-k18-universal-u-boot-spl.bin |
| u-boot.img | ARM | BootLoader download dtb, kernel image and rootfs image into DDR and jump to kernel offset to run | $(K18DIR)/openwrt/bin/leo-k18-universal -glibc/uboot-leo-k18-universal /openwrt- leo-k18-universal - u-boot.img |
| dtb | ARM | Device tree blob for kernel image | $(K18DIR)/openwrt/bin/leo-k18-universal -glibc/openwrt-leo-k18-universal.dtb |
| zImage | ARM | Linux kernel image | $(K18DIR)/openwrt/bin/leo-k18-universal -glibc/openwrt- leo-k18-universal-zImage |
| ubi.img | ARM | Rootfs | $(K18DIR)/openwrt/bin/leo-k18-universal -glibc/openwrt-leo-k18-universal-ubi.img |

有两种整体编译Kamino18 YODAOS镜像的方法如下：

1\. 系统根目录下运行

*   ./build.sh –p leo_k18_universal_node -n openwrt-leo-k18-universal -f leo-k18-universal -j12 -r

2\. 为了获取更多的编译信息，可以进入openwrt进行编译，命令如下：

*   cd openwrt
*   cp configs/leo_k18_universal_node_defconfig .config
*   make defconfig
*   make -j1 V=99

编译结果存放在$(K18DIR)/openwrt/bin目录下。

修改openwrt package配置：

*   make menuconfig

修改kernel配置：

*   make kernel_menuconfig

openwrt整个编译后，如需编译单个package用如下命令（详细说明参考$(K18DIR)/openwrt/README.md）：

*   make package/some_package/clean
*   make package/some_package/compile V=99

### Kernel编译 {#kernel}

通过自带工具链，开发者可以独立编译kernel代码，命令如下：

*   cd openwrt
*   make kernel_menuconfig
*   make target/linux/clean
*   make target/linux/compile
*   make target/linux/install

kernel编译生成的dtb和zImage文件在$(K18DIR)/kernel/arch/arm/boot/目录中。

### Uboot编译 {#uboot}

通过自带工具链，开发者可以独立编译uboot代码，命令如下：

*   cd openwrt
*   make package/uboot-leo/clean
*   make package/uboot-leo/ compile 或 make package/uboot-leo/install

uboot编译生成的u-boot-spl.bin在$(K18DIR)/uboot/spl/目录中, u-boot.img在$(K18DIR)/uboot/目录中。

### VSP编译 {#vsp}

VSP目录中包含MCU和VSP驱动的源文件（DSP为非开源算法代码，编译方法本文略去），其编译方法如下：

*   cd $(K18DIR)/hardware/nationalchip/gx8010/vsp
*   make k18_universal_defconfig
*   make

编译生成的镜像如下表所示：

| **镜像名字** | **镜像说明** | **镜像生成位置** |
| --- | --- | --- |
| mcu_nand.bin | The mcu image which is flashed into spi nand flash | $(K18DIR)/hardware/nationalchip/gx8010/vsp/output/mcu_nand.bin |
| mcu_nor.bin | The mcu image which is flashed into spi nor flash | $(K18DIR)/hardware/nationalchip/gx8010/vsp/output/mcu_nor.bin |
| vsp.ko | The vsp driver module which is installed into kernel | $(K18DIR)/ hardware/nationalchip/gx8010/vsp/output/vsp.ko |