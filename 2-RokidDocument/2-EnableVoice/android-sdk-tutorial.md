#### ROKID 前端语音快速集成指南
 
完整的[下载地址](https://github.com/Rokid/openvoice-android-ndk/tree/deprecated) ，选择 deprecated 分支，其包含了：前端激活，降噪，VAD，寻向，音墙，仲裁；NLP语音识别，语义理解；ASR语音识别；TTS语音合成等等。支持 Android 4.4 及以上版本。
```
git clone https://github.com/Rokid/rokid-openvoice-process-android-ndk.git -b deprecated
```

使⽤步骤：
第⼀步：ROKID账号体系

1、进入Rokid开放平台22申请Rokid账号，已经有Rokid账号的同学可直接登录（但需进行部分信息补全）。
2、登录后点选「语音接入」进行设备认证信息申请。
3、具体做法：语音接入 > 创建新设备 > 填写设备名称 > 创建认证文件。之后您将获得：
account_id、device_type_id、device_id、secret、key
把得到账号填⼊到 rokid-openvoice-process-android-ndk/assets/etc/openvoice_profile.json 这个⽂件被编译到 system/etc/ ⽬录

第二步：打包(非常重要)

默认使用附件1开发板配置。如果是其他的开发板可以添加配置文件，如何配置见附件2，将配置文件放到 rokid-openvoice-process-android-ndk/assets/etc 目录，命名方式以 blacksiren_xxxx.json，然后在 device/<company>/<device>/device.mk Makefile 中添加宏定义 ROKID_BLACKSIREN_CONFIG := xxxx，以后整编便会使用该配置。最后在您产品的 device/<company>/<device>/device.mk Makefile 中添加如下代码

注意路径 
```
include rokid-openvoice-process-android-ndk/device/amlogic/p230/openvoice.mk
```
第三步：编译

将 sdk 放到 Android 源码目录下，第一次需要完整编译， 编译成功之后将镜像刷入开发版，后续 mm 编译即可。最终会以一个 Android 标准应用程序，被放到 /system/priv-app/ 目录下自动运行。

编译完成后可以在如下⽬录下拿到BearKid Jar包获取 NLP 消息
out/target/common/obj/JAVA_LIBRARIES/BearKidAdapter_intermediates/classes.jar
![](前端语音快速集成指南image.jpg)