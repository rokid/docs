## Software Folder Structure {#software-folder-structure}

Kamino18 Dev3.0 works with YodaOS based on Linux kernel，whose code folder structure as below：

├── 3rd

├── applications

├── build.sh -&gt; /home/zhubin/kamino18/products/rokid/common/build.sh

├── check_by_jenkins

├── envsetup.sh -&gt; /home/zhubin/kamino18/products/rokid/common/envsetup.sh

├── frameworks

├── hardware

├── kernel

├── openwrt

├── products

├── toolchains

├── tools

├── uboot

└── vendor

*   3rd: The 3<sup>rd</sup> sdk source code
*   applications: Local application
*   build.sh: Compiling script
*   envsetup.sh: Toolchains environment setup script
*   frameworks: Application framework, native service/command/lib and 3<sup>rd</sup> abstract layer
*   hardware: HAL (hardware abstract layer)，include main soc and peripheral HAL;
*   kernel: Kamino18 DEV3.0 Linux kernel code
*   openwrt: YodaOS compiling environment
*   toolchains: Compiling toolchains
*   tools: YodaOS developing and debugging tool
*   uboot: Kamino18 DEV3.0 uboot code
*   vendor: SDK lib provided by the vendor