# RokidOS 源代码 #

RokidOS 是一个针对多种不同设备类型打造的开放源代码以语音交互为特色的软件堆栈。RokidOS 主要目的是为运营商、设备制造商、DesignHouse 和开发者创造一个开放的软件平台，使他们能够将创新理念变为现实，并推出能够卓有成效地改善用户体验的真实产品。

## 系统架构图
![Rokid_Linux_Architecture](../../files/RokidOS_Architecture-1.png)

## 语音数据流示意图
![Rokid_Sdk_Architecture](../../files/Rokid_Sdk_Architecture.png)


* **语音数据处理**
    
    语音数据处理顾名思义就是对麦克风采集的数据流进行处理，主要由降采样模块(RS)，声音寻向(SL)，波束形成(BF)，自身音源消除模块(AEC)，噪音消除模块(NS)，人声检测(VAD)，语音激活(VT)，opus 编码器(COD)等算法组成，并封装在 SDK Blacksiren 中。

* **OpenVoice Processor**
   
    对应Openvoice Service，将Blacksiren封装成服务，维护拾音、唤醒、云端识别解析业务的状态。

* **唤醒词检测引擎**
    
    使用激活算法实时检测唤醒词，一旦激活成功，将结果返回 OpenVoiceproc Service，再对语音数据做一系列处理。若激活失败则不做任何处理。

* **Speech Communication Library**
    
    Rokid语音通讯库，封装了与 Rokid 云服务交互协议，包括自动语音识别(ASR)、自然语言处理(NLP)、语音合成(TTS)等云端服务。

* **VUI**
    
    语音交互应用框架，通过上层自然语言处理结果，将不同的语音指令解析到特定应用中，并完成一次语音交互过程。框架支持本地应用、轻应用以及云端应用三种运行形态，开发者根据不同的需求，可以在三种形态中自由切换。

## 系统特性
* **Linux Native Services**
	* **systemd** Linux Init System - systemd 管理各种服务进程
	* **PulseAudio** 提供 Audio 服务及路由机制

* **Rokid Openvoice SDK**
	* **Speech SDK** 封装了与 Rokid 云服务交互协议，包括 ASR、NLP、TTS 等云端服务
	* **Blacksiren SDK** 输入麦克风数据，经内部拾音算法及云端服务（调用 SpeechSDK ），输出语音识别结果、各种拾音事件

* **Rokid System上的基础组件**
	* **媒体播放库** 提供媒体播放功能
	* **Android Binder** 提供 Android 系统进程间通讯机制
	* **Android HAL** 提供 Android HAL 功能
		* Android HAL 移植到Linux系统，方便实现 Mic Array，Led Array，Sensor 等

* **Rokid System Services/Framework**
	* **OpenvoiceProc Service** 将 Blacksiren 封装成服务，维护拾音、唤醒、云端识别解析业务的状态
	* **Openvoice App Zygote** 由该进程负责启动所有语音应用
	* **系统音量控制** 提供系统的音量控制服务
	* **Input Service** 提供按键、触摸、鼠标事件服务
	* **TTSFlinger Service** 提供设备端的语音转文字服务
	* **LumenFlinger Service** 提供灯光渲染服务
	* **BtFlinger Service** 提供蓝牙功能
	* **系统电量服务** 系统电量服务
	* **应用包管理** 应用安装升级
	* **OTA** 系统升级
	* **蓝牙配网服务** 通过蓝牙BLE来配置Wifi网络

* **Rokid Node.js Runtime**
	* **Voice User Interface** Rokid 语音交互接口(VUI)，应用的生命期调度、事件分发框架

* **Rokid System Apps**
	* **CloudAppAgent** 云应用通用客户端
		* 支持天气、新闻、音乐、聊天、百科等云应用
	* **灯光寻向指示**
	* **蓝牙音乐应用**

* **调试开发工具**
	* **Android ADB** 提供 ADB 支持，方便开发
	* **手机端蓝牙配网应用** 提供手机端配网及相关功能


