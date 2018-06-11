## 一、概述

### Rokid 全链路通用方案

Rokid 全链路系统集成是指选择 Rokid 全链路 SDK 下载后,通过 Android 源码方式集成SDK,集成 SDK 成功后,可以获取Rokid 前端语音激活/降噪以及 Rokid 语音识别服务和语音合成服务的相关能力.
 - 前端语音能力
  - 将麦克风阵列中的语音数据转换成对应的前端语音激活/休眠等事件. Rokid 提供的前端语音能力可为开发者提供语音 AEC 降噪处理/回声消除处理等
 - 语音识别服务(ASR)
  - 语音识别可以通过开发者提供的原始语音数据/经过算法处理过的语音数据识别成对应的自然语言(ASR),以及对应的自然语言处理(NLP)信息
 - 语音合成服务(TTS)
  - Rokid语音合成服务可以根据开发者提供的文字合成高质量的音频。



## 二、SDK生成产物目录结构

### config

*  speech_config.json ---- sdk需要与厂商相关的key/secret等信息,在语音识别以及tts合成时,需要用这些配置信息进行认证,会作为参数传递进SDK,可以点击[语音接入](https://developer.rokid.com/voice/#/product/create/list)处创建产品，在下载 SDk 处查看key/secret。
*  workdir_asr_cn  ----前端mic硬件配置以及激活模型文件目录,其中```ctc.xxx.cfg``` 文件为配置激活词信息以及,```device.xxx.cfg``` 文件为麦克风阵列相关配置文件.```workdir_asr_cn```目录中的配置文件一旦生成,不允许私自修改内容及文件名.

### example

 - 源码示例程序1(android 源码编译集成前端 + speech 的示例程序 ,目录:SpeechExecutor)

### executable

* turenproc   ---- 前端拾音服务 链接mic数据读取以及语音识别服务(speech)模块的可执行进程

### java-libraries  文件列表

* jdk1.7  若编译器javac版本为java 1.7.x版本
  * VoiceRecognize.jar
  * rokid_speech.jar
* jdk1.8  若编译器javac版本为java 1.8.x版本
  * VoiceRecognize.jar
  * rokid_speech.jar

**说明**
* VoiceRecognize.jar    -----前端拾音服务(turen)输入输出 的java api接口封装
* rokid_speech.jar    ---- 语音识别以及合成服务(speech/tts) 输入输出的java api接口封装

### shared-libraries 文件列表

* arm64-v8a
   * libc++_shared.so
   * librkcodec.so
   * librokid_opus_jni.so
   * librokid_speech_jni.so
   * libspeech.so
   * libuWS.so
* armeabi-v7a
   * libc++_shared.so
   * libr2mvdrbf.so
   * libr2ssp.so
   * libr2vt.so
   * librasr.so
   * librfe.so
   * librkcodec.so
   * librkvoicerec.so
   * librokid_opus_jni.so
   * librokid_speech_jni.so
   * libsourcelocation.so
   * libspeech.so
   * libtensorflow_inference.so
   * libtfam.so
   * libtfrtl.so
   * libturen.so
   * libturenrpc.so
   * libuWS.so
   * libztvad.so

**说明**
* common
  * libc++_shared.so
* 语音识别以及合成服务相关
  * librkcodec.so
  * librokid_opus_jni.so
  * librokid_speech_jni.so
  * libspeech.so
  * libuWS.so
* 前端拾音服务相关(目前还没有arm64-v8a 的so库)
  * libr2mvdrbf.so
  * libr2ssp.so
  * libr2vt.so
  * librasr.so
  * librfe.so
  * librkcodec.so
  * libsourcelocation.so
  * libtensorflow_inference.so
  * libtfam.so
  * libtfrtl.so
  * libturen.so
  * libturenrpc.so
  * libztvad.so



## 三、快速集成

### 集成步骤

#### 下载SDK

 * 请登录[Rokid 开发者社区官网](https://developer.rokid.com/#/) （https://developer.rokid.com/#/）， 选择语音接入，创建产品，并根据网站提示进行配置，最后生成 SDK 后进行下载即可。

#### 集成SDK

  * 将下载的SDK进行解压,解压后的目录结构说明请参照 [SDK目录结构](sdk_dir.md)
  * 需要将对应的```so/jar/exe```以及配置文件预置到系统指定位置,可参考方法如下:将解压后的目录放到系统源码中,比如```/vendor/rokid/sdk_v2/``` 目录下,然后在此文件夹下添加如下 [sdk_v2.mk](../extra/sdk_v2.mk) ,同时按照以下步骤使sdk能够被系统编译到
   * 在系统源码的```device/{platform}/{product}/*.mk``` 最后(此mk文件可以在编译时被编译到) 中添加如下
   ```
      $(call inherit-product,vendor/rokid/sdk_v2/sdk_v2.mk) 
   ```
   * 在 config 文件夹加下 添加 [Android.mk](../extra/android_config.mk) 
   * 在 executable 文件夹 添加 [Android.mk](../extra/android_executable.mk)
   * 在 shared-libraries 文件夹下添加 [Android.mk](../extra/android_libs.mk)
   * 将预置到```system/bin/turenproc``` 可执行进程加入到工程的```init.*.rc```中,使之能够以 root 权限在开机启动,示例如下:
   ```
     service turenproc /system/bin/turenproc <port> <deviceName>
     class main
     user root
     group root root
   ```
  其中 port 为启动 turenproc 进程启动时所依赖的运行端口号,比如: ```30000```, ```deviceName``` 为在网站上下载sdk时选择前端麦克风时的 ```deviceName``` ,与生成的``` workdir_asr_cn ``` 文件加中 ```ctc.{deviceName}.cfg```文件中的```deviceName```必须保持一致.假如在网站上 ```deviceName``` 取名为 pebble ,则需要如下方式启动
  ```
     service turenproc /system/bin/turenproc 30000 pebble
     class main
     user root
     group root root
  ```

   * 将 java-libraries 下的静态jar包集成到一个系统应用中,来接收前端语音事件以及ASR/NLP,以提供的 example 中的 SpeechExecutor [模块说明](introduce_speechexecutor.md)为例,集成编译后会在```system/app/SpeechExecutor```下生成 SpeechExecutor.apk, 在系统开机配置好网络后,通过```adb shell am startservice com.rokid.voicerec/.SpeechExecutor``` 来启动Demo的service,然后通过Log查看是否有前端语音事件以及asr/nlp相关的log信息,如果有则证明集成OK.如果没有,请参考下边的集成注意事项或者联系我们.

#### 集成注意事项

 * 目前Android全链路前端语音识别部分仅支持32位armeabi-v7a so文件输出,64位支持正在开发中,敬请期待.
 * 由于前端拾音模块需要读取Mic数据,因此各个客户/集成开发者需要在hal层实现mic设备的open以及read等接口,并以```"mic_array"```为```HAL_MODULE_INFO_SYM``` 的 id.具体接口为 android 标准的硬件设备hal层实现,具体可参考 [mic_array.c](../extra/mic_array.c) & [mic_array.h](../extra/mic_array.h) 的实现.目前支持的 mic 阵列数据采集格式至少为```16K/16bit/单通道``` 的数据格式.

#### 接口调用说明
* 请参考[Android全链路接口调用说明](api_voicerecognize.md)



## 四、API参考

VoiceRecognize.jar中包含```VoiceRecognize```和```VoiceRecognizeBuilder```两个比较重要的类。
使用```VoiceRecognizeBuilder```设置Rokid账号信息就能得到一个```VoiceRecognize```对象，账号获取方式见[创建设备流程](../rookie-guide/create-device.md)。
下面详细介绍```VoiceRecognize```内部类和接口定义。


#### VoiceRecognize

**方法预览**

| 返回类型  | 返回值                                   | 方法                                           | 备注                 |      |
| --------- | ---------------------------------------- | ---------------------------------------------- | -------------------- | ---- |
| int       | 成功返回0；失败返回-1                    | control(Action action)                         | 控制语音激活         |      |
| int       | 成功返回0；失败返回-1                    | addVtWord(VtWord vtWord)                       | 添加激活词           |      |
| int       | 成功返回0；失败返回-1                    | remoteVtWord(String content)                   | 删除激活词           |      |
| ArrayList | 成功返回激活词集合；失败返回一个空的集合 | getVtWords()                                   | 获取激活词           |      |
| int       | 成功返回0；失败返回-1                    | setSkillOption(String skillOption)             | 同步客户端信息到云端 |      |
| int       | 成功返回0；失败返回-1                    | updateStack(String currAppId,String prevAppId) | 更新云端NLP栈信息    |      |

**control(Action action)**

**方法说明**

控制语音激活

**参数说明**

| 字段   | 类型   | 描述     |
| ------ | ------ | -------- |
| action | Action | 控制意图 |

**返回说明**

| 类型 | 描述                  |
| ---- | --------------------- |
| int  | 成功返回0；失败返回-1 |

**addVtWord(VtWord vtWord)**

**方法说明**

添加激活词

**参数说明**

| 字段   | 类型   | 描述       |
| ------ | ------ | ---------- |
| vtWord | VtWord | 激活词信息 |

**返回说明**

| 类型 | 描述                  |
| ---- | --------------------- |
| int  | 成功返回0；失败返回-1 |

**remoteVtWord(String content)**

**方法说明**

删除激活词

**参数说明**

| 字段    | 类型   | 描述                        |
| ------- | ------ | --------------------------- |
| content | String | 需要删除的激活词utf-8字符串 |

**返回说明**

| 类型 | 描述                  |
| ---- | --------------------- |
| int  | 成功返回0；失败返回-1 |

**getVtWords()**

**方法说明**

获取激活词

**返回说明**

| 类型      | 描述                                     |
| --------- | ---------------------------------------- |
| ArrayList | 成功返回激活词集合；失败返回一个空的集合 |

**setSkillOption(String skillOption)**

**方法说明**

同步客户端信息到云端

**参数说明**

| 字段        | 类型   | 描述                  |
| ----------- | ------ | --------------------- |
| skillOption | String | 当前skill运行状态信息 |

**返回说明**

| 类型 | 描述                  |
| ---- | --------------------- |
| int  | 成功返回0；失败返回-1 |

**updateStack(String currAppId,String prevAppId)**

**方法说明**

更新云端NLP栈信息

**参数说明**

| 字段      | 类型   | 描述                          |
| --------- | ------ | ----------------------------- |
| currAppId | String | 执行当前语音命令的应用AppId   |
| prevAppId | String | 执行上一条语音命令的应用AppId |

**返回说明**

| 类型 | 描述                  |
| ---- | --------------------- |
| int  | 成功返回0；失败返回-1 |

#### 内部类
| 类型 | 名称   | 描述                                                         |
| :--: | :----- | :----------------------------------------------------------- |
| enum | Action | 语音控制意图枚举定义：<br> `ACTION_SET_STATE_AWAKE` 设置当前从休眠状态进入激活状态，此时不用说激活词直接语音命令即可，也可以通过说休眠词进入休眠状态<br>`ACTION_SET_STATE_SLEEP` 设置当前从激活状态进入休眠状态，此时可以通过唤醒词再次进入激活状态<br>`ACTION_OPEN_MIC` 打开麦克风，此时可以通过唤醒词进入激活状态<br>`ACTION_CLOSE_MIC` 关闭麦克风，需要打开麦克风才能通过唤醒词唤醒 |
| enum | Event  | 语音唤醒事件枚举定义：<br>`EVENT_VOICE_COMING` 激活即将开始<br>`EVENT_VOICE_LOCAL_WAKE` 本地已经激活<br>`EVENT_VOICE_START` 开始上传VAD<br>`EVENT_VOICE_NONE` 二次确认结果为空，只出于已经在激活状态下，直接说语音命令<br>`EVENT_VOICE_ACCEPT` 云端二次确认通过<br>`EVENT_VOICE_REJECT` 云端二次确认不通过<br>`EVENT_VOICE_CANCEL` 取消当前上传VAD<br>`EVENT_VOICE_LOCAL_SLEEP` 通过休眠词从激活状态进入休眠状态 |
|enum|ExceptionCode|异常状态定义：<br>`EXCEPTION_SERVICE_INTERNAL` 语音内部错误 <br> `EXCEPTION_ASR_TIMEOUT` ASR识别超时
|class|VtWord|激活词信息：`type` 激活词类型，`word`激活词中文字符表示形式，`pinyin`激活词拼音字符+音调表示形式(例：若琪 ruo4qi2，ruo为四声，qi为二声)|
|enum|Type|激活词类型枚举定义：`AWAKE`唤醒词，`SLEEP`休眠词，`HOTWORD`热词，`OTHER`保留|
|interface|Callback|接收识别结果的回调接口定义，详细介绍见第3节Callback接口说明|


#### 回调接口
#####  VoiceRecognize.Callback

| 返回类型 | 方法                                              | 备注                           |      |
| -------- | ------------------------------------------------- | ------------------------------ | ---- |
| void     | onVoiceEvent(Event event,float sl,float energy)   | 语音事件回调接口               |      |
| void     | onIntermediateResult(String asr，boolean isFinal) | 语音识别中间结果，可能回调多次 |      |
| void     | onRecognizeResult(String nlp,String action)       | 最终语音识别回调接口           |      |
| void     | onException(ExceptionCode code)                   | 语音识别出错                   |      |

**onVoiceEvent(Event event,float sl,float energy))**

**方法说明**

语音事件回调接口

**参数说明**

| 字段   | 类型  | 描述                             |
| ------ | ----- | -------------------------------- |
| event  | Event | 语音事件                         |
| sl     | float | 当前唤醒角度(0到360度之间)       |
| energy | float | 当前说话能量值(0到1之间的浮点数) |

**onIntermediateResult(String asr，boolean isFinal)**

**方法说明**

语音识别中间结果，可能回调多次

**参数说明**

| 字段    | 类型    | 描述                           |
| ------- | ------- | ------------------------------ |
| asr     | String  | 语音转文字结果                 |
| isFinal | boolean | 是否是最终完整的语音转文字结果 |

**onRecognizeResult(String nlp,String action)**

**方法说明**

最终语音识别回调接口

**参数说明**

| 字段   | 类型   | 描述             |
| ------ | ------ | ---------------- |
| nlp    | String | 自然语义解析结果 |
| action | String | 云端skill结果    |

**onException(ExceptionCode code)**

**方法说明**

语音识别出错

**参数说明**

| 字段 | 类型          | 描述   |
| ---- | ------------- | ------ |
| code | ExceptionCode | 错误码 |

#### 示例代码

```java
import android.util.Log;
    
    import com.rokid.voicerec.VoiceRecognize;
    import com.rokid.voicerec.VoiceRecognizeBuilder;
    
    public class MainService extends android.app.Service implements VoiceRecognize.Callback{
    
        private String TAG = getClass().getSimpleName();
        private VoiceRecognize mVoiceRecognize = null;
    
        @Override
        public void onCreate(){
            VoiceRecognizeBuilder builder = new VoiceRecognizeBuilder();
            mVoiceRecognize = builder.setHost("apigwws.open.rokid.com")
                .setPort(443)
                .setBranch("/api")
                .setKey("your key")
                .setSecret("your secret")
                .setDeviceTypeId("your device_type_id")
                .setDeviceId("your device_id")
                .setCallback(this)
                .build();
    
            //mVoiceRecognize.control(VoiceRecognize.Action.ACTION_OPEN_MIC);
        }   
    
        @Override
        public void onVoiceEvent(VoiceRecognize.Event event, float sl, float energy) {
            Log.d(TAG, "onVoiceEvent    event " + event + ", sl " + sl + ", energy " + energy);
        }   
        
        @Override
        public void onIntermediateResult(String asr, boolean isFinal) {
            Log.d(TAG, "onIntermediateResult    asr " + asr);
        }   
        
        @Override
        public void onRecognizeResult(String nlp, String action) {
            Log.d(TAG, "onRecognizeResult   nlp " + nlp + ", action " + action);
        }   
        
        @Override
        public void onException(int errCode) {
            Log.d(TAG, "onException     errCode " + errCode);
        }   
    
        @Override
        public android.os.IBinder onBind(android.content.Intent intent) {
            return null;
        }   
    }
    
```


