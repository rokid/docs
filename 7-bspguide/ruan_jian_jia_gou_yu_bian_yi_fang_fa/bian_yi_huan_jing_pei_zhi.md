## 编译环境配置

因为Kamino18平台采用MCU/ARM的异步架构，开发者需要安装arm和MCU交叉编译工具链。

### Openwrt编译环境搭建 {#openwrt}

整个Kamino18平台的YodaOS是基于openwrt进行编译的，通过openwrt我们可以得到文件系统，交叉编译工具链等。请在进行openwrt编译前，确保如下工具包已经在ubuntu环境上安装完成。

*   sudo apt-get install build-essential subversion libncurses5-dev zlib1g-dev gawk gcc-multilib flex git-core gettext libssl-dev unzip texinfo
*   sudo apt-get install device-tree-compiler
*   sudo apt-get install gcc-4.7-arm-linux-gnueabihf
*   sudo apt-get install libusb-1.0-0-dev

### 自带编译工具链环境搭建 {#-0}

Kamino18平台代码中包含自带工具链，如下图：

├── toolchains

│   ├── arm

│   ├── csky

│   └── scripts

自带工具链目录包含arm（64位ubuntu-16.04编译服务器上使用）和csky(用于编译MCU)两个交叉编译工具链。为了使用这两个工具链，需要设置环境变量, 在代码包根目录运行命令如下：

*   source env.sh
*   export ARCH=arm
*   export CROSS_COMPILE=arm-openwrt-linux-gnueabi-

### MCU编译环境搭建 {#mcu}

Kamino18的VSP子系统由MCU+DSP组成，其中MCU是控制部分，DSP处理算法部分。MCU编译工具链（toolchains/csky/）的依赖环境如下：

*   sudo dpkg --add-architecture i386
*   sudo apt-get update
*   sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386 libx11-6:i386 gtk2-engines:i386 lib32ncurses5 lib32z1 libxtst6:i386 libgtk2.0-0:i386 lib32ncurses5 libcanberra-gtk3-0:i386