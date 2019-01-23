YodaOS Build Environment
==================
This article introduces how to build environment/download/build/upgrade.

##Build Compiling Environment
#### Linux Compiling Enviroment
*	YodaOS supports Ubuntu 14.04/16.04 LTS

#### Install depended-upon packages
```
sudo apt-get install build-essential subversion libncurses5-dev zlib1g-dev gawk gcc-multilib flex git-core gettext libssl-dev unzip texinfo device-tree-compiler dosfstools libusb
```

## Download Source Code
YodaOS Project use Gerrit system from Google to manage the source code, will be open with github later.

#### Sign up to the developer of Rokid
*	Login Method
Search https://openai-corp.rokid.com , the Rokid Developer website. If you are not already registered to Rokid Developer, sign up for a free account and within seconds you will get the gerrit page.
*	Access Permission 
Gerrit service supports SSH download only, you must add public key to the account.（the account->Settings->ssh public keys->add key）The developer must have specific authorization before downloading.

#### Install repo
* Create a new bin directory in your home directory.

```
$ mkdir ~/bin
$ PATH=~/bin:$PATH
```

*	Get repo tool（circumvention technology）

```
$ curl https://storage.googleapis.com/git-repo-downloads/repo > ~/bin/repo
$ chmod a+x ~/bin/repo
```
*	get repo tool (harmonious society)

```
  $ curl https://scm-deps-library.rokid-inc.com/linux/buildroot_dl_aml/tools/repo > ~/bin/repo
  $ chmod a+x ~/bin/repo
```

#### Download source code
Take the stable branch 7.30.x for example
* repo init (google)

```
  repo init -u ssh://username@openai-corp.rokid.com:29418/kamino_universal_cust/open-platform/manifest -m yodaos-v7.30.x-20190103.xml
```
 * repo init (rokid)
 
```
  repo init -u ssh://username@openai-corp.rokid.com:29418/kamino_universal_cust/open-platform/manifest -m yodaos-v7.30.x-20190103.xml -repo-url=ssh://username@openai-corp.rokid.com:29418/tools/repo  --no-repo-verify
```

*	repo sync 
     
## Compile Environment
#### Configure Environment
*	source envsetup.sh
    [0] broadcom_bcm2710_rpi3b_plus
    [1] leo_gx8010_ota_1v
    [2] leo_gx8010_rkd_1v
    [3] leo_gx8010_rkd_2v
    [4] leo_gx8010_rkd_3v
    [5] leo_gx8010_rkd_4v
    [6] leo_gx8010_rkd_naboo_chinateleom
    [7] leo_gx8010_rkd_naboo_chinaunicom
    [8] leo_gx8010_rkd_naboo
    [9] leo_gx8010_rkd_naboo_yodaos
    [10] leo_gx8010_rkd_naboo_yodaos_hostap
    [11] leo_gx8010_rkd_naboo_yodaos_telecom
    [12] leo_gx8010_ssd_1v
    [13] leo_gx8010_ssd_1v_yodaos_display
    [14] leo_k18_cus360
    [15] leo_k18_cus360_native
    [16] leo_k18_cus360_ota
    [17] leo_k18_dev311
    [18] leo_k18_dev311_ota
    [19] leo_k18_dev31
    [20] leo_k18_dev32
    [21] leo_k18_dev33
    [22] leo_k18_dev33_ota
    [23] leo_k18_dev34
    [24] leo_k18_dev34_ota
    [25] leo_k18_universal_avs
    [26] leo_k18_universal
    [27] leo_k18_universal_node
    [28] leo_k18_universal_yimo
    [29] leo_k18_universal_yodaos_display
    [30] yodaos_a113_dev11
    [31] yodaos_a113_mini
    [32] yodaos_a113_ota
    [33] yodaos_a113_rokidme
    [34] yodaos_a113_rokidmini
    [35] yodaos_a113_rokidmini_ota
    [36] yodaos_a113_tuyamini
    [37] yodaos_a113_tuyamini_ota
    Which would you like? [8]
   
*	Select K18 dev33 configure
	[21] leo_k18_dev33
	
*	Select A113 mini configure
	[31] yodaos_a113_mini  

*	Select file system type（default ubifs）
    Lunch menu... pick a root filesystem:
    1. ubifs(root filesystem is read wirte)
    2. squashfs(root filesystem is read only)
    Which would you like? [1]

*	Select debug or release mode（default debug）
    You are building on Linux
    Lunch menu... pick a image style:
    1. debug(root filesystem bin is not striped)
    2. release(root filesystem bin is striped)
    Which would you like? [1]
  
#### Compile 
*	make -j1 V=s 


## Upgrade guide
#### Amlogic A113 Chip
*	the generated image path
```
    ├── aml_upgrade_package.conf       		#<< partition table information
    ├── aml_upgrade_package.img        		#<< Amlogic upgrade image with official upgrade tools
    ├── aml_upgrade_package_squash.conf		#<< squash partition table information
    ├── boot.img                       		#<< fastboot upgrade image(kernel & ramdisk)
    ├── dtb.img						 		#<< fastboot upgrade image(dtb)
    ├── recovery.img						#<< fastboot upgrade image(for ota)
    ├── rootfs.ubi							#<< fastboot upgrade image(file system)
    ├── u-boot.bin							#<< fastboot upgrade image(bootloader）
```
    
*	upgrade methods
	*	windows upgrade
        *	Install [Amlogic offical upgrade tool](https://scm-deps-library.rokid-inc.com/linux/buildroot_dl_aml/tools/aml_burn_img_tool_v2.1.2.exe)
            Please refer to the detailed installation steps [Amlogic offical upgrade tool guide](https://rokid.github.io/rokidos-linux-docs/files/amlogic/AmlUSBBurning.pdf).
        *	Select upgrade image
            Open Amlogic offical upgrade tool，choose item "File"->"Import image", then select "aml_upgrade_package.img" in the file dialog box.
        *	Connect the development board to the computer with Type-C.
        *	adb shell reboot update
           This command performs the device into DFU mode after reboot, and the tool will appear the succeesful connection.
        *	click the item "Start" to upgrade the device，within minutes the tool will shows the completed information.

	*	fastboot upgrade
[TBD]

#### K18 Chip
*	the generated image path
    openwrt/bin/leo-k18-universal-glibc/
    
```
    ├── bootmusic.wav                                       #<< starting music
    ├── bootx												#<< linux upgrade tool
    ├── bootx_win                                           #<< windows upgrade tool
    ├── download.bat									    #<< windows upgrade script
    ├── download.sh											#<< linux upgrade script
    ├── env.bin												#<< env partition image
    ├── gen_swupdate_img.sh									#<< packaging script
    ├── mcu.bin												#<< mcu partition image
    ├── md5sums												#<< md5sum value
    ├── openwrt-leo-k18-universal-app.img					#<< Data partition app image
    ├── openwrt-leo-k18-universal.dtb						#<< kernel dtb image
    ├── openwrt-leo-k18-universal-ext4.img					#<< unuse
    ├── openwrt-leo-k18-universal-fit-uImage.itb			#<< unuse
    ├── openwrt-leo-k18-universal-rootfs.tar.gz				#<< unuse
    ├── openwrt-leo-k18-universal-sdcard-vfat-ext4.img		#<< unuse
    ├── openwrt-leo-k18-universal-squashfs.img				#<< unuse
    ├── openwrt-leo-k18-universal.swu						#<< unuse
    ├── openwrt-leo-k18-universal-ubifs.img					#<< rootfs ubifs
    ├── openwrt-leo-k18-universal-ubi.img					#<< rootfs partition ubifs image
    ├── openwrt-leo-k18-universal-u-boot.img				#<< unuse
    ├── openwrt-leo-k18-universal-u-boot-spl.bin			#<< unuse
    ├── openwrt-leo-k18-universal-uImage					#<< unuse
    ├── openwrt-leo-k18-universal-zImage					#<< kernel image
    ├── openwrt-leo-ota-fit-uImage-initramfs.itb            #<< Recovery image
    ├── packages                                            #<< ipkg 
    ├── sha256sums											#<< sha256 value
    └── sw-description										#<< unuse
```
*	upgrade methods
    *	Linux PC
        *	$ cd openwrt/bin/leo-k18-universal-glibc/
        *	sudo cp bootx /usr/local/bin/ 
        *	./download.sh all
        *	press and hold the UPGRADE/BOOT key on the device，then connect it to the compute, pwower on.
        
    *	windows
        *	Install usb driver
        (the driver files in leo-k18-universal-glibc/bootx_win/driver_install directory)
        *	cd $(K18DIR)/openwrt/bin/leo-k18-universal-glibc/ 
        *   cp bootx_win/bin/bootx.exe ./
        *	dblclick download.bat
        *	press and hold the UPGRADE/BOOT key on the device，then connect it to the compute,power on.


## Configure System and Application
YodaOS Project is based on the openWRT，so you would like have a general outline to begin with.  

#### Openwrt directory
##### Original
*	scripts
    contains some compiling scripts, such as bash/python/perl scripts and so on.
    
*	tools
   automake, autoconf, sed, cmake
*	config
    contains the system configs
*	configs
    contains the board defconfigs
*	docs
    contains the openWRT module guide. 
*	toolchain
    contains cross compilation tool chains，such as binutils/uClibc/gcc/glibc and so on.
*	target
contains many board firmware and kernel modules, to generate the kernel and firmware image.
*	package
    The OpenWrt distributions provide several thousand packages to extend the functionality of your device.    
*	package/rokid/
    	some rokid packages for YodaOS Project
*	include
    Contains some *.mk files for compiling, are included in makefiles.
*	feeds
    feeds are retrieved and managed by scripts/feeds, a perl script. The feeds script reads the configured feeds, obtains the current or specified version of each of them, and “installs” them. The default package contains packages、management、luci、routing and telephony. If want install other package, you can modify feeds.conf.default and update it.
    
    * Update the package: 
    ./scripts/feeds update -a 
    * Install the downloaded package: 
    ./scripts/feeds install -a
*	dl
    download source code of packages when compiling.  
*	others

    *	Makefile:
This file is executed by make command in the top-level directory.
    *	rules.mk
    define some generic variables and functions for makefile 
    *	Config.in
    The file associated with the configure by making menuconfig.
    * feeds.conf.default
    The file used to download some third-party software packages.
    *	LICENSE & README
    the software license and the basic description of the software
    
##### build directory
*	build_dir
contains host, toolchain-XXX and toolchain-XXX.
 * host
    compile the tools used by the host in this directory. 
 *	toolchain-XXX
    compile the cross-compile toolchain in this directory.
 *	target-XXX
    compile the target platform and packages in this directory.
*	bin
    contain the binary files and all the ipk files.
*	staging_dir
    store the compiled packages and install the cross-compile toolchain in the build_dir directory. 
*	tmp
    the temp directory
*	logs
    This folder, sometimes you can see it, sometimes you don't. It appears while wrong, so you can get and analyze the wrong information.    
   
#### Custom configure
*	make menuconfig and modify configure
*	diffconfig.sh

```
./scripts/diffconfig.sh > configs/<board>_defconfig
```

#### Compile package
*	clean, compile, install package

```
make package/<name>/{clean,compile,install}
```
*	clean, compile, install toolchain

```
make toolchain/{clean,compile,install}
```

#### Compile uboot
*	compile

```
make package/uboot-leo/compile
```
*	install

```
make package/uboot-leo/install
```

#### Compile kernel
*	compile modules

```
make target/linux/compile
```
*	compile zImage、dts and install

```
make target/linux/install
```

#### Configure kernel
```
make kernel_menuconfig
```

#### Choose Debug/Release
*	source envsetup.sh
```
    ...
    ...
    You are building on Linux
    Lunch menu... pick a image style:
    1. debug(root filesystem bin is not striped)（limited by the size of K18, the root filesystem bin is striped）
    2. release(root filesystem bin is striped)
```

*	./build.sh add the -d option
```
./build.sh -p leo_k18_universal_node -n openwrt-leo-k18-universal -f leo-k18-universal  -j32 -r -d
```
*	Release mode
```
    1. the debugger doesn't need to package into image file.   
    2. change the RKlog's default level to info.
```
*   Debug mode
```
    1. enable macro CONFIG_DEBUG.
    2. copy and install test tools into the image according to the macro definition.
    3. change the RKlog's default level to debug.
    4. add gdb/strace/valgrind and so on.
```

#### add custom package
*	please refer to https://openwrt.org/docs/guide-developer/helloworld/chapter3

#### add system service
*	take alab-libs for example, the customer does not want to run it while booting.
*	modify configure by the macro definition.
```
    menu "Configuration"

    config TURENPROC_AUTO_RUN
        bool "auto run"
        default y
        help
            turenproc service auto run

    endmenu
```

*	determine whether to start up by the macro TURENPROC_AUTO_RUN definition.
```
    if [ "$(CONFIG_TURENPROC_AUTO_RUN)" != "y" ]; then \
$(SED) "s/^START/#START/g" $(1)/etc/init.d/turenproc; \
fi
```