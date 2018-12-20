YodaOS Universal 如何配置系统和应用
=============================== 
## 目录

*	[YodaOS 完整体验](#yodaos) 
*	[如何定制化系统和应用](#setup)

### <span id="yodaos">一.YodaOS完整体验</span>
#### 下载代码

1. google repo:

```sh
  repo init -u ssh://yourname@openai-corp.rokid.com:29418/kamino_universal_cust/open-platform/manifest -m yodaos-7.27.0-alpha-20181030.xml
```
2. rokid repo:

```sh
  repo init -u ssh://yourname@openai-corp.rokid.com:29418/kamino_universal_cust/open-platform/manifest -m yodaos-7.27.0-alpha-20181030.xml -repo-url=ssh://yourname@openai-corp.rokid.com:29418/tools/repo  --no-repo-verify
```

#### 代码结构

```sh
*   ├── 3rd ：第三方软件包
    ├── applications :应用
    ├── build.sh -> /home/hailiang.xu/naboo/products/rokid/common/build.sh  ：ci 编译脚本
    ├── envsetup.sh -> /home/hailiang.xu/naboo/products/rokid/common/envsetup.sh ：本地编译脚本
    ├── frameworks：应用框架，native 服务、命令、库，和对第三方的抽象等
    ├── hardware ： HAL (hardware abstract layer)，包括主芯片和外设的硬件抽象
    ├── kernel：内核
    ├── Makefile -> /home/hailiang.xu/naboo/products/rokid/common/Makefile:外部makefile
    ├── openwrt:[openwrt 目录](#openwrt_folder)
    ├── products：产品相关文件目录
    ├── toolchains：编译工具链
    ├── tools：系统工具
    ├── uboot：uboot
    └── vendor：第三方厂家文件
  ```

#### 安装编译依赖工具

      **ubuntu 16.04**
	
```sh
  sudo apt-get install build-essential subversion libncurses5-dev zlib1g-dev gawk gcc-multilib flex git-core gettext libssl-dev unzip texinfo device-tree-compiler dosfstools libusb
```
      **CentOS7**
	
```sh
yum install -y unzip bzip2 dosfstools wget gcc gcc-c++ git ncurses-devel zlib-static openssl-devel svn patch perl-Module-Install.noarch perl-Thread-Queue
```

CentOS7需手动安装device-tree-compiler：

```sh
wget http://www.rpmfind.net/linux/epel/6/x86_64/Packages/d/dtc-1.4.0-1.el6.x86_64.rpm
rpm -i dtc-1.4.0-1.el6.x86_64.rpm
```

#### 编译 

方法1.手动拷贝:

```sh
    cd openwrt
    cp configs/leo_k18_universal_node_defconfig .config
    make defconfig
    make
    如果想查看详细编译信息，请加V=s参数。
    如果想加快编译速度，请加-j参数。
```

方法2.通过source envsetup.sh 配置编译：

```sh
    You're building on openwrt
    Lunch menu...pick a combo:

    1. leo_gx8010_ota_1v
    2. leo_gx8010_rkd_1v
    3. leo_gx8010_rkd_2v
    4. leo_gx8010_rkd_3v
    5. leo_gx8010_rkd_4v
    6. leo_gx8010_rkd_naboo
    7. leo_gx8010_rkd_naboo_yodaos
    8. leo_gx8010_ssd_1v
    9. leo_k18_cus360
    10. leo_k18_dev31
    11. leo_k18_dev32
    12. leo_k18_dev33
    13. leo_k18_dev34
    14. leo_k18_universal_avs
    15. leo_k18_universal
    16. leo_k18_universal_node
    17. leo_k18_cus360_native
    18. leo_gx8010_rkd_naboo_chinateleom

    Which would you like? [6] 16

    You are building on Linux
    echo Lunch menu... pick a root filesystem:
    1. ubifs(root filesystem is read wirte)
    2. squashfs(root filesystem is read only)
    Which would you like? [1]1

    You are building on Linux
    Lunch menu... pick a image style:
    1. debug(root filesystem bin is not striped)
    2. release(root filesystem bin is striped)
    Which would you like? [1]1
    /home/hailiang.xu/k18/openwrt
    ~/k18/openwrt ~/k18
    ===========================================

    #TARGET_BOARD=k18
    #BUILD_TYPE=32
    #CONFIG=leo_k18_universal_node_defconfig

    ===========================================
    #
    # configuration written to .config
    #
    1
    set configure Debug info ...
    Merging /home/hailiang.xu/k18/products/rokid/common/rokidos_debug_config.frag
    Merging /home/hailiang.xu/k18/products/rokid/common/rokidos_debug_packages.frag
    Merging /home/hailiang.xu/k18/products/rokid/common/rokidos_debug_noset_package.frag
    merge DEBUG info success
    ~/k18
    
    make -j32
    方法2将方法1做成自动脚本，并添加选择文件系统和release/debug选项。
```

方法3.自动编译脚本用于发布镜像：

```sh
./build.sh -p leo_k18_universal_node -n openwrt-leo-k18-universal -f leo-k18-universal  -j32 -r
    方法3是调用方法2，并编译生成Recovery分区+OTA固件，通常用做生产镜像发布。
```

#### 固件地址
*具体参考Rokid Kamino18 Universal Install Guide V2.5.pdf 6章节 这里做简要描述
*生成固件在 openwrt/bin/leo-k18-universal-glibc/

```sh
    -rwxr-xr-x  1 xhl  staff    57K 10 16 23:40 bootmusic.wav
    -rwxr-xr-x@ 1 xhl  staff   332K 10 17 00:35 bootx
    drwxr-xr-x  8 xhl  staff   256B 10 16 23:40 bootx_win
    -rwxr-xr-x  1 xhl  staff   1.9K 10 16 23:40 download.bat
    -rwxr-xr-x  1 xhl  staff   3.1K 10 17 15:55 download.sh
    -rw-r--r--  1 xhl  staff   256K 10 17 00:26 env.bin
    -rwxr--r--  1 xhl  staff   386B 10 16 23:40 gen_swupdate_img.sh
    -rw-r--r--  1 xhl  staff   162K 10 17 00:09 mcu.bin
    -rw-r--r--  1 xhl  staff   1.4K 10 17 00:26 md5sums
    -rw-r--r--  1 xhl  staff   2.0M 10 17 00:26 openwrt-leo-k18-universal-app.img
    -rw-r--r--  1 xhl  staff   4.0M 10 17 00:26 openwrt-leo-k18-universal-fit-uImage.itb
    -rw-r--r--  1 xhl  staff    22M 10 17 00:26 openwrt-leo-k18-universal-rootfs.tar.gz
    -rw-r--r--  1 xhl  staff    27M 10 17 00:26 openwrt-leo-k18-universal-squashfs.img
    -rw-r--r--  1 xhl  staff    37K 10 17 00:10 openwrt-leo-k18-universal-u-boot-spl.bin
    -rw-r--r--  1 xhl  staff   346K 10 17 00:10 openwrt-leo-k18-universal-u-boot.img
    -rw-r--r--  1 xhl  staff   4.0M 10 17 00:26 openwrt-leo-k18-universal-uImage
    -rw-r--r--  1 xhl  staff    27M 10 17 00:26 openwrt-leo-k18-universal-ubi.img
    -rw-r--r--  1 xhl  staff    26M 10 17 00:26 openwrt-leo-k18-universal-ubifs.img
    -rwxr-xr-x  1 xhl  staff   4.0M 10 17 00:26 openwrt-leo-k18-universal-zImage
    -rw-r--r--  1 xhl  staff    24K 10 17 00:26 openwrt-leo-k18-universal.dtb
    -rw-r--r--  1 xhl  staff    31M 10 17 00:26 openwrt-leo-k18-universal.swu
    -rw-r--r--  1 xhl  staff   3.1M 10 16 23:40 openwrt-leo-ota-fit-uImage-initramfs.itb
    -rw-r--r--  1 xhl  staff   2.4K 10 17 00:26 sha256sums
    -rw-r--r--  1 xhl  staff   983B 10 16 23:40 sw-description
```

*编译方法3，会拷贝固件到openwrt/bin/leo-k18-universal-glibc/full_images，并将full_images压缩后放到check_by_jenkins用于发布。

    
#### 烧写固件
**linux 烧写**

```sh
    cd openwrt/bin/leo-k18-universal-glibc/
    sudo cp bootx /usr/local/bin/ 
    ./download.sh all
    根据提示按住调试板上的 BOOT_KEY，然后连接 USB 线到 PC 上.
```
**indows烧写**

使用 windows 烧写工具前，对于一台新电脑需要安装 usb 驱动(驱动安装文件和说明在`leo-k18-universal-glibc/bootx_win/driver_install`
目录下), Windows 电脑上具体烧写流程如下:

* 进入$(K18DIR)/openwrt/bin/ leo-k18-universal-glibc /full_images 目录
* 双击 download.bat
* 根据提示按住调试板上的 BOOT_KEY，然后连接 USB 线到 PC 上

### 定制系统和应用

YodaOS 是基于 openwrt 编译系统，所以需要了解优化后的目录结构。	

#### OpenWrt 目录结构

##### 原始目录

* `scripts` 存放了一些脚本，使用了 bash、python、perl 等多种脚本语言。编译过程中，用于第三方软件包管理的 feeds 文件也是在这个目录当中。在编译过程中，使用到的脚本也统一放在这个目录中。
* `tools` 编译时，主机需要使用一些工具软件，tools 里包含了获取和编译这些工具的命令。软件包里面有 Makefile 文件,有的还包含了 Patch。每个 Makefile 当中都有一句 `$(eval $(call HostBuild))`，这表明编译这个工具是为了在主机上使用的。
* `config` 存放着整个系统的配置文件
* `configs` 存放各个板级的默认配置
* `docs` 包含了整个宿主机的文件源码的介绍，里面还有 Makefile 为目标系统生成文档。使用`make -C docs/`可以为目标系统生成文档。
* `toolchain` 交叉编译链，这个文件中存放的就是编译交叉编译链的软件包.包括 binutils、gcc、libc 等等。
* `target` OpenWrt 的源码可以编译出各个平台适用的二进制文件，各平台在这个目录里定义了固件和内核的编译过程。
* `package` 存放了系统中适用的软件包,包含针对各个软件包的 Makefile。OpenWrt 定义了一套 Makefile 模板。各软件参照这个模板定义了自己的信息，如软件包的版本、下载地址、编译方式、安装地址等。在二次开发过程中，这个文件夹我们会经常打交道。事实上，通过 `./scripts/feed update -a` 和 `./scripts/feed install -a` 的软件包也会存放在这个目录之中。
  * `rokid` 存放了YodaOS所需要的package。
  * `include` OpenWrt 的 Makefile 都存放在这里。文件名为 `*.mk`。这里的文件上是在 Makefile 里被包含的，类似于库文件，这些文件定义了编译过程。
  * `feeds` OpenWrt 的附加软件包管理器的扩展包索引目录。简单来说就是下载管理软件包的。默认 feeds 下载有 packages、management、luci、routing、telephony。如要下载其他的软件包，需打开源码根目录下面的 feeds.conf.default 文件，去掉相应软件包前面的#号，然后更新源：`./scripts/feeds update -a`，安装下载好的包：`./scripts/feeds install -a`
* `dl` 在编译过程中使用的很多软件，刚开始下载源码并没有包含，而是在编译过程中从其他服务器下载的，这里是统一的保存目录。
* `Makefile` 在顶层目录执行make命令的入口文件。
* `rules.mk` 定义了Makefile中使用的一些通用变量和函数。
* `Config.in` 在 `include/toplevel.mk` 中我们可以看到，这是和 `make menuconfig` 相关联的文件。
* `feeds.conf.default` 是下载第三方一些软件包时所使用的地址。
* LICENSE & README 即软件许可证和软件基本说明，README 描述了编译软件的基本过程和依赖文件。
   
###### 生成目录

* `build_dir` 在前面的原始目录中，我们提到了 host 工具，toolchain 工具还有目标文件。OpenWrt 将在这个目录中展开各个软件包，进行编译，所以这个文件夹中包含3个子文件夹:
  * `host` 在该文件夹中编译主机使用的工具软件。
  * `toolchain-XXX` 在该文件夹中编译交叉工具链。
  * `target-XXX` 在此编译目标平台的目标文件，包括各个软件包和内核文件。
  * `bin` 保存编译完成后的二进制文件，包括完整的 bin 文件,所有的 ipk 文件。
  * `staging_dir` 用于保存在 build_dir 目录中编译完成的软件，所以这里也和 build_dir 有同样的子目录结构。比如，在 target-XXX 文件夹中保存了目标平台编译好的头文件，库文件。在我们开发自己的 ipk 文件时，编译过程中，预处理头文件，链接动态库，静态库都是到这个子文件夹中。
  * `tmp` 临时文件夹，在编译过程中，有大量中间临时文件需要保存，都是在这里。
  * `logs` 日志文件夹，遇到错误时从这里获取信息，分析编译失败的原因。
  
#### 如何生成定制化配置
*使用 `make menuconfig` 完成配置修改
*使用`diffconfig.sh`脚本生成配置

```sh
./scripts/diffconfig.sh > configs/<板级>_defconfig
```

#### 如何编译单个包
*清理、编译、安装单个包

```sh
make package/<name>/{clean,compile,install}
```

*编译清理, 编译, 安装工具链

```sh
make toolchain/{clean,compile,install}
```

#### 如何单独编译uboot
编译uboot

```sh
make package/uboot-leo/compile
```

安装到 `openwrt/bin/` 目录

```sh
make package/uboot-leo/install
```

#### 如何单独编译kernel
编译module

```sh
make target/linux/compile
```

编译zImage、dts。install到openwrt/bin/目录下

```sh
make target/linux/install
```

#### 如何修改kernel配置

```sh
make kernel_menuconfig
```

#### 如何选择Debug/Release

```sh
 $ source envsetup.sh

 You are building on Linux
 Lunch menu... pick a image style:
 
 1. debug(root filesystem bin is not striped)（目前受限于k18 flash的大小，debug模式下也是不带符号表）
 2. release(root filesystem bin is striped)
```

./build.sh 添加 -d 选项:

```sh
./build.sh -p leo_k18_universal_node -n openwrt-leo-k18-universal -f leo-k18-universal  -j32 -r -d
```
Release模式下

1. 自己的调试程序不需要打包到镜像。
2. RKLog里设置默认log级别调到info。

Debug 模式下

1. config下CONFIG_DEBUG 宏会被打开。
2. 各软件包，根据宏定义拷贝相应的测试程序和工具到镜像中。
3. RKLog里设置默认log级别调到debug。
4. 后续DEBUG模式会加入 gdb strace valgrind....

#### 如何添加自己的package
> 请参考https://openwrt.org/docs/guide-developer/helloworld/chapter3

#### 如何控制系统服务是否开机启动

以 alab-libs 仓库为例子。开发者需要我们的前端激活库，但并不希望开机启动。查看 `package/rokid/alab-libs/Config.in` 默认
是开机启动，如不需要开机启动。

* `make menuconfig`
* 在 `rokid/alab-libs/Configuration` 去掉勾选项

```sh
    menu "Configuration"

    config TURENPROC_AUTO_RUN
        bool "auto run"
        default y
        help
            turenproc service auto run

    endmenu
```

查看alab-libs/Makefile 根据menuconfig中是否有选择TURENPROC_AUTO_RUN来判断是否开机启动。\

```sh
if [ "$(CONFIG_TURENPROC_AUTO_RUN)" != "y" ]; then \
$(SED) "s/^START/#START/g" $(1)/etc/init.d/turenproc; \
fi
```


