## Code Compile {#code-compile}

### Openwrt Compile {#openwrt-compile}

In the compiling environment for Kamino18 YodaOS， using openwrt, we can compile out the images as below table:

| **Image name** | **Image running place** | **Image illustration** | **Image generating place** |
| --- | --- | --- | --- |
| mcu.bin | MCU | The image which run on MCU | $(K18DIR)/openwrt/bin/leo-k18-universal-glibc/mcu.bin |
| u-boot-spl.bin | ARM | Secondary program loader, which is charge of DDR initialization and download u-boot.img into DDR to run | $(K18DIR)/openwrt/bin/leo-k18-universal-glibc/uboot-leo-k18-universal/openwrt-leo-k18-universal-u-boot-spl.bin |
| u-boot.img | ARM | BootLoader download dtb, kernel image and rootfs image into DDR and jump to kernel offset to run | $(K18DIR)/openwrt/bin/leo-k18-universal -glibc/uboot-leo-k18-universal /openwrt- leo-k18-universal - u-boot.img |
| dtb | ARM | Device tree blob for kernel image | $(K18DIR)/openwrt/bin/leo-k18-universal -glibc/openwrt-leo-k18-universal.dtb |
| zImage | ARM | Linux kernel image | $(K18DIR)/openwrt/bin/leo-k18-universal -glibc/openwrt- leo-k18-universal-zImage |
| ubi.img | ARM | Rootfs | $(K18DIR)/openwrt/bin/leo-k18-universal -glibc/openwrt-leo-k18-universal-ubi.img |

There are two ways to compile Kamino18 YodaOS images as below：

1\. In K18 source code root directory, run the below command

*   ./build.sh –p leo_k18_universal_node -n openwrt-leo-k18-universal -f leo-k18-universal -j12 -r

2\. In order to get more compiling message，we can enter openwrt directory to use the below compiling commands as below:

*   cd openwrt
*   cp configs/leo_k18_universal_node_defconfig .config
*   make defconfig
*   make -j1 V=99

The compiling images are generated in $(K18DIR)/openwrt/bin directory.

Setup openwrt configuration：

*   make menuconfig

Setup kernel configuration：

*   make kernel_menuconfig

After openwrt full image compiling，use the below compiling command to compile a specific package(Referring to the document $(K18DIR)/openwrt/README.md for the detail）：

*   make package/some_package/clean
*   make package/some_package/compile V=99

### Kernel Compile {#kernel-compile}

Developer also can compile kernel source code independently through the below commands：

*   cd openwrt
*   make kernel_menuconfig
*   make target/linux/clean
*   make target/linux/compile
*   make target/linux/install

The kernel compiling result dtb and zImage files are located in $(K18DIR)/kernel/arch/arm/boot/ directory.

### Uboot Compile {#uboot-compile}

Developer also can compile uboot source code independently through the below commands：

*   cd openwrt
*   make package/uboot-leo/clean
*   make package/uboot-leo/ compile 或 make package/uboot-leo/install

The uboot compiling result u-boot-spl.bin is located in $(K18DIR)/uboot/spl/ directory and u-boot.img is located in $(K18DIR)/uboot/ directory.

### VSP Compile {#vsp-compile}

VSP directory contains MCU and VSP driver source code, whose compiling method as below：

*   cd $(K18DIR)/hardware/nationalchip/gx8010/vsp
*   make k18_universal_defconfig
*   make

VSP compiling results are as the below table：

| **Image name** | **Image illustration** | **Image generating place** |
| --- | --- | --- |
| mcu_nand.bin | The mcu image which is flashed into spi nand flash | $(K18DIR)/hardware/nationalchip/gx8010/vsp/output/mcu_nand.bin |
| mcu_nor.bin | The mcu image which is flashed into spi nor flash | $(K18DIR)/hardware/nationalchip/gx8010/vsp/output/mcu_nor.bin |
| vsp.ko | The vsp driver module which is installed into kernel | $(K18DIR)/ hardware/nationalchip/gx8010/vsp/output/vsp.ko |