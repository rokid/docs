## Compiling Environment {#compiling-environment}

Because Kamino18 is a heterogeneous architecture SOC, we need install both arm and mcu cross-compile toolchain to compile the whole source code.

### Openwrt Compiling Environment Setup {#openwrt-compiling-environment-setup}

The YodaOS working on Kamino18 platform is compiled based on openwrt SDK. Through openwrt, we can make rootfs image and get cross-compile toolchain. Before using openwrt sdk, please make sure the below tool packages have been installed in your Ubuntu PC.

*   sudo apt-get install build-essential subversion libncurses5-dev zlib1g-dev gawk gcc-multilib flex git-core gettext libssl-dev unzip texinfo
*   sudo apt-get install device-tree-compiler
*   sudo apt-get install gcc-4.7-arm-linux-gnueabihf
*   sudo apt-get install libusb-1.0-0-dev

### Compiling Toolchain Environment Setup {#compiling-toolchain-environment-setup}

The YodaOS source package also contain toolchains as below：

├── toolchains

│   ├── arm

│   ├── csky

│   └── scripts

The toolchains folder contain arm and csky(MCU) two cross-compile toolchains. In order to use these two toolchains, we need setup environment parameter as the below commands：

*   source env.sh
*   export ARCH=arm
*   export CROSS_COMPILE=arm-openwrt-linux-gnueabi-

Note: These two toolchains need use on 64bit ubuntu-16.04 PC environment.

### MCU Compiling Environment Setup {#mcu-compiling-environment-setup}

The VSP subsystem in Kamino18 consists of MCU and DSP two parts. MCU(CK) is the control part. DSP is the algorithm process part. The dependency environment of MCU cross-compile toolchain（toolchains/csky/）is as below：

*   sudo dpkg --add-architecture i386
*   sudo apt-get update
*   sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386 libx11-6:i386 gtk2-engines:i386 lib32ncurses5 lib32z1 libxtst6:i386 libgtk2.0-0:i386 lib32ncurses5 libcanberra-gtk3-0:i386