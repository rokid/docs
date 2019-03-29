# Rokid语音SDK使用文档

## 目录
* [一、概述](#一、概述)
* [二、集成准备](#二、集成准备)
  * [2.1 开发者账号注册](#2.1 开发者账号注册)
  * [2.2 设备注册](#2.2 设备注册)
  * [2.3 SDK获取](#2.3 SDK获取)
* [三、集成说明](#三、集成说明)
  * [3.1 硬件及系统环境](#3.1 硬件及系统环境)
  * [3.2 所需Android权限](#3.2 所需Android权限)
  * [3.3 配置文件](#3.3 配置文件)
    * [3.3.1 使用说明](#3.3.1 使用说明)
    * [3.3.2 主要文件说明](#3.3.2 主要文件说明)
  * [3.4 Android 项目gradle引入SDK相关aar](#3.4 Android 项目gradle引入SDK相关aar)
  * [3.5 SDK初始化](#3.5 SDK初始化)
    * [3.5.1 启动语音服务](#3.5.1 启动语音服务)
    * [3.5.2 注册返回结果监听](#3.5.2 注册返回结果监听)
  * [3.6 校验机制](#3.6 校验机制)
  * [3.7 基础识别结果处理](#3.7 基础识别结果处理)
    * [3.7.1 语音识别Asr处理](#3.7.1 语音识别Asr处理)
    * [3.7.2 语音识别技能nlp处理](#3.7.2 语音识别技能nlp处理)
    * [3.7.3 语音识别Event处理](#3.7.3 语音识别Event处理)
    * [3.7.4 语音识别Error处理](#3.7.4 语音识别Error处理)
* [四、SDK具体功能使用](#四、SDK具体功能使用)
  * [4.1 使用NlpConsumer来继续分发NLP](#4.1 使用NlpConsumer来继续分发NLP)
  * [4.2 使用RokidAiSkillEngine、RokidAiCloudApp 来处理Rokid 云端技能](#4.2 使用RokidAiSkillEngine、RokidAiCloudApp 来处理Rokid 云端技能)
  * [4.3 使用RokidAiSkillEngine、RokidAILocalSkillSdk 来处理Rokid 本地技能](#4.3 使用RokidAiSkillEngine、RokidAILocalSkillSdk 来处理Rokid 本地技能)
  * [4.4 使用算法处理过程中的相关pcm数据](#4.4 使用算法处理过程中的相关pcm数据)
  * [4.5 使用kenobi设备](#4.5 使用kenobi设备)
  * [4.6 关闭speech，只接收语音event、离线asr、pcm](#4.6 关闭speech，只接收语音event、离线asr、pcm)
  * [4.7 使用离线asr功能](#4.7 使用离线asr功能)
  * [4.8 使用有线mac地址来做校验](#4.8 使用有线mac地址来做校验)
  * [4.9 使用turenproc方式运行语音SDK](#4.9 使用turenproc方式运行语音SDK)
* [五、主要API参考](#五、主要API参考)
  * [5.1 IRokidAudioAiService.java](#5.1 IRokidAudioAiService.java)
  * [5.2 IRokidAudioAiListener.java](#5.2 IRokidAudioAiListener.java)
  * [5.3 ServiceConfig.java](#5.3 ServiceConfig.java)
  * [5.4 VoiceRecognize.Event](#5.4 VoiceRecognize.Event)
  * [5.5 RecordClientManager](#5.5 RecordClientManager)
  * [5.6 ClientSocketManager.IConnnectListener](#5.6 ClientSocketManager.IConnnectListener)
  * [5.7 PcmClientManager](#5.7 PcmClientManager)
  * [5.8 IReceiverPcmListener](#5.8 IReceiverPcmListener)
  * [5.9 错误码说明](#5.9 错误码说明)
* [六、其他说明](#六、其他说明)
  * [6.1 最新版本](#6.1 最新版本)
  * [6.2 参考demo地址（包含最新SDK）](#6.2 参考demo地址（包含最新SDK）)
  * [6.3 主要调用流程图](#6.3 主要调用流程图)



## 一、概述

RokidAiSdk 集合前端算法Turen相关功能，通过speech、云端来进行语音语义识别，并返回处理信息给三方开发者，附带Rokid的TTS功能，同时适用于Rokid外置语音Kenobi方案。
面向Android 软件开发工程师, 提供aar形式的SDK，简化接入流程，适应单独apk形式的集成，更方便用户接入Rokid AI语音技术。
RokidAiSdk 是语音技能全链路解决方案的核心引擎，用户接收到nlp数据，可以选择继续集成Rokid云端技能方案（RokidAiSkillEngine、RokidAiCloudApp）、本地技能方案（RokidLocalSkillSdk），打造一款完美的智能语音交互体验设备。


## 二、集成准备

### 2.1 开发者账号注册
Rokid 有自己的开发者账号、社区体系，使用Rokid的技术需要在[Rokid开放平台](https://developer.rokid.com/#/)的注册**开发者账号**，同时可以获取相关技术支持。

### 2.2 设备注册
Rokid 语音技术需要硬件设备做承接，相关的硬件信息同时也需要在Rokid开发者网站上进行产品报备。在[Rokid开放平台](https://developer.rokid.com/#/)的控制台的语音接入中，创建对应的产品，Rokid后台会自动生成`Key`、`Secret`、`deviceTypeId`，同时会为每个设备预生成10个测试用的`deviceId(sn)`和`seed`，这些信息会被组合起来做授权认证，保证语音SDK正常初始化。
  * **Rokid 开放平台介绍** ： https://developer.rokid.com/docs/
  * **产品创建及Sn导入** ： https://developer.rokid.com/docs/5-enableVoice/rokid-vsvy-sdk-docs/rookie-guide/rookie-guide-end.html

### 2.3 SDK获取
1、可以从[Rokid开放平台](https://developer.rokid.com/#/)开放平台获取，注册相应类型设备的同时，会生成相应的SDK，供开发者下载。参考[产品创建及Sn导入](https://developer.rokid.com/docs/5-enableVoice/rokid-vsvy-sdk-docs/rookie-guide/rookie-guide-end.html)。

2、从参考Demo程序获取最新SDK：https://github.com/Rokid/RokidAiSdkDemo （最新版本1.4.1）

## 三、集成说明

### 3.1 硬件及系统环境
1、Android方案：
- 带麦克风的Android 系统机器一台，系统Android 6.0及以上；
- 完全使用Android的AudioRecord录音，只支持单路或双路数据。

2、Kenobi方案：
- 支持USB并且可以插接外置kenobi卡板的Android 系统机器一台，系统Android 6.0及以上；
- Kenobi 单片机及相关USB线（Rokid提供）。

3、Android 系统定制方案：
- 带定制麦克风的Android 系统机器一台，系统Android 6.0及以上；
- 自定义pcm数据获取方案：
    * Rokid mic array方式，配合lothalproc使用；
    * 修改系统的audio源码，AudioRecord录音后独立解码成Rokid语音可支持的格式。
- 这种方式支持各种麦克风组合方案，多路数据。

4、附Rokid mic array方式Rokid语音支持的麦克风说明：[麦克风阵列音频采集程序集成说明文档](extra/麦克风阵列音频采集程序集成说明文档.md)

### 3.2 所需Android权限

```
    <!-- 网络 -->
    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
    <uses-permission android:name="android.permission.INTERNET" />
    <!-- 录音 -->
    <uses-permission android:name="android.permission.RECORD_AUDIO" />
    <uses-permission android:name="android.permission.MODIFY_AUDIO_SETTINGS" />
    <!-- 读取SD卡 -->
    <uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
    <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
    <uses-permission android:name="android.permission.MOUNT_UNMOUNT_FILESYSTEMS" />
    <!-- 设备网络状态 -->
    <uses-permission android:name="android.permission.READ_PHONE_STATE" />
    <uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
    <!-- Rokid技能权限 -->
    <uses-permission android:name="com.rokid.ai.skill.provider.READ_PROVIDER" />
    <uses-permission android:name="com.rokid.ai.skill.provider.WRITE_PROVIDER" />
```
  * **上述Android权限需要开发者在SDK接入的app入口页面事先实现权限获取，否则部分功能将无法正常运行 **

### 3.3 配置文件

#### 3.3.1 使用说明
Rokid语音SDK中包含众多语音算法，在整体流程的搭配中，我们对外提供基于默认配置上的一些可配置文件，方便不同设备实现不同的定制化语音功能。
* 配置文件路径：
```
  └── workdir_asr_cn
    ├── logging.conf
    ├── lothal_double.ini
    ├── lothal_double_modules.ini
    ├── lothal_single.ini
    ├── lothal_single_modules.ini
    ├── model
    │   └── emb
    │       ├── output_graph.bin
    │       └── symbol_table.txt
    ├── rasr.emb.double.ini
    ├── rasr.emb.single.ini
    └── words.ini
```
**上述配置需要开发者根据自己的硬件设备修改后放置到app 的 assert 目录中。**
**简单的配置会随示例给出，如果用户的麦克风进行了复杂的阵列设计，或者定制过激活词，建议走商务渠道让Rokid专业人员来进行个性化配置。**

#### 3.3.2 主要文件说明
##### 3.3.2.1 lothal_*.ini 

SDK集成配置文件，单通道/双通道，其他需要根据硬件麦克风状况进行修改，主要包括：

* 麦克风阵列配置:  对应文件中的`[mic_array]`部分，包含了对麦克风阵列参数的配置

```shell
# Mic阵列相关的配置
[mic_array]
# Mic通道数（包含AEC参考信号通道）
mic_num=8    
# 表示一次采样的bit位宽，支持可配置值 int16, int32, float32
audio_type=int32  
# Mic采样率
audio_rate=48000  
# Mic阵列类型：线麦(10)或环麦（11）
sl_micarray_shape=11

# Mic坐标参数，根据Mic阵列的尺寸和Mic所在的位置进行计算
# 阵列的坐标是量出直径（环麦）或最大长度（线麦） x（单位：m），然后根据环麦或线麦按随意选定的坐标
# 系计算出来。比如如下为正圆六环麦，均匀分布，坐标通过正余弦计算得出
pos0= -0.043000,  0.000000,  0.000000
pos1= -0.021500, -0.037239,  0.000000
pos2=  0.021500, -0.037239,  0.000000
pos3=  0.043000,  0.000000,  0.000000
pos4=  0.021500,  0.037239,  0.000000
pos5= -0.021500,  0.037239,  0.000000
pos6=  0,         0,         0
pos7=  0,         0,         0

# 增益缩放系数
mics_big=1,1,1,1,1,1,1,1

# 表明需要做AEC算法的通道
aec_mics=0,1,2,3,4,5  

# 表明参考通道的位置
ref_mics=6,7  

# Mic各通道的延迟，默认为0，一般不要修改，如果硬件确实存在延时，需要硬件工程师介入调试
mic_delay=0,0,0,0,0,0,0,0
```

* SDK内部算法模块配置: 对应文件中的`[modules]`部分，其中包含了指定模型配置文件`module.ini`的路径

```shell
# 语音处理流水线工作模块配置
[modules]

# 设置语音处理流水线工作模块，默认无需修改，当前包括：
# IN -  用于将输入音频转成float 32
# RDC - 去直流零票
# RS - 重采样，输出16K采样的音频
# NS - 噪音消除模块
# AEC - 回声消除
# ENGINE - 用于语音激活引擎，支持二次确认，CTC/CRNN
# VAD - 语音端点检测模块
# OPUS - 将PCM音频编码成opu
# OUT - 用于输出最终音频
sequence=IN,RDC,RS,AEC,ENGINE,VAD,OPUS,OUT   

# 指定针对上述各个模块的具体调优参数配置，稍后下一节会具体介绍
# modules.ini 相对路径 
config=lothal_single_modules.ini
```

* 激活词配置: 对应文件中的`[words]`部分，其中包含了指定唤醒词配置文件`words.ini`的路径。

```shell
# 激活词配置
[words]
# 激活词的拼音, 示例中使用的是若琪
words=ruoqi
# 指定激活词配置文件，会跟唤醒词模型同时输出，模型训练好后，无需修改，只需替换
config=words.ini
```

* 调试配置 - 对应文件中的`[debug]`部分，目前包含了日志打印级别的配置

```shell
# 调试配置
[debug]
# SDK输出日志级别 1 表示简略日志，0 表示大量调试日志
log.level=1
```
##### 3.3.2.2 lothal_single_modules.ini / lothal_double_modules.ini
* 模型配置文件，各种模型配置项，示例中对应了单麦/双麦。
* 需要指定模型配置文件`rasr.emb.*.ini`的路径配置，目前需要绝对路径，配置方式：

```shell
rasr_ini= rasr.emb.*.ini文件最终存放目录
# 格式为绝对路径：/sdcard/Android/data/{app packageName}/files/{your assert config path name}/rasr.emb.*.ini
# eg: /sdcard/Android/data/com.rokid.ai.sdkdemo/files/workdir_asr_cn/rasr.emb.single.ini
```

##### 3.3.2.3 rasr.emb.*.ini 
- 模型及算法优化配置文件，内部涉及到麦克风信息的地方需要开发者进行修改。

##### 3.3.2.4 words.ini
- 激活词配置文件，需要根据实际激活词信息配置即可，特殊自定义激活词需要跟Rokid商务联系进行定制。

##### 3.3.2.5 model
- 唤醒词模型文件夹，不要修改。

##### 3.3.2.6 logging.conf
- 日志配置文件，不要修改。

### 3.4 Android 项目gradle引入SDK相关aar
1、SDK提供aar文件说明：

* **basic.aar** : 提供语音基础工具类；
* **turenso.aar** : 核心语音处理工程，独立进程运行；
* **audioai.aar** : 语音处理结果接收及后续分发；
* **nlpconsumer.aar** : nlp技能控制相关，对接RokidAiSkillEngine或其他技能服务。

2、将SDK提供的 basic.aar, turenso.aar, audioai.aar, nlpconsumer.aar 放到app工程的libs目录下；

3、在app工程的build.gradle文件中引入上述aar；

```groovy
defaultConfig {
    // ... 保证app运行时使用armeabi-v7a 中的so，RokidAiSdk目前没有提供64位的so
    ndk {
        abiFilters "armeabi-v7a"
    }
}
// 设置依赖查找目录，其中 basic.aar, turenso.aar, audioai.aar, nlpconsumer.aar 放到app工程的libs目录
repositories{
    flatDir{
        dirs 'libs'
    }
}
// gradle merge 操作时，忽略掉多出的部分so文件
packagingOptions {
    pickFirst 'lib/armeabi-v7a/librlog.so'
    pickFirst 'lib/armeabi-v7a/libcaps.so'
}
// 引入依赖, gson、appcompat-v7需要用户引入，版本可以自定
dependencies {
    implementation fileTree(include: ['*.jar'], dir: 'libs')
    implementation (name:'basic-1.4.1', ext:'aar')
    implementation (name:'turenso-1.4.1', ext:'aar')
    implementation (name:'nlpconsumer-1.4.1', ext:'aar')
    implementation (name:'audioai-1.4.1', ext:'aar')
    implementation "com.google.code.gson:gson:2.8.5"
    implementation 'com.android.support:appcompat-v7:27.1.1'
    // ...
}
```

4、混淆配置，如果用户app需要混淆的话，请不要混淆rokid语音SDK相关代码

```shell
# 保持 native 方法不被混淆
-keepclasseswithmembernames class * { 
   native <methods>;
}
-keep class com.rokid.** { *; }
```

### 3.5 SDK初始化

#### 3.5.1 启动语音服务
1、开发者需要创建一个符合自己需求的ServerConfig 实例；

```java
private ServerConfig getServiceConfig() {

    ServerConfig config = null;
    // Android 的 AudioRecord 录音最多只支持2个麦克风
    // 使用一个麦克风配置
    // "workdir_asr_cn": 算法配置文件在assets目录中的位置
    // "lothal_single.ini": 算法库启动配置文件名
    // useOtherAudio: 是否使用用户自己的audio数据模块, false 代表使用Rokid 的Kenobi方案。
    config = new ServerConfig("workdir_asr_cn", "lothal_single.ini", true);
    // 使用两个个麦克风配置
    // config = new ServerConfig("workdir_asr_cn", "lothal_double.ini", true);

    // 设置log日志级别
    config.setLogConfig(Logger.LEVEL_D, true, true);

    // key: Rokid开放平台注册时生成的Key
    String key = "2FA1968AE2B14942BA56D3B874A9C5B0";
    // secret: Rokid开放平台注册时生成的Secret
    String secret = "3540CBB498DB4D348E8AD784B21DD7D1";
    // deviceTypeId: Rokid开放平台注册时生成的DeviceTypeId
    String deviceTypeId = "0ABA0AA4F71949C4A3FB0418BF025113";
    // deviceId: 设备SN号，由6~15位的字母和数字组成，不能含有空格和特殊符号
    String deviceId = "0502031835000134";
    // seed: 设备seed号，跟rokid设备账号绑定时使用
    String seed = "gQ5H5k0936G71077KZ1Xzy7Y7A71z9";

    config.setKey(key).setSecret(secret).setDeviceTypeId(deviceTypeId).setDeviceId(deviceId)
            .setSeed(seed);
    // 使用语音处理软件处理NLP技能
    config.setUseNlpConsumer(true);

    return config;
}
```
**上述代码只使用基础的语音功能，其他特殊的语音功能设置请参考 [SDK具体功能使用](#四、SDK具体功能使用)**

2、开发者需要startService的方式来创建AudioAiService；
    **注意：在启动语音Service之前，Android 6.0以上系统，开发者需要自行申请[所需Android权限](#3.2 所需Android权限)并且用户点击通过**。

```java
// 开始启动AudioAiService 
// SDK和app在独立进程方式
Intent mServiceIntent = AudioAiConfig.getIndependentIntent(this);
// SDK和app在相同进程方式
// Intent mServiceIntent = AudioAiConfig.getAttachmentIntent(this);
mServiceIntent.putExtra(AudioAiConfig.PARAM_SERVICE_START_CONFIG, getServiceConfig());
startService(mServiceIntent);

// 在用户需要彻底结束语音AudioAiService时，需要调用stop
// stopService(mServiceIntent);
```

3、开发者启动AudioAiService 服务后，需要再使用binder方式来绑定服务，以便可以和服务进行交互；

```java
// 绑定AudioAiService 
private IRokidAudioAiService mAudioAiService;
private ServiceConnection mAiServiceConnection;

private void createConnection() {
    if (mAiServiceConnection != null) {
        return;
    }
    mAiServiceConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            Logger.d(TAG, "the onServiceConenct is called");
            if (service != null) {
                Logger.d(TAG, "onServiceConenct asInterface ");
                mAudioAiService = IRokidAudioAiService.Stub.asInterface(service);
                //try {
                //    service.linkToDeath(mDeathRecipient, 0);
                //    Logger.d(TAG, "onServiceConenct registAudioAiListener ");
                //    mAudioAiService.registAudioAiListener(mAudioAiListener);
                //} catch (RemoteException e) {
                //    e.printStackTrace();
                //}
            }
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            mAudioAiService = null;
        }
    };
}
// 需要在用户startService 调用之后再进行绑定，最好两个调用之间有些微弱的时间间隔
bindService(mServiceIntent, mAiServiceConnection, BIND_AUTO_CREATE);

// 在用户需要彻底结束语音AudioAiService时，需要先解除绑定再结束
// unbindService(mAiServiceConnection);
```

#### 3.5.2 注册返回结果监听
1、IRokidAudioAiService服务绑定后，需要立即注册语音处理结果监听；

```java
mAiServiceConnection = new ServiceConnection() {
    @Override
    public void onServiceConnected(ComponentName name, IBinder service) {
        Logger.d(TAG, "the onServiceConenct is called");
        if (service != null) {
            Logger.d(TAG, "onServiceConenct asInterface ");
            mAudioAiService = IRokidAudioAiService.Stub.asInterface(service);
            try {
            //    service.linkToDeath(mDeathRecipient, 0);
                Logger.d(TAG, "onServiceConenct registAudioAiListener ");
                mAudioAiService.registAudioAiListener(mAudioAiListener);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void onServiceDisconnected(ComponentName name) {
        mAudioAiService = null;
    }
};
```

2、创建AudioAiListener 实例，主要用来监听语音SDK的返回结果（event、asr、nlp、error）；

```java
private IRokidAudioAiListener mAudioAiListener = new IRokidAudioAiListener.Stub() {

    private String mListenerKey = FileUtil.getStringID();

    @Override
    public void onIntermediateSlice(int id, String asr, boolean isLocal) throws RemoteException {
        Logger.d(TAG, "onIntermediateSlice(): " + (isLocal ? "LOCAL" : "NET") + " asr = " + asr);
    }

    @Override
    public void onIntermediateEntire(int id, String asr, boolean isLocal) throws RemoteException {
        Logger.d(TAG, "onIntermediateEntire(): " + (isLocal ? "LOCAL" : "NET") + " asr = " + asr);
    }

    @Override
    public void onCompleteNlp(int id, String nlp, String action, boolean isLocal) throws RemoteException {
        Logger.d(TAG, "onCompleteNlp(): " + (isLocal ? "LOCAL" : "NET") + " nlp = " + nlp + " action = " + action + "\n\r");
    }

    @Override
    public void onVoiceEvent(int id, int event, float sl, float energy, String extra) throws RemoteException {
        Logger.d(TAG, "onVoiceEvent(): event = " + event + ", sl = " + sl + ", energy = " + energy + ", extra = " + extra + "\n\r");
    }

    @Override
    public void onRecognizeError(int id, int errorCode) throws RemoteException {
        Logger.d(TAG, "onRecognizeError(): errorCode = " + errorCode + "\n\r");
    }

    @Override
    public void onServerSocketCreate(String ip, int port) throws RemoteException {
        Logger.d(TAG,"onServerSocketCreate(): ip = " + ip + ", port = " + port);
    }

    @Override
    public void onPcmServerPrepared() throws RemoteException {
        Logger.d(TAG,"onPcmServerPrepared(): called");
    }

    @Override
    public String getKey() throws RemoteException {
        return mListenerKey;
    }

    @Override
    public void controlNlpAppExit() throws RemoteException {
        Logger.d(TAG,"controlNlpAppExit(): called");
    }

    @Override
    public boolean interceptCloudNlpControl(int id, String nlp, String action) throws RemoteException {
        Logger.d(TAG,"interceptCloudNlpControl(): called");
        return false;
    }

    @Override
    public void onVerifyFailed(String deviceTypeId, String deviceId, String seed, String mac) throws RemoteException {
        Logger.d(TAG,"onVerifyFailed(): deviceTypeId = " + deviceTypeId +
                "，deviceId = " + deviceId + "，seed = " + seed + "，mac = " + mac);
    }
};
```

3、如果使用SDK和app在各自独立进程方式，推荐做一下服务绑定失效监听，这样失效后可以立即再次绑定(非必要)；

```java
private IBinder.DeathRecipient mDeathRecipient = new IBinder.DeathRecipient() {
    @Override
    public void binderDied() {
        try {
            Logger.d(TAG, "DeathRecipient(): binderDied start");
            startService(mServiceIntent);
            bindService(mServiceIntent, mAiServiceConnection, BIND_AUTO_CREATE);
            Logger.d(TAG, "DeathRecipient(): binderDied end");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
};

mAiServiceConnection = new ServiceConnection() {
    @Override
    public void onServiceConnected(ComponentName name, IBinder service) {
        Logger.d(TAG, "the onServiceConenct is called");
        if (service != null) {
            Logger.d(TAG, "onServiceConenct asInterface ");
            mAudioAiService = IRokidAudioAiService.Stub.asInterface(service);
            try {
                service.linkToDeath(mDeathRecipient, 0);
                Logger.d(TAG, "onServiceConenct registAudioAiListener ");
                mAudioAiService.registAudioAiListener(mAudioAiListener);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void onServiceDisconnected(ComponentName name) {
        mAudioAiService = null;
    }
};

// 在用户需要彻底结束语音AudioAiService时，需要先去除失效监听，然后再解除绑定，结束Service
// try {
//     if (mAudioAiService != null) {
//         mAudioAiService.asBinder().unlinkToDeath(mDeathRecipient, 0);
//         mAudioAiService = null;
//     }
// } catch (Throwable e) {
// }
```

### 3.6 校验机制
Rokid语音SDK内部附带校验机制，需要开发者在启动服务时提供正确的设备启动信息：
* key ：Rokid开放平台注册时生成的Key
* secret ：Rokid开放平台注册时生成的Secret
* deviceTypeId ：Rokid开放平台注册时生成的DeviceTypeId
* deviceId ：设备SN号，由6~15位的字母和数字组成，不能含有空格和特殊符号
* seed ：设备seed号，跟rokid设备账号绑定时使用
*  macAddress ：设备网络的mac 地址，每一对deviceId、seed只能对应一个设备，即一个macAddress。请开发者谨慎使用十个免费的测试deviceId和seed，如果想要大量商用的，请联系Rokid商务进行正式的SN、Seed信息导入。

在IRokidAudioAiService的回调函数中，会接收到校验失败返回信息
```java
/**
 * 校验失败回调
 * 
 * @param deviceTypeId 设备deviceTypeId
 * @param deviceId 设备deviceId
 * @param seed 设备seed
 * @param mac 设备真实mac
 * @throws RemoteException
 */
@Override
public void onVerifyFailed(String deviceTypeId, String deviceId, String seed, String mac) throws RemoteException {
    Logger.d(TAG,"onVerifyFailed(): deviceTypeId = " + deviceTypeId +
            "，deviceId = " + deviceId + "，seed = " + seed + "，mac = " + mac);
}
```

### 3.7 基础识别结果处理

#### 3.7.1 语音识别Asr处理
在IRokidAudioAiService的回调函数中，会接收到相关asr识别返回信息

* 返回语音识别中间结果片段

```java
/**
 * 返回语音识别中间结果片段
 *
 * @param id 会话ID：一次激活开始到识别结束，nlp或error返回过程中的统一识别ID
 * @param asr asr String 数据
 * @param isLocal 是否是本地离线识别 true：离线识别，false：有网络在线识别
 * @throws RemoteException
 */
@Override
public void onIntermediateSlice(int id, String asr, boolean isLocal) throws RemoteException {
    Logger.d(TAG, "onIntermediateSlice(): " + (isLocal ? "LOCAL" : "NET") + " asr = " + asr);
    }

}
```

* 返回语音识别最终结果完整的数据

```java
/**
 * 返回语音识别最终结果完整的数据
 *
 * @param id 会话ID：一次激活开始到识别结束，nlp或error返回过程中的统一识别ID
 * @param asr asr String 数据
 * @param isLocal 是否是本地离线识别 true：离线识别，false：有网络在线识别
 * @throws RemoteException
 */
@Override
public void onIntermediateEntire(int id, String asr, boolean isLocal) throws RemoteException {
    Logger.d(TAG, "onIntermediateEntire(): " + (isLocal ? "LOCAL" : "NET") + " asr = " + asr);
    }
}
```

#### 3.7.2 语音识别技能nlp处理
在IRokidAudioAiService的回调函数中，会接收到语音识别技能nlp处理返回信息
```java
/**
 * 返回语音识别技能结果nlp、action
 *
 * @param id 会话ID：一次激活开始到识别结束，nlp或error返回过程中的统一识别ID
 * @param nlp 技能结果nlp
 * @param action 技能结果action，Rokid云技能使用
 * @param isLocal 是否是本地离线识别 true：离线识别，false：有网络在线识别
 * @throws RemoteException
 */
@Override
public void onCompleteNlp(int id, String nlp, String action, boolean isLocal) throws RemoteException {
    Logger.d(TAG, "onCompleteNlp(): " + (isLocal ? "LOCAL" : "NET") + " nlp = " + nlp + " action = " + action + "\n\r");

}
```

#### 3.7.3 语音识别Event处理
在IRokidAudioAiService的回调函数中，会接收到语音识别Event处理返回信息
```java
/**
 * 返回语音唤醒事件
 *
 * @param id 会话ID：一次激活开始到识别结束，nlp或error返回过程中的统一识别ID
 * @param event 事件号 语音事件类型VoiceRecognize.Event的ordinal()值
 * @param sl  当前唤醒角度(0到360度之间)
 * @param energy 当前说话能量值(0到1之间的浮点数)
 * @param extra 其他事件的附加信息
 * @throws RemoteException
 */
@Override
public void onVoiceEvent(int id, int event, float sl, float energy, String extra) throws RemoteException {
    Logger.d(TAG, "onVoiceEvent(): event = " + event + ", sl = " + sl + ", energy = " + energy + ", extra = " + extra + "\n\r");
}
```
事件说明：VoiceRecognize.Event
* EVENT_VOICE_LOCAL_WAKE：本地激活成功
* EVENT_VOICE_LOCAL_SLEEP：本地休眠事件
* EVENT_VOICE_COMING：本地激活语音数据到来
* EVENT_VOICE_ACCEPT：激活词云端二次确认成功
* EVENT_VOICE_REJECT：激活词云端二次确认失败
* EVENT_VOICE_CANCEL：激活取消
* EVENT_VOICE_SYS_EXIT：本次激活系统退出
* EVENT_VOICE_OUTSERVER_READY：Turen系统重启，重新连接

#### 3.7.4 语音识别Error处理
在IRokidAudioAiService的回调函数中，会接收到语音识别Error处理返回信息
```java
/**
 * 返回语音识别出错信息
 *
 * @param id 会话ID：一次激活开始到识别结束，nlp或error返回过程中的统一识别ID
 * @param errorCode 错误码 VoiceRecognize.ExceptionCode的ordinal()值
 * @throws RemoteException
 */
@Override
public void onRecognizeError(int id, int errorCode) throws RemoteException {
    Logger.d(TAG, "onRecognizeError(): errorCode = " + errorCode + "\n\r");
}
```
错误码说明：https://developer.rokid.com/docs/5-enableVoice/rokid-vsvy-sdk-docs/common/err_code.html

## 四、SDK具体功能使用
### 4.1 使用NlpConsumer来继续分发NLP
如果用户需要使用Rokid的nlp、技能相关的后续功能链路，需要打开NlpConsumer来继续分发NLP功能。
```java
// 在ServerConfig中打开NlpConsumer开关
private ServerConfig getServiceConfig(int status) {

    ServerConfig config = null;
    // ...
    // 使用语音处理软件处理NLP技能 默认为false
    config.setUseNlpConsumer(true);
    // ...
    return config;
}
```

### 4.2 使用RokidAiSkillEngine、RokidAiCloudApp 来处理Rokid 云端技能
1、RokidAiSkillEngine.apk：需要安装SDK包内附带的RokidAiSkillEngine，主要负责技能的分发、技能与语音SDK之间的交互，对云端技能、本地技能的控制。

2、RokidAiCloudApp.apk：需要安装SDK包内附带的RokidAiCloudApp，主要云端技能的处理，一些较小技能需求，推荐使用Rokid云技能方案来解决，快速稳定。

3、技能开发推荐参考：https://developer.rokid.com/docs/2-RokidDocument/1-SkillsKit/getting-started/creat.html

### 4.3 使用RokidAiSkillEngine、RokidAILocalSkillSdk 来处理Rokid 本地技能
1、RokidAiSkillEngine.apk：需要安装SDK包内附带的RokidAiSkillEngine，主要负责技能的分发、技能与语音SDK之间的交互，对云端技能、本地技能的控制。

2、RokidAILocalSkillSdk.aar：需要在开发者的本地技能apk中引入使用，Rokid 语音SDK 本地技能快速开发工具，方便开发配合Rokid语音SDK一起使用的本地技能。

3、本地技能开发及SDK使用文档请参考：https://developer.rokid.com/docs/5-enableVoice/rokid-vsvy-sdk-docs/LocalSkillSdk/LocalSkillSdk.html

### 4.4 使用算法处理过程中的相关pcm数据：必须通过校验
1、算法配置修改；
```shell
# 在*_modules.ini中, 每个算法步骤的配置模块，都可以对外吐出算法处理的pcm数据

# 注：每一个步骤处理露出的pcm数据格式都是不同的
# 注：不同步骤的数据格式请咨询Rokid商务，因对外提供pcm会影响Rokid语音SDK对硬件设备资源的占用，需要Rokid专用人员对相关硬件设备能否使用作出评估。

# eg：将[ENGINE]步骤处理的数据映射到30003端口
# ...
[ENGINE]
dump.uri=socket:30003
# ...

# eg：将[AEC]步骤处理的数据映射到30010端口
# ...
[AEC]
dump.uri=socket:30010
# ...
```

2、在算法配置的同时，需要java层用socket来主动获取，我们的aar中已经提供了获取pcm数据的工具类；
```java
private PcmClientManager mPcmSocketManager;

@Override
protected void onCreate(Bundle savedInstanceState) {
    // ...
    mPcmSocketManager = new PcmClientManager();
}

private IRokidAudioAiListener mAudioAiListener = new IRokidAudioAiListener.Stub() {
    // ......

    @Override
    public void onPcmServerPrepared() throws RemoteException {
        Logger.d(TAG,"onPcmServerPrepared(): called");
        if (mPcmSocketManager != null) {
        // 端口为用户自己在配置文件上定义的 dump.uri=socket:30003
            mPcmSocketManager.startSocket(null, mPcmReceiver, 30003);
        }
    }
};

private IReceiverPcmListener mPcmReceiver = new IReceiverPcmListener() {
    @Override
    public void onPcmReceive(int length, byte[] data) {
        Logger.d(TAG, "onPcmReceive(): len = " + length + "\n\r");
        // showPcmData(length, data);
    }
};

@Override
protected void onDestroy() {
    // ...
    mPcmSocketManager.onDestroy();
    mPcmSocketManager = null;

    super.onDestroy();
}
```

### 4.5 使用kenobi设备
如果用户要配合Rokid kenobi设备来一起使用SDK。
```java
// 在ServerConfig中关闭useOtherAudio 
// useOtherAudio 是否使用用户自己的audio数据模块, false 代表使用kenobi设备
private ServerConfig getServiceConfig() {

    ServerConfig config = null;
    config = new ServerConfig("workdir_asr_cn","lothal_single.ini", false);

    // ...
    return config;
}
```

### 4.6 关闭speech，只接收语音event、离线asr、pcm
如果用户不需要使用Rokid的speech功能，只使用前端算法的部分功能，可以通过开关来关闭speech 方式启动。
```java
// 在ServerConfig中关闭speech功能开关
private ServerConfig getServiceConfig() {

    ServerConfig config = null;
    // ...
    // 是否打开speech 默认为true
    config.setUseSpeech(false);
    // ...
    return config;
}
```

### 4.7 使用离线asr功能
如果用户需要使用Rokid的离线asr功能，需要做两部操作：

1、**通过Rokid 商务来定制离线asr指令，并使用Rokid提供的专业配置文件(包含离线词表配置)**；

2、需要打开离线asr开关，这样Rokid语音会在设备处于离线环境时启动离线asr功能；

```java
// 在ServerConfig中打开NlpConsumer开关
private ServerConfig getServiceConfig() {

    ServerConfig config = null;
    // ...
    // 使用离线asr开关，默认为false
    config.setUseOffLine(true);
    // ...
    return config;
}
```

### 4.8 使用有线mac地址来做校验
如果用户需要使用有线mac地址来做设备校验的话，需要开启有线校验开关。
```java
// 在ServerConfig中开启有线校验开关
private ServerConfig getServiceConfig() {

    ServerConfig config = null;
    // ...
    // 是否开启有线校验 默认为false
    config.setNotUseWifi(true);
    // ...
    return config;
}
```

### 4.9 使用turenproc方式运行语音SDK
Rokid 算法集成库可以使用系统独立进程方式运行，在这种模式下，RokidAiSdk可以用来只作为Event、asr、nlp、error的接收方。

1、参考系统全链路方式初步集成算法so、将turenproc放到init rc中开机启动，同时准备与设备对应的pcm读取工具，mic_array.so。参考：https://developer.rokid.com/docs/5-enableVoice/rokid-vsvy-sdk-docs/fullLink/fulllink.html；

2、可以在gradle 依赖中去掉turenso.aar相关的依赖；

3、在ServerConfig中打开使用turenproc的开关；

```java
// 在ServerConfig中打开使用turenproc功能开关
private ServerConfig getServiceConfig() {

    ServerConfig config = null;
    // ...
    // 是否打开turenproc开关 默认为false
    config.setUseTurenProc(true);
    // ...
    return config;
}
```

## 五、主要API参考
### 5.1 IRokidAudioAiService.java
**ASR 主Service的binder接口**

| 返回值 | 方法和说明 |
| ------ | ------------------------------------------------------------ |
| `void` | `playTtsVoice(java.lang.String text)`用tts服务播放text语音   |
| `void` | `setUserMediaPlaying(boolean userMediaPlaying)`通知当前设备是否有用户媒体流在播放 |
| `boolean` | `srartAudioAiServer(ServerConfig config, IRokidAudioAiListener listener)`根据配置信息启动服务, 并注册Asr语音服务处理结果的监听（若当前服务已启动，则不会重新启动）true：表示监听添加成功，false：表示监听添加失败，config中的Key、Secret、DeviceTypeId三个值与服务启动时的config中的三个值不相等 |
| `void` | `registAudioAiListener(IRokidAudioAiListener listener)`注册Asr语音服务处理结果的监听 |
| `void` | `unRegistAudioAiListener(IRokidAudioAiListener listener)`注销Asr语音服务处理结果的监听 |
| `void` | `setPickUp(boolean open)` 在单独的激活模块中，主动开启拾音和关闭拾音 true: 开启拾音, false: 结束拾音 |
| `int` | `control(String action)` 发送控制命令：action "ACTION_SET_STATE_AWAKE" ：开始拾音；"ACTION_SET_STATE_SLEEP" ：设置为接受激活状态；"ACTION_OPEN_MIC" ：打开麦克风（打开才能激活、拾音）；"ACTION_CLOSE_MIC" ：关闭麦克风（无法激活、拾音） |
| `int` | `addVtWord(String vtWordType, String word, String pinyin)` 添加自定义激活词 vtWordType : 激活词类型 "AWAKE"、"SLEEP"、"HOTWORD"、"OTHER"；word : 激活词中文；pinyin : 激活词拼音 |
| `int` | `removeVtWord(String content)` 去除激活词 |
| `List<String>` | `getVtWords()` 获取当前所有自定义激活词 |
| `int` | `updateStack(String currAppId, String prevAppId)` 更新turen Stack 技能栈 currAppId : 当前的AppId；prevAppId : 上一个AppId |
| `int` | `setSkillOption(String skillOption)` 设置SkillOption |

### 5.2 IRokidAudioAiListener.java
**监听AudioAiService服务对语音的处理结果**

| 返回值 | 方法和说明 |
| ------ | ------------------------------------------------------------ |
| void   | onIntermediateSlice(int id, String asr, boolean isLocal) 返回语音识别中间结果片段 (id: 本次激活会话id)   |
| void   | onIntermediateEntire(int id, String asr, boolean isLocal)  返回语音识别中间结果完整的数据(id: 本次激活会话id) |
| void   | onCompleteNlp(int id, String nlp, String action, boolean isLocal) 返回最终语音识别结果（id: 本次激活会话id，nlp：自然语义解析结果， action：云端skill结果） |
| void   | onVoiceEvent(int id, int event, float sl, float energy, String extra)  返回语音唤醒事件（id: 本次激活会话id，event: 语音事件类型VoiceRecognize.Event的ordinal()值（见**VoiceRecognize.Event  enum 类型说明**）， sl：当前唤醒角度(0到360度之间)， energy：当前说话能量值(0到1之间的浮点数)） |
| void   | onRecognizeError(int id, int errorCode)  返回语音识别出错信息（id: 本次激活会话id，errorCode：错误码，**见错误码说明**） |
| void   | onServerSocketCreate(String ip, int port) 接收pcm数据的socket启动成功时的回调 （ip：socket的ip地址， post：socket的端口） |
| void   | onPcmServerPrepared()  发送算法处理过后的pcm数据的服务已经准备好  |
| String   | getKey()  返回当前IRokidAudioAiListener 唯一标志 （不可为null或""，否则IRokidAudioAiListener将会注册失败）  |
| void   | controlNlpAppExit()  处理NLP中的退出所有app指令  |
| boolean   | interceptCloudNlpControl(int id, String nlp, String action)  对NlpConsumer云端处理NLP进行拦截（id：会话ID，nlp：自然语义解析结果， action：云端skill结果）  |
| void   | onVerifyFailed(String deviceTypeId, String deviceId, String seed, String mac)  设备校验失败回调（deviceTypeId：设备类型ID，deviceId：设备sn， seed：账号值， mac：mac地址） |

### 5.3 ServiceConfig.java 
**启动参数配置类**

| 返回值             | 方法和说明  |
| ------------------ | ------------------------------------------------------------ |
| `java.lang.String` | `getAssetsConfigPath()`获取Assets目录中算法库配置文件路径    |
| `java.lang.String` | `getConfigFileName()`获取初始化turen配置文件名               |
| `java.lang.String` | `getDeviceId()`获取设备的DeviceId， sn号                     |
| `java.lang.String` | `getDeviceTypeId()`获取当前DeviceTypeId                      |
| `java.lang.String` | `getKey()`获取当前Key                                        |
| `int`              | `getLogLevel()`返回log等级                                   |
| `java.lang.String` | `getRealConfigPath()`获取算法库配置文件真实路径              |
| `java.lang.String` | `getSecret()`获取当前Secret                                  |
| `java.lang.String` | `getSpeechConfig()`                                          |
| `boolean`          | `isShowDecoderSoLog()`返回decode so日志是否展示              |
| `boolean`          | `isShowTurenLog()`查看Turen Log的展示                        |
| `boolean`          | `isTestWays()`获取是否开启测试模式                           |
| `boolean`          | `isUseNlp()`查询是否输出NLP功能                              |
| `boolean`          | `isUseNlpConsumer()`查询是否使用NLP云端、本地技能语音处理功能 |
| `boolean`          | `isUseOtherAudio()`获取当前是否使用用户自己的audio数据模块   |
| `boolean`          | `isUsePcm()`查询是否输出PCM功能                              |
| `boolean`          | `isUseTurenProc()`查询是否turenproc命令行工具启动Turen方式   |
| `ServerConfig`     | `setAssetsConfigPath(java.lang.String path)`设置Assets目录中算法库配置文件路径 |
| `ServerConfig`     | `setConfigFileName(java.lang.String fileName)`设置初始化turen配置文件名 |
| `ServerConfig`     | `setDeviceId(java.lang.String mDeviceId)`设置设备的DeviceId， sn号 |
| `ServerConfig`     | `setDeviceTypeId(java.lang.String mDeviceTypeId)`设置开放平台注册时生成的Type ID |
| `ServerConfig`     | `setKey(java.lang.String key)`设置开放平台注册时生成的KEY    |
| `ServerConfig`     | `setLogConfig(int logLevel, boolean showTurenLog, boolean showDecoderSoLog)`设置log等级 |
| `ServerConfig`     | `setRealConfigPath(java.lang.String path)`设置算法库配置文件真实路径 |
| `ServerConfig`     | `setSecret(java.lang.String secret)`设置开放平台注册时生成的Secret |
| `ServerConfig`     | `setShowDecoderSoLog(boolean show)`设置decode so日志是否展示 |
| `ServerConfig`     | `setShowTurenLog(boolean show)`设置Turen Log的展示           |
| `ServerConfig`     | `setTestWays(boolean testWays)`设置是否开启测试模式，识别服务器会有区别 |
| `ServerConfig`     | `setUseMacArray(boolean useMacArray)`设置是否使用mic_array方式获取PCM数据 |
| `ServerConfig`     | `setUseNlpConsumer(boolean useNlpConsumer)`设置是否使用NLP云端、本地技能语音处理功能 |
| `ServerConfig`     | `setUseOtherAudio(boolean useOtherAudio)`设置是否使用用户自己的audio数据模块（默认使用SDK的BSP Audio数据模块） |
| `ServerConfig`     | `setNotUseWifi(boolean notUseWifi)`是否不使用WiFi，使用有线网卡，mac地址用 |
| `ServerConfig`     | `setSpeechBranch(String speechBranch)`设置Speech 请求分支 |
| `ServerConfig`     | `setSpeechPort(int speechPort)`设置Speech 请求端口 |
| `ServerConfig`     | `setSpeechHost(String speechHost)`设置Speech 请求host |

### 5.4 VoiceRecognize.Event  
**Event Enum 类型说明**

| 类型 | 语音唤醒事件枚举定义 |
| ---- | ------------------------------------------------------------ |
| `EVENT_VOICE_COMING` | 激活即将开始（sl 存在值，energy值为0） |
| `EVENT_VOICE_LOCAL_WAKE` | 本地已经激活（sl 存在值，energy值为0） |
| `EVENT_VOICE_START` |  开始上传VAD（sl 值为0，energy存在值 ）  |
| `EVENT_VOICE_NONE`  | 二次确认结果为空，只出于已经在激活状态下，直接说语音命令 |
| `EVENT_VOICE_ACCEPT`  | 云端二次确认通过 |
| `EVENT_VOICE_REJECT`  | 云端二次确认不通过 |
| `EVENT_VOICE_CANCEL`  | 取消当前上传VAD |
| `EVENT_VOICE_LOCAL_SLEEP` |  通过休眠词从激活状态进入休眠状态 |

### 5.5 RecordClientManager 
**录音Pcm的Client Socket, 用来向语音SDK发送录音录到的pcm数据**

| 类型 | 描述 |
| ---------------------------- | ----------------------------------------------------------- |
| `boolean` | `isUseQueue()`查看是否使用队列缓存数据发送 |
| `void` | `onDestroy()` |
| `void` | `sendRecordData(byte[] data)`发送录音数据 |
| `void` | `setUseQueue(boolean useQueue)`设置是否使用队列缓存数据发送 |
| `void` | `startSocket(java.lang.String ip, int port, ClientSocketManager.IConnnectListener listener)` 启动一个socket长连接|

### 5.5 IRecordPcmReceiver 
**录音pcm数据获取后处理监听回调**

| 类型 | 描述 |
| ---------------------------- | -------------- |
| `void` | `onPcmReceive(int length, byte[] data)`录音pcm数据获取后处理 |

### 5.6 ClientSocketManager.IConnnectListener 
**Socket连接监听**

| 类型 | 描述 |
| ---------------------------- | -------------- |
| `void` | `onConnectFailed(ClientSocketManager socketManager)`连接失败 |
| `void` | `onConnectSuccess(ClientSocketManager socketManager)`连接成功 |

### 5.7 PcmClientManager 
**算法Pcm工具类的Client Socket，用来获取算法各步骤的pcm数据**

| 类型 | 描述 |
| ---------------------------- | --------------------- |
| `boolean` | `isUseQueue()`查看是否使用队列缓存数据发送 |
| `void` | `onDestroy()` |
| `void` | `sendRecordData(byte[] data)`发送录音数据 |
| `void` | `setUseQueue(boolean useQueue)`设置是否使用队列缓存数据发送 |
| `void` | `startSocket(ClientSocketManager.IConnnectListener listener, IReceiverPcmListener pcmReceiver)` 启动一个socket长连接 |

### 5.8 IReceiverPcmListener 
**算法pcm数据获取后处理监听回调**

| 类型 | 描述 |
| ---------------------------- | -------------------- |
| `void` | `onPcmReceive(int length, byte[] data)`算法pcm数据获取后处理|

### 5.9 错误码说明

| 值 | 错误描述 |
| ---|---|
| 0 | 成功 |
| 3 | 与服务器连接数量过多 |
| 4 | 服务器资源不足 |
| 5 | 服务器忙 |
| 6 | 服务器内部错误 |
| 7 | 语音识别超时 |
| 101 | 无法连接到服务器 |
| 103 | 语音请求服务器超时未响应 |
| 104 | 未知错误 |


## 六、其他说明

### 6.1 最新版本

SDK 版本：（aar）1.4.1 
  
* audioai-1.4.1.aar
* basic-1.4.1.aar
* nlpconsumer-1.4.1.aar
* turenso-1.4.1.aar

### 6.2 参考demo地址（包含最新SDK）

github：https://github.com/Rokid/RokidAiSdkDemo

### 6.3 主要调用流程图

   ![AudioAiSdk 时序](image/AudioAiSdk 时序.png)