# Linux 系统设计

## 系统架构图
![Rokid_Linux_Architecture](images/Rokid_Linux_Architecture-1.png)

## 系统特性

模块 | 功能介绍 | 代码位置 | 实现语言 | 状态
--- | --- | --- | --- | ---
AMS | Application Manager Service Rokid语音应用的生命期调度、事件分发框架 | robot/openvoice/ams | C | 支持
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

## Linux开源编译框架
* Buildroot

### BuildRoot Package

#### 扩展的buildroot_external

rokid_br_external 是 Rokid 通过 BuildRoot 的 external 机制，将 Rokid 提供的包或第三方库的编译配置放在此处

#### FFWT
  
需要使用Rokid对该包的配置，核心的语音算法会依赖该动态库

#### NE10
  
需要使用Rokid对该包的配置，核心的语音算法会依赖该动态库

#### Node.js

需要使用 Rokid 对该包的配置，CloudappClient-Nodejs 依赖该配置

#### tinyplay

需要使用 Rokid 对该包的配置，目前 Mic Array 使用了 tinyplay 接口读取数据，而 Amlogic 源码释放出的 tinyplay
版本存在超过2个channel时读取音频数据会存在 Bug，所以需要使用 Rokid 目前配置的版本。

