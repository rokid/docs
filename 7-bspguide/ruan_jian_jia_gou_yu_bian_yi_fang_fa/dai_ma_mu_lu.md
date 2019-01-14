## 代码目录

Kamino18 Dev平台采用基于Linux内核的YODAOS操作系统，其代码目录如下图所示：

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

*   3rd: 第三方库，第三方sdk等
*   applications: 本地应用
*   build.sh: 统一编译脚本
*   envsetup.sh: 设置toolchains的环境变量脚本
*   frameworks: 应用框架，native 服务、命令、库，和对第三方的抽象等
*   hardware: HAL (hardware abstract layer)，包括主芯片和外设的硬件抽象
*   kernel: Kamino18 DEV平台Linux内核代码
*   openwrt: YODAOS编译环境代码
*   toolchains:自带工具链目录
*   tools: YODAOS开发调试测试工具目录
*   uboot: Kamino18 DEV平台uboot代码
*   vendor: 第三方平台供应商驱动或sdk代码