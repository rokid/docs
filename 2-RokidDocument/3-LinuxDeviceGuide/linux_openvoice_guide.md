# 开发者社区 Linux 设备开发引导

## 支持的开发板

芯片厂商 | 芯片型号 | 开发板内部代号 | 编译框架 | 状态
--- | --- | --- | --- | ---
Amlogic | A112 | nana_l | buildroot | 支持
Amlogic | S905D | nana_t | buildroot | 支持
Amlogic | S905D | nana_t2 | buildroot | 支持
Amlogic | S905D | rm101 | buildroot | 支持
Amlogic | S905D | rp102 | buildroot | 支持
Amlogic | A113 | banban_m | buildroot | 开发中

## 系统架构图
![Rokid_Linux_Architecture](images/Rokid_Linux_Architecture-1.png)

## 系统特性

模块 | 功能介绍 | 代码位置 | 实现语言 | 状态
--- | --- | --- | --- | ---
AMS | Application Manager Service Rokid语音应用的生命期调度、事件分发框架 | robot/openvoice/ams | C | 开发中
Speech SDK | 封装了与Rokid云服务交互协议，包括ASR、NLP、TTS等开发服务 | robot/openvoice/speech | C++ | 支持
Blacksiren SDK | 输入麦克风数据，经内部拾音算法及云端服务（调用SpeechSDK），输出语音识别结果、各种拾音事件 | robot/openvoice/blacksiren | C++ | 支持
openvoice_proc Service | 将Blacksiren封装成服务 | robot/openvoice_proc | C++ | 支持
Linux systemd | Linux Init System -- systemd |  | C/C++ | 支持
openvoice app Zygote | 由该进程负责启动所有语音应用 | robot/service/zygote  | C/C++ | 支持
PulseAudio | 提供Audio服务及路由机制 | buildroot原生 | C | 支持
TTSFlinger Service | 提供设备端的语音转文字服务 | robot/services/ttsflinger | C++ | 支持
Lumenflinger | 提供灯光渲染服务 | robot/services/lumenflinger | C++ | 支持
BTFlinger | 提供蓝牙功能 | robot/services/btflinger | C | 支持
系统电量服务 | 系统电量服务 | | C/C++ | 支持
应用包管理 | 应用安装升级 | | C/Node.JS | 支持
OTA | 系统升级 | | C | 支持
蓝牙配网服务 | 提供通过蓝牙来配置Wifi网络 |  | C | 支持
热点配网 | 提供通过设备开启热点方式来配置网络 |  | C | 开发中
CloudClient C版 | 实现Cloud Skill功能／应用支持（如天气、新闻、音乐等），适用小内存系统 | |  C | 开发中
CloudClient Nodejs版本 | 实现Cloud Skill功能／应用支持（如天气、新闻、音乐等Cloud应用）、适用大内存系统 | | C/Node.JS | 支持
系统音量控制 | 提供系统及的音量控制服务 | | C/C++/Node.JS | 支持
灯光寻向指示 | 提供唤醒、对话时的寻向指示 | | C/C++/Node.JS | 支持
媒体播放器 | 媒体播放器 | robot/external/librplayer | C/C++ | 支持
蓝牙音乐应用 | 媒体播放器 | robot/apps/xxx | C/C++ | 支持
聊天应用 | 提供系统语音聊天服务 | | C/C++/Node.JS | 支持 
Android ADB | 提供ADB支持，方便开发 | | C++ | 支持
Android HAL | 提供Android HAL，方便实现Mic Array，Led Array， Sensor等 | | C++ | 支持
Android Binder | 提供进程间通讯机制 | | C++ | 支持
Input Manager | 提供按键、触摸、鼠标事件SDK | | C++ | 支持


## 编译

### 环境要求

- Ubuntu 14.04.5 LTS
- gcc 4.8.4 及以上

### Amlogic芯片

### Rokid对厂商代码的修改

#### U-Boot

修改了厂商代码，支持Rokid的板级配置目录

#### Kernel

修改了厂商代码，支持Rokid多型号板子的DST配置目录

#### BuildRoot Package

##### 扩展的buildroot_external

rokid_br_external 是 Rokid 通过 BuildRoot 的 external 机制，将 Rokid 提供的包或第三方库的编译配置放在此处

##### FFWT
  
需要使用Rokid对该包的配置，核心的语音算法会依赖该动态库

##### NE10
  
需要使用Rokid对该包的配置，核心的语音算法会依赖该动态库

##### Node.js

需要使用 Rokid 对该包的配置，CloudappClient-Nodejs 依赖该配置

##### TinyPlay

需要使用 Rokid 对该包的配置，目前 Mic Array 使用了 Tinyplay 接口读取数据，而 Amlogic 源码释放出的 Tinyplay
版本存在超过2个channel时读取音频数据会存在 Bug，所以需要使用 Rokid 目前配置的版本。

##### 编译指令

目前支持64位版本，32后续会考虑支持。

```
source rokid_br_external/build/setenv.sh
```
输出
```
Environment setting is OK!
Just type 'lunch' and you will get a list of choices, or you can type 'lunch [choice]' to lunch directly.
```

```
lunch
```

输出
```
You are building on Linux
echo Lunch menu... pick a combo:
1. nana_t_s905d_release
2. nana_l_a112_release
3. rm101_s905d_release
4. rp102_s905d_release
5. banban_m_a113_release
6. nana_t2_s905d_release

Which would you like? [2]
```

##### 目前使用注意事项

###### 关于刷机
如果你的设备是mini没有接串口，无法在U-Boot下进入刷机模式,请看如下指示：
刷机镜像是：output/rm101_s905d/images/aml_upgrade_package.img
先打开PC端的windows版的amlogic刷机工具，Amlogic也提供了linux版本。

mini让他进入update模式的指令（无串口，无法进入uboot的情况下）,
adb shell登录到设备上，敲如下指令：

```
fw_setenv bootcmd "run update"
reboot
```

之后PC端的刷机程序就会检测到设备进入刷机模式，按软件的刷机提示刷机即可。

###### 关于配置网络
由于目前配网模块还在开发中，需要手动配置：

```
vi /etc/wpa_supplicant.conf
```

将

```
4 network={
5   key_mgmt=NONE
6 }
```
  
修改为：

```
network={
   ssid="你的WiFi网络名"
   psk="你的密码"
}
```  

然后启动网络

```
/etc/init.d/S42wifi stop
/etc/init.d/S42wifi start
```
