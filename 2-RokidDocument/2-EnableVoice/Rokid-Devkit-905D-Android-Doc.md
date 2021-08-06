## ALL in ONE 开发板 AMLOGIC 905D android代码编译烧写教程

### 设置 android 编译环境

### 64-bit\_Ubuntu 系统

1. 安装 Ubuntu \(14.04或者 16.04\) 64位系统。内存至少8G， CPU核数至少4个，单个可用分区至少60G。  
        如有需要，可以下载VMWARE的虚拟机镜像，我们提供的ubuntu镜像密码是Rokid123：

   ```
        14.04镜像：ftp://ftp-customer:9921/images/vmware/ubuntu_14.04.5_64.zip

        16.04镜像：ftp://ftp-customer:9921/images/vmware/ubuntu_16.04.3_64.zip
   ```

2. 安装编译必须的软件包：  
   ```
        sudo apt-get install git-core gnupg gperf zip cscope ctags libz-dev libexpat-dev \
        python language-pack-en texinfo zlib1g-dev  x11proto-core-dev  libx11-dev\
        build-essential g++ git bison flex unzip gcc-multilib g++-multilib libgl1-mesa-dev \
        libssl-dev libxml-simple-perl libxml-sax-perl libxml2-dev libxml2-utils xsltproc \
        wget bc ccache curl libc6-dev-i386 lib32ncurses5-dev lib32z-dev

      ```

3. 安装java环境并配置java环境变量；安装命令如下：
   ``` shell
   sudo add-apt-repository ppa:openjdk-r/ppa
   sudo apt-get update
   sudo apt-get install openjdk-7-jdk 
   ```
   
   保证java -version 有以下结果：
   ```
   java -version
   java version "1.7.0_121"

   OpenJDK Runtime Environment (IcedTea 2.6.8) (7u121-2.6.8-1ubuntu0.14.04.3)
   OpenJDK 64-Bit Server VM (build 24.121-b00, mixed mode)
   ```

### 安装repo 工具

1. 确保主目录下有一个 bin/ 目录，并且该目录包含在路径中：

```
$ mkdir ~/bin
$ PATH=~/bin:$PATH
```

2.根据您的办公网络情况，获取 repo 工具。

1. 可以翻墙

   如果您的办公环境可以翻墙访问 Google 网站，您可以使用Google 官方发行的 repo 工具。

   ```
   $ curl -Ls -o ~/bin/repo https://storage.googleapis.com/git-repo-downloads/repo 
   $ chmod a+x ~/bin/repo
   ```

2. 不能翻墙

   如果您的办公环境可以不能访问 Google 网站，您可以使用Rokid 修正版的 repo 工具。

   ```
   $ curl -Ls -o ~/bin/repo  http://scm-deps-library.rokid-inc.com/linux/buildroot_dl_aml/tools/repo
   $ chmod a+x ~/bin/repo
   ```

### 初始化 repo 客户端

需要根据您的开发板的芯片厂商来选择具体的代码下载库。我们最近在外网代码仓库中加入了权限管理，各位可以参考[配置代码权限](https://developer-forum.rokid.com/t/topic/1145)，申请账号，并配置权限。之后再执行以下命令，同步代码：

> 注意命令中的user对应的openai的用户名。

**以下示例同步的代码仅保证支持Amlogic-905D开发板。**

* 运行repo init

  * repo 是Google官方版本

  ```
  repo init -u ssh://{user}@openai.rokid.com:29418/amlogic-sdk-s9xx/manifest -m rokid_sdk_release.xml
  ```

  * repo 是Rokid 修正版本

  ```
  repo init -u ssh://{user}@openai.rokid.com:29418/amlogic-sdk-s9xx/manifest -m rokid_sdk_release.xml --repo-url=ssh://{user}@openai.rokid.com:29418/tools/repo --no-repo-verify
  ```

* 下载RokidOS 代码树

```
repo sync
```

* 编译代码树

  ```
  source
   build/envsetup.sh

      lunch nanat2-userdebug-32

  # 或 lunch 对应的id号 

      lunch 69
      make update-api
      make -j40
  ```

  > 如果用ubuntu16.04的版本，可能出现以下报错：  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_set16\_instance: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_set16\_instance: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_set32\_instance: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_set32\_instance: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_set\_obj\_instance: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_set\_obj\_instance: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_set64\_instance: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_set64\_instance: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_set64\_static: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_set64\_static: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_proxy\_invoke\_handler: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_resolution\_trampoline: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_resolution\_trampoline: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_generic\_jni\_trampoline: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_to\_interpreter\_bridge: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_to\_interpreter\_bridge: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_instrumentation\_entry: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_instrumentation\_entry: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_instrumentation\_exit: error: unsupported reloc 43  
  > out/host/linux-x86/obj32/SHARED\_LIBRARIES/libart\_intermediates/arch/x86/quick\_entrypoints\_x86.o:function art\_quick\_deoptimize: error: unsupported reloc 43  
  > host C++: libinput &lt;= frameworks/native/libs/input/KeyLayoutMap.cpp  
  > clang: error: linker command failed with exit code 1 \(use -v to see invocation\)  
  > build/core/host\_shared\_library\_internal.mk:51: recipe for target ‘out/host/linux-x86/obj32/lib/libart.so’ failed  
  > make: \*\*\* \[out/host/linux-x86/obj32/lib/libart.so\] Error 1  
  > make: \*\*\* Waiting for unfinished jobs…  
  > Install: out/host/linux-x86/bin/apicheck  
  > \`\`\`

  需要做以下修改：

  ```
  It works to me:
  in file /art/build/Android.common_build.mk, find out:
  # Host.
  ART_HOST_CLANG := false
  ifneq ($(WITHOUT_HOST_CLANG),true)
  # By default, host builds use clang for better warnings.
  ART_HOST_CLANG := true
  endif
  change to :
  # Host.
  ART_HOST_CLANG := false
  ifeq ($(WITHOUT_HOST_CLANG),false)
  # By default, host builds use clang for better warnings.
  ART_HOST_CLANG := true
  endif
  endif
  ```

### 结构

对于AMLOGIC开发板一共包含5个部分。

1. CPU板
2. MIC板
3. DEBUG板
4. CPU\_MIC连接排线
5. CPU\_DEBUG连接排线

[![](/2-RokidDocument/2-EnableVoice/images/structure.jpg)](https://developer-forum.rokid.com/uploads/default/original/1X/df46ea76dffd58093fdc833cc3722ef373a894d9.jpg)

### 连接方法

所有连接线对应的金手指均为向下扣。效果如图所示：

[![](/2-RokidDocument/2-EnableVoice/images/connect.jpg)](https://developer-forum.rokid.com/uploads/default/original/1X/b1e3a9d34be9d85e3fbc4b378cca9f9b7f3b6ae4.jpg)

> 注意：对于拿到我们测试机（对应下图）的开发者，请千万注意CPU\_DEBUG连接排线再CPU测是朝向上扣下，如下图红框，其余三端也是朝下扣。

[![](/2-RokidDocument/2-EnableVoice/images/connect1.jpg)](https://developer-forum.rokid.com/uploads/default/original/1X/6c40b3713f0f5ac24bb93fb4c1e2919e86f74271.jpg)

### 固件烧写

#### 固件位置

AMLOGIC 905D Android镜像具体位置及相关介绍如下：

```
out/target/product/p230/
    ├── aml_upgrade_package.img             #<< Amlogic 官方工具刷机包
    ├── upgrade/aml_upgrade_package.conf    #<< 分区配置分区
    ├── boot.img                            #<< 可 fastboot 刷机镜像，kernel、ramdisk 分区
    ├── dtb.img                             #<< 可 fastboot 刷机镜像，这是一个软链接，实际刷机时用指向的镜像
    ├── recovery.img                        #<< 可 fastboot 刷机镜像，OTA 功能主体
    ├── u-boot.bin                          #<< 可 fastboot 刷机镜像，bootloader 分区
```

#### 固件烧录方式

固件烧录可以有以下两种方式：

#### 整包烧录

1. 安装[Amlogic官方刷机工具11](https://scm-deps-library.rokid-inc.com/linux/buildroot_dl_aml/tools/aml_burn_img_tool_v2.1.2.exe)

   具体安装步骤，请参阅[Amlogic官方刷机工具使用说明9](https://rokid.github.io/rokidos-linux-docs/files/amlogic/AmlUSBBurning.pdf)。\(需要说明的是：最新工具其他品牌HUB也可以使用，或者无HUB直连也可以烧写）。

2. 参考镜像\(20171028\)地址: ftp://ftp-customer.rokid-inc.com:9921/images/nanat2/20171028/aml\_upgrade\_package.img

3. 进入刷机模式

首先：开发板核心板**TypeC**接口与**PC**已连接。

方法一：接上开发板配套的Debug 板 ，先按住Debug上的 &lt;**upgrade**&gt; 键不能松开，再按 &lt;**reset**&gt; 键，刷机工具界面出现已连接，请马上松开按键，即表示开发板已经进入刷机模式。

备注：如果用虚拟机，其中涉及到虚拟机usb口设备的选择，需要勾选

```
         Devices-USB-Amlogic GX Chip

         Devices-USB-Amlogic,Inc
```

方法二：通过 Debug 板上的 TypeC 连接串口线，开机后迅速按enter或者space，进入u-boot，输入update，您将看到刷机工具界面出现已连接，表示开发板已经进入刷机模式。

`shell Hit Enter or space or Ctrl+C key to stop autoboot -- : 0 nana_t2# nana_t2# nana_t2# nana_t2#`

方法三：如果您没有debug板或者debug已损坏，可以通过主板上面的测试点短接，主板上面reset对应debug的reset按键，u对应debug上面的update按键。具体位置如下图，具体操作跟方法二一样：

[![](/2-RokidDocument/2-EnableVoice/images/HW reset.jpg)](https://developer-forum.rokid.com/uploads/default/original/1X/f9778b5ccb0bbdc057d94ad078d86cb198276ebb.jpg)

方法四：如果您的开发板系统是**Android**系统\(支持ADB\)，  
   `adb shell reboot update`  
   ，您将看到刷机界面出现已连接，表示开发板已经进入刷机模式。  
   [![](/2-RokidDocument/2-EnableVoice/images/fuse.jpg)](https://developer-forum.rokid.com/uploads/default/original/1X/8607325738dc10c909d03eb12eca21a2dda2df39.jpg)

1. 刷机工具刷机。点击刷机工具中的"**开始**"按钮，开始刷机，并等待刷机完成，请按照刷机工具中的提示操作。图中对应的刷机工具版本是usb buring tool v2.1.2。

> 注意：**右上角如果勾选擦除flash**，则会擦除整个flash或者emmc，如果不勾选只会烧写。则只会擦除aml\_upgrade\_package.conf对应的分区。所以如果需要保存data分区开发者，请注意此选项。

### fastboot烧录

1. 进入 fastboot 模式

   首先：开发板核心板**TypeC**接口与**PC**已连接。  
   方法一：通过 Debug 板上的**TypeC**连接串口线，进入u-boot，输入`fastboot`，开发板会进入fastboot模式。\(备注：有时需要sudo fastboot）  
   方法二：如果您的开发板系统是**Android**系统，`adb shell reboot fastboot`，开发板会进入fastboot模式。

2. 刷机指令

2.1镜像文件与设备分区的对应关系

Amlogic芯片的开发板，您可以通过查看\*\* aml\_upgrade\_package.conf \*\*文件内容，如`cat aml_upgrade_package.conf`，来找到一些线索。

```
#This file define how pack aml_upgrade_package image

[LIST_NORMAL]
#partition images, don't need verfiy
file="u-boot.bin.usb.bl2"   main_type= "USB"            sub_type="DDR"
file="u-boot.bin.usb.tpl"   main_type= "USB"            sub_type="UBOOT"
file="u-boot.bin.sd.bin"    main_type="UBOOT"           sub_type="aml_sdc_burn"
file="platform.conf"        main_type= "conf"           sub_type="platform"
file="aml_sdc_burn.ini"     main_type="ini"             sub_type="aml_sdc_burn"
file="dtb.img"              main_type="dtb"             sub_type="meson1"

[LIST_VERIFY]
#partition images with verify
file="boot.img"             main_type="PARTITION"       sub_type="boot"
file="recovery.img"         main_type="PARTITION"       sub_type="recovery"
file="rootfs.ubifs"         main_type="PARTITION"       sub_type="system"    file_type="ubifs"
file="u-boot.bin"           main_type="PARTITION"       sub_type="bootloader"
file="dtb.img"              main_type="PARTITION"       sub_type="_aml_dtb"
```

2.2开发板是 Linux 系统

在PC端执行如下指令：

```
fastboot flash bootloader u-boot.bin
fastboot flash dtb <开发板型号>.dtb
fastboot flash boot boot.img
fastboot flash system rootfs.ubifs
fastboot flash recovery recovery.img2.3
```

2.3开发板是 Android 系统

在PC端执行如下指令：

```
fastboot flash bootloader u-boot.bin
fastboot flash dtb dtb.img
fastboot flash boot boot.img
fastboot flash system system.img
fastboot flash recovery recovery.img
fastboot flash data userdata.img
```



