# YodaOS 杭研移动和家固话+云网关方案 V1.0

* 版本：V1.0
* 方案撰写：陈国龙、李林超、梁宁清、张品、黄克雷、李玉娜

##方案介绍

杭研基础SDK比较多，流程复杂，本方案的目的是让厂商设备能够快速集成杭研和家固话、云网关能力，并进入杭研产品库。和家固话+云网关方案是基于 `YodaOS` 方案，目前同时支持 `A113` 和 `K18` 芯片。

* 和家固话提供登录、来电监听、拨打、 接听、挂断电话、语音会议等功能。
* 云网关提供 Andlink 云网关，本地智/Users/peterchen/Downloads/cooperation/移动和家固话方案/杭研移动和家固话+云网关方案V1.0/框架方案.jpeg
能网关方式为设备进行配网功能

本方案分为认证方案流程、设计方案、代码移植流程、业务介绍、测试方案：

##认证方案

产品进入中国移动杭研产品库，必须按照杭研提供的一系列技术文档标准、接入 SDK 和认证服务，流程详细如下：
![认证流程](http://markdownpicture.test.upcdn.net/2019/05/14/upload_xu79xd69s5x2wav7fbutuewuq88c1a3e.jpeg)

杭研入库前测试一般是先在测试环境上测试，再上线上环境，所以测试时必须保证两边环境一一对应，如杭研测试环境对应ROKID 测试环境。

##设计方案
整个云网关和云固话，涉及到杭研云网关、和家亲、和家固话、YodaOS、ROKID 服务端的交互，才能完成整个配网、登录、使用 ROKID 语音服务，和家固话功能，完成整套方案。整体框架图如下：

![框架方案](http://markdownpicture.test.upcdn.net/2019/05/14/upload_4tstec0pg7shlp4zm8r0mqdf58rqul2w.jpeg)


简单描述：设备使用杭研和家亲APP配网，配网方式是 Andlink 配网。配网成功之后，该设备会在杭研服务端和 ROKID 服务端会分别注册一个账号，同时和家固话同步此设备账户。和家固话与 ROKID服务端交互主要有通讯录变更通知、解绑\添加、启用\禁用、更新密钥操作等。

注意事项如下：

* 设备需要授权和家亲技能方可进行电话功能
* ROKID 服务端需要有设备 sn 和 MAC 地址映射表，此表用于杭研服务端和 ROKID 服务端鉴权需要
* 需要先测试云网关，再测试和家固话，如果顺序颠倒，可能会出现异常问题，比如通讯录获取失败
* 和家固话通讯录需要同步到 ROKID 服务器上
* 解绑\添加、启用\禁用、密钥（secret）更新通知需要同步到 ROKID 服务器上

##业务介绍

* 云网关：详细请看云网关业务文件夹
* 和家固话：详细请看和家固话业务文件夹

##代码移植流程

###拉取云网关相关代码

* 厂家在自家的 `xml` 文件里面添加云网关仓库，以 `yodaos-v7.31.x-20190117.xml` 为例如下：

```
$ vi .repo/manifests/yodaos-v7.31.x-20190117.xml
```

添加如下代码到文件中：


```
...

<project name="kamino_rokidos/applications/qlink-network" path="applications/qlink-network" revision="v1.0.1"/>

...
```

添加完成，保存退出后，拉取最新代码：

```
$ repo sync
```

拉取到的云网关相关代码在 `applications/qlink-network` 目录下:

```
$ ls -al applications/qlink-network
```

###更改配置

#####在云网关注册、上线时，传参时需要 `devicetype，productToken` 等字段，不同厂家使用的配置不同，所以其他厂家在使用云网关方式配网时，需要填写在杭研平台申请的配置。具体更改配置方法以 `Rokid-Mini`为例：

> 1、新建设备配置项，以设备名称 `${PRODUCT_NAME}` 为目录名字

```
$ cd applications/qlink-network/custom
$ mkdir Rokid-mini
```

> 2、创建 `config.json` 文件和 `media` 目录。

```
$ cd Rokid-mini
$ vi configure.lua
```
在 `config.json` 中填入下列代码。

```
{
  "deviceType": "xxxxxx",
  "productToken": "xxxxxx",
  "defaultApAddr": "192.168.188.1"
}
```

`media` 目录为音频文件,并添加相应音频文件。

```
$ mkdir media
```

###设备 WIFI AP 模式支持

由于云网关需要设备WIFI在 AP 模式下配网，需要添加相应 AP 模块：

```
$ vi mini_yodaos/products/rokid/a113-mini/configs/yodaos_a113_mini_defconfig
```
添加如下配置文件
```
···
CONFIG_PACKAGE_hostapd=y
CONFIG_PACKAGE_dnsmasq=y
···
```
###云固话差异化配置

###拉取云固化相关代码
* 厂家在自家的 `xml` 文件里面添加云网关仓库，以 `yodaos-v7.31.x-20190117.xml` 为例如下：

```
$ vi .repo/manifests/yodaos-v7.31.x-20190117.xml
```

添加如下代码到文件中：

```
...

<project name="kamino_rokidos/applications/voip-cmcc" path="applications/voip-cmcc" revision="v1.0.1"/>
<project name="kamino_rokidos/open-platform/embedded-linux/cmcc_voip" path="applications/voip-service" revision="v1.0.1"/>

...
```

添加完成，保存退出后，拉取最新代码：

```
$ repo sync
```

拉取到的云网关相关代码在 `applications/` 目录下:

```
$ ls -al applications/voip-service
$ ls -al applications/voip-cmcc
```

###更改配置
#####在SDK初始化时需要通过 `appkey,appsecret` 来进行注册 `ims` 信息，不同厂家配置不同，具体更改配置方法以 `Rokid-Mini`为例

```
$ cd applications/voip-cmcc/custom
$ mkdir Rokid-mini
```

> 2、创建 `config.json` 文件和 `media` 目录。

```
$ cd Rokid-mini
$ vi config.json
```
在 `config.json` 中填入下列代码。

```
{
  "appkey": "xxxxxx",
  "secret": "xxxxxx",
  "deviceType": "xxxxxx"
}
```

`media` 目录为音频文件,并添加相应音频文件。

```
$ mkdir media
```
##产品编译配置
##### 添加以上应用配置，以 `Rokid-Mini` 为例
```
$ vi products/rokid/a113-mini/CMakeLists.txt
```
添加配置如下

```
···

function(YodaLocalApp NAME)
    message("the include path: ${CMAKE_INCLUDE_DIR}")
    message("the platform: ${TARGET_PLATFORM}")
    message("the product name: ${PRODUCT_NAME}")
    ExternalProject_Add(${NAME}
        SOURCE_DIR "$ENV{TOPDIR}/../applications/${NAME}"
        CMAKE_ARGS
            -DCMAKE_INSTALL_DIR=${CMAKE_INSTALL_DIR}
            -DCMAKE_INCLUDE_DIR=${CMAKE_INCLUDE_DIR}
            -DCMAKE_TARGET_PLATFORM=${TARGET_PLATFORM}
            -DCMAKE_PRODUCT_NAME=Rokid-mini)
endfunction()

YodaLocalApp("qlink-network")
YodaLocalApp("voip-cmcc")
YodaLocalApp("voip-service")

···
```
添加成功后，即可开始编译。

## 开始调试
###云网关配网测试
1、首先下载和家亲测试APP：
2、设备上电将设备切为配网测试模式，

## 常见问题
1、配网时，听到设备TTS：正在连接中国移动网络...,之后仍报配网失败
首先检查APP是否时测试 APP 还是线上 APP，通过和家亲 APP 中 我的->设置->关于我们 中查看
其次输入以下命令检查设备是测试环境还是线上环境
```
adb shell getprop persist.sys.rokid.sandbox
```
其中 0或者为空是线上环境, 1 代表测试环境，须保证 APP 和 设备都为测试环境或者线上环境

2、更改前端配置
## H5 页面制作流程
详见 H5 页面制作文件夹
##测试方案
详见测试方案文件夹，里面有详细的的测试方案和相应测试用例. 





