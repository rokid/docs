### 目录

* [一、概述](#一、概述)
* [二、SDK生成产物目录结构](#二、sdk生成产物目录结构)
* [三、快速集成](#三、快速集成)
  * [集成前准备](#集成前准备)
  * [语音识别服务集成](#语音识别服务集成)
  * [语音合成服务集成](#语音合成服务集成)
* [四、API 参考](#四、api参考)
  * [语音识别服务](#语音识别服务)
  * [语音合成服务](#语音合成服务)
* [五、示例源码](#五、示例源码)

### 一、概述
#### Rokid 语音识别服务（Speech）
Rokid语音识别服务与Rokid云平台对接，为各位开发者提供包括：文字识别、语音识别两种识别服务。

文字识别可以通过开发者提供的语句返回云平台对应的技能信息。

语音识别可以通过开发者提供的音频流识别出对应的文字，并相应的返回云平台对应的技能信息。
#### Rokid 语音合成服务（TTS）
Rokid语音合成服务可以根据开发者提供的文字合成高质量的音频。

### 二、SDK生成产物目录结构
#### config

* speech_config.json ---- sdk需要与厂商相关的key/secret等信息,在语音识别以及tts合成时,需要用这些配置信息进行认证,会作为参数传递进SDK,可以点击[语音接入](https://developer.rokid.com/voice/#/product/create/list)创建产品，在下载 SDk 处查看key/secret。

#### java-libraries  文件列表

* jdk1.7  若编译器javac版本为java 1.7.x版本
 * rokid_speech.jar
* jdk1.8  若编译器javac版本为java 1.8.x版本
  * rokid_speech.jar

**说明**
* rokid_speech.jar    ---- 语音识别以及合成服务(speech/tts) 输入输出的java api接口封装

#### shared-libraries 文件列表

* arm64-v8a
  * libc++_shared.so
  * librkcodec.so
  * librokid_opus_jni.so
  * librokid_speech_jni.so
  * libspeech.so
  * libuWS.so
* armeabi-v7a
   * libc++_shared.so
   * librkcodec.so
   * librokid_opus_jni.so
   * librokid_speech_jni.so
   * libspeech.so
   * libuWS.so

### 三、快速集成
#### 集成前准备
##### 获取SDK

 * 请登录[Rokid 开发者社区官网](https://developer.rokid.com/#/) （https://developer.rokid.com/#/）， 选择语音接入，创建产品，并根据网站提示进行配置，最后生成 SDK 后进行下载即可。

##### 复制文件

将```java-libraries```文件夹下的```rokid_speech.jar```复制到 Android 工程下的 ```app/libs``` 文件夹中，并设置为工程的依赖库

![](image/init_jar.png)

将```shared-libraries```文件夹下的全部文件包含文件夹复制到 Android 工程下的```app/src/main/jniLibs``` 文件夹中

![](image/init_jnilibs.png)

##### 添加权限

```xml
    <!--网络访问权限-->
    <uses-permission android:name="android.permission.INTERNET" />
```

#### 语音识别服务集成

用户需要在使用语音识别服务之前，调用以下代码来进行初始化

首先创建实例

```java
        Speech speech = new Speech();
```
传入之前获取的相关秘钥，以及相关配置信息

```java
        PrepareOptions prepareOptions = new PrepareOptions();
        prepareOptions.host = "apigwws.open.rokid.com";
        prepareOptions.port = 443;
        prepareOptions.branch = "/api";
        //key
        prepareOptions.key = "";
        //device_type_id
        prepareOptions.device_type_id = "";
        //secret
        prepareOptions.secret = "";
        // 设备名称，类似昵称，可自由选择，不影响认证结果
        prepareOptions.device_id = "";
        
        speech.prepare(prepareOptions);

```
在prepare后任意时刻，都可以调用config修改配置
```java
        // 修改音频编码格式及语言，其它选项不变
        SpeechOptions opts = new SpeechOptions();
        opts.set_codec("opu");
        opts.set_lang("zh");
        speech.config(opts);
```

以上为初始化步骤，初始化完成后，开发者可模拟发送语音识别请求来验证是否集成成功

```java
// 语音Speech请求
// 不设置VoiceOptions，全部使用默认值。
int id = speech.startVoice(new SpeechCallback() {
                ......
            });
speech.putVoice(id, your_voice_data);
speech.putVoice(id, more_voice_data);
speech.putVoice(id, ...);
...
speech.endVoice(id);
```

```java
// 文字Speech请求
speech.putText("你好若琪", new SpeechCallback() {
            @Override
            public void onStart(int i) {
                LogUtil.d("onStart " + i);
            }

            @Override
            public void onIntermediateResult(int i, String s, String s1) {
                LogUtil.d("onIntermediateResult " + i + " " + s + " " + s1);
            }

            @Override
            public void onAsrComplete(int i, String s) {
                LogUtil.d("onAsrComplete " + i + " " + s);
            }

            @Override
            public void onComplete(int i, final String s, final String s1) {
                LogUtil.d("onComplete " + s + " " + s1);
                //需要在主线程更新ui
             
            }

            @Override
            public void onCancel(int i) {
                LogUtil.d("onCancel " + i);
            }

            @Override
            public void onError(int i, int i1) {
                LogUtil.d("onError " + i + " " + i1);
            }
        });
```

#### 语音合成服务集成

用户需要在使用语音合成服务之前，调用以下代码来进行初始化

首先创建实例

```java
        Tts tts = new Tts();
```
传入之前获取的相关秘钥，以及相关配置信息

```java
        PrepareOptions popts = new PrepareOptions();
        popts.host = "apigwws.open.rokid.com";
        popts.port = 443;
        popts.branch = "/api";
        // 认证信息，需要申请
        popts.key = "";
        popts.device_type_id = "";
        popts.secret = "";
        // 设备名称，类似昵称，可自由选择，不影响认证结果
        popts.device_id = "";
        tts.prepare(popts);

```
在prepare后任意时刻，都可以调用config修改配置
```java
        // 默认配置codec = "pcm", declaimer = "zh", samplerate = 24000
        // 下面的代码将codec修改为"opu2"，declaimer、samplerate保持原状不变
        TtsOptions topts = new TtsOptions();
        topts.set_codec("opu2");
        tts.config(topts);
```

以上为初始化步骤，初始化完成后，开发者可以调用语音合成接口来验证是否集成成功

```java
// 语音Speech请求
// 不设置VoiceOptions，全部使用默认值。
int id = speech.startVoice(new SpeechCallback() {
                ......
            });
speech.putVoice(id, your_voice_data);
speech.putVoice(id, more_voice_data);
speech.putVoice(id, ...);
...
speech.endVoice(id);
```

```java
        tts.speak(s,
                new TtsCallback() {
                    // 在这里实现回调接口 onStart, onVoice等
                    // 在onVoice中得到语音数据，调用播放器播放
                    @Override
                    public void onStart(int i) {

                    }

                    @Override
                    public void onText(int i, String s) {

                    }

                    public void onVoice(int id, byte[] data) {
                        OpusPlayer opusPlayer = new OpusPlayer();
                        opusPlayer.play(data);
                    }

                    @Override
                    public void onCancel(int i) {

                    }

                    @Override
                    public void onComplete(int i) {

                    }

                    @Override
                    public void onError(int i, int i1) {

                    }
                });
```

### 四、API 参考
#### 语音识别服务
##### 1）SDK 初始化

**接口说明**

Rokid Speech 语音合成 SDK 初始化

**方法预览**

| 返回类型 | 方法                            | 备注                     |      |
| -------- | ------------------------------- | ------------------------ | ---- |
| void     | prepare(PrepareOptions options) | 使用PrepareOption 初始化 |      |

**参数说明**

| 字段    | 类型           | 必须？ | 描述                             |
| ------- | -------------- | ------ | -------------------------------- |
| options | PrepareOptions | 可选   | 选项，详见PrepareOptions数据结构 |

**示例代码**

```java
//使用 PrepareOption 初始化
                Speech speech = new Speech();
                PrepareOptions prepareOptions = new PrepareOptions();
                prepareOptions.host = "apigwws.open.rokid.com";
                prepareOptions.port = 443;
                prepareOptions.branch = "/api";
                prepareOptions.key = Prepare.ROKID_KEY;
                prepareOptions.device_type_id = Prepare.ROKID_DEVICE_TYPE_ID;
                prepareOptions.secret = Prepare.ROKID_SECRET;
                prepareOptions.device_id = Prepare.ROKID_DEVICE_ID;
                speech.prepare(prepareOptions);
```
##### 2）SDK 关闭

**接口说明**

关闭 Rokid Speech 语音识别服务

**方法预览**

| 返回类型 | 方法      | 备注           |      |
| -------- | --------- | -------------- | ---- |
| void     | release() | Speech SDK关闭 |      |

**示例代码**

```java
	...
	speech.release();
```
##### 3）文本识别

**接口说明**

Rokid 语音识别服务允许用户直接发送文字，并根据用户发送的文本，返回对应的数据

**方法预览**

| 返回类型 | 方法    | 备注                                                  |      |
| -------- | ------- | ----------------------------------------------------- | ---- |
| int      | putText | 发起文本识别，返回值为当前发起的语音识别请求speech id |      |

**参数说明**

| 返回类型 | 方法           | 备注               |      |
| -------- | -------------- | ------------------ | ---- |
| text     | String         | speech文本         |      |
| cb       | SpeechCallback | speech回调接口对象 |      |

**示例代码**

```java

        speech.putText(s, new SpeechCallback() {
            @Override
            public void onStart(int i) {
                LogUtil.d("onStart " + i);
            }

            @Override
            public void onIntermediateResult(int i, String s, String s1) {
                LogUtil.d("onIntermediateResult " + i + " " + s + " " + s1);
            }

            @Override
            public void onAsrComplete(int i, String s) {
                LogUtil.d("onAsrComplete " + i + " " + s);
            }

            @Override
            public void onComplete(int i, final String s, final String s1) {
                LogUtil.d("onComplete " + s + " " + s1);
                //需要在主线程更新ui
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        //自然语义解析结果
                        tvAsrResult.setText(s);
                        //Rokid Speech skill返回的结果
                        tvAsrBackResult.setText(s1);
                    }
                });
            }

            @Override
            public void onw/Cancel(int i) {
                LogUtil.d("onCancel " + i);
            }

            @Override
            public void onError(int i, int i1) {
                LogUtil.d("onError " + i + " " + i1);
            }
        });

```

##### 4）语音识别

| 返回类型 | 返回值    | 方法                                                     | 备注                                           |      |
| -------- | --------- | -------------------------------------------------------- | ---------------------------------------------- | ---- |
| int      | speech id | startVoice(SpeechCallback callback,VoiceOptions options) | 发起语音speech，返回                           |      |
| void     |           | putVoice(int id ,byte[] data)                            | 发送语音数据, 一次speech的语音数据可分多次发送 |      |
| void     |           | endVoice(int id)                                         | 通知sdk语音数据发送完毕，结束speech            |      |

**startVoice**

**参数说明**

| 字段    | 类型           | 必须？ | 描述                                     |
| ------- | -------------- | ------ | ---------------------------------------- |
| cb      | SpeechCallback | 是     | speech回调接口对象                       |
| options | VoiceOptions   | 否     | 当前语音speech的选项，详见VoiceOptions。 |

**putVoice**

**参数说明**

| 字段 | 类型   | 必须？ | 描述                                                   |
| ---- | ------ | ------ | ------------------------------------------------------ |
| id   | int    | 是     | speech id                                              |
| data | byte[] | 是     | 语音数据,**输入的音频流必须为16bit 16kHz采样，单声道** |

**endVoice**

**参数说明**

| 字段 | 类型 | 必须？ | 描述      |
| ---- | ---- | ------ | --------- |
| id   | int  | 是     | speech id |

**示例代码**

```java
int speechId = speech.startVoice(new SpeechCallback() {
            @Override
            public void onStart(int i) {
                
            }

            @Override
            public void onIntermediateResult(int i, String s, String s1) {

            }

            @Override
            public void onAsrComplete(int i, String s) {

            }

            @Override
            public void onComplete(int i, String s, String s1) {

            }

            @Override
            public void onCancel(int i) {

            }

            @Override
            public void onError(int i, int i1) {

            }
        });
        speech.putVoice(speechId,voiceByte);
        speech.endVoice(speechId);

```

##### 5）设置语音识别参数

**接口说明**

用户可以通过这种方式来手动录音，并发送给语音分析服务器，并返回识别结果

**方法预览**

| 返回类型 | 方法                          | 备注                     |      |
| -------- | ----------------------------- | ------------------------ | ---- |
| void     | config(SpeechOptions options) | 语音识别Speech的配置选项 |      |

**参数说明**

| 字段   | 类型          | 必须？ | 描述 |
| ------ | ------------- | ------ | ---- |
| config | SpeechOptions | 是     |      |

##### 6）取消语音识别请求

**接口说明**

当用户调用了startVoice请求之后，如果想取消语音识别，可调用此方法，而不是endVoice方法

**方法预览**

| 返回类型 | 方法           | 备注                 |      |
| -------- | -------------- | -------------------- | ---- |
| void     | cancel(int id) | 取消指定的speech请求 |      |

**参数说明**

| 字段 | 类型 | 必须？ | 描述      |
| ---- | ---- | ------ | --------- |
| id   | int  | 是     | speech id |

**示例代码**

```java
speech.cancel(speechId);
```

##### 7）SpeechOptions

使用SpeechOptions设置语音识别相关参数

| 返回类型 | 方法                                  | 备注                                                         |      |
| -------- | ------------------------------------- | ------------------------------------------------------------ | ---- |
| void     | set\_lang(String lang)                | 设定文字语言。设定speech putText接口要发送的文本的语言; 影响语音识别结果'asr'的文本语言 |      |
| void     | set\_codec(String codec)              | 设定语音编码。指定putVoice接口发送的语音编码格式             |      |
| void     | set\_vad\_mode(String mode)           | 设定语音起始结束检查在云端还是本地                           |      |
| void     | set\_no\_nlp(boolean v)               | 设定是否需要服务端给出nlp结果                                |      |
| void     | set\_no\_intermediate\_asr(boolean v) | 设定是否需要服务端给出中间asr结果                            |      |

**set\_lang**

**参数说明**

| 字段 | 类型   | 必须？ | 描述           |
| ---- | ------ | ------ | -------------- |
| lang | String | 是     | 限定值```zh``` |

**set\_codec**

**参数说明**

| 字段  | 类型   | 必须？ | 描述                                 |
| ----- | ------ | ------ | ------------------------------------ |
| codec | String | 是     | 编码格式，限定值```pcm```、```opu``` |

**set\_vad\_mode**

**参数说明**

| 字段 | 类型   | 必须？ | 描述                            |
| ---- | ------ | ------ | ------------------------------- |
| mode | String | 是     | 限定值```local```、 ```cloud``` |

**set\_no\_nlp**

**参数说明**

| 字段 | 类型    | 必须？ | 描述 |
| ---- | ------- | ------ | ---- |
| v    | boolean | 是     |      |

**set\_no\_intermediate\_asr**

**参数说明**

| 字段 | 类型    | 必须？ | 描述 |
| ---- | ------- | ------ | ---- |
| v    | boolean | 是     |      |

##### 8）回调接口

###### SpeechCallback

**方法预览**

| 返回类型 | 方法                                                         | 备注                       |      |
| -------- | ------------------------------------------------------------ | -------------------------- | ---- |
| void     | onStart(int id)                                              | speech结果开始返回         |      |
| void     | onIntermediateResult(int id,String asrResult，String extraResult) | 给出当前已经转成语音的文字 |      |
| void     | onAsrComplete(int id,String asrResult)                       | speech asr完整结果         |      |
| void     | onComplete(int id，String nlpResult,String intent)           | speech最终结果             |      |
| void     | onCancel(int id)                                             | speech被取消               |      |
| void     | onError(int id,int errCode)                                  | speech出错                 |      |

**onStart(int id)**

**方式说明**

通知开发者，语音识别的结果开始返回。

**参数说明**

| 字段 | 类型 | 描述                |
| ---- | ---- | ------------------- |
| id   | int  | 当前Speech 请求的id |

**onIntermediateResult(int id,String asrResult，String extraResult)**

**方法说明**

持续返回当前语音识别出的文字

**参数说明**

| 字段        | 类型   | 描述               |
| ----------- | ------ | ------------------ |
| id          | int    | speech id          |
| asrResult   | String | 语音转文字中间结果 |
| extraResult | String | 激活结果           |

**onAsrComplete(int id,String asrResult)**

**方法说明**

语音识别技术后返回完整的语音识别结果

**参数说明**

| 字段      | 类型   | 描述                |
| --------- | ------ | ------------------- |
| id        | int    | 当前Speech 请求的id |
| asrResult | String | 语音转文字完整结果  |

**onComplete(int id，String nlpResult,String intent)**

**方法说明**

根据识别结果返回Rokid 云平台上的skill信息

**参数说明**

| 字段      | 类型   | 描述                         |
| --------- | ------ | ---------------------------- |
| id        | int    | 当前Speech 请求的id          |
| nlpResult | String | 自然语义解析结果             |
| intent    | String | rokid speech skill返回的结果 |

**onCancel(int id)**

**方法说明**

语音是被取消

**参数说明**

| 字段 | 类型 | 描述                |
| ---- | ---- | ------------------- |
| id   | int  | 当前Speech 请求的id |
**onError(int id,int errCode)**

**方法说明**

语音识别发生错误，详情请看[错误码](../common/err_code.md)

**参数说明**

| 字段    | 类型 | 描述                |
| ------- | ---- | ------------------- |
| id      | int  | 当前Speech 请求的id |
| errCode | int  | 错误码              |

##### 数据结构
###### PrepareOptions

| 名称             | 类型   | 描述                                                 |
| ---------------- | ------ | ---------------------------------------------------- |
| host             | String | 语音识别服务host,一般为 ```apigwws.open.rokid.com``` |
| port             | int    | 语音识别服务port ```443```                           |
| branch           | String | 语音识别服务url path ```/api```                      |
| key              | String | 语音识别服务认证key                                  |
| device\_type\_id | String | 设备类型，用于语音识别服务认证                       |
| secret           | String | 用于语音识别服务认证                                 |
| device\_id       | String | 设备id，用于语音识别服务认证                         |

获取key、id等参数，请参考[创建设备流程](../rookie-guide/create-device.md)章节。

#### 语音合成服务
##### 1）SDK 初始化

**接口说明**

Rokid TTS 语音合成 SDK 初始化

**方法预览**

| 返回类型 | 方法                            | 备注                     |      |
| -------- | ------------------------------- | ------------------------ | ---- |
| void     | prepare(PrepareOptions options) | 使用PrepareOption 初始化 |      |
| void     | prepare(String configFile)      | 使用配置文件初始化       |      |
| void     | prepare(InputStream is)         | 使用流初始化             |      |

**参数说明**

| 字段       | 类型           | 必须？ | 描述                                                      |
| ---------- | -------------- | ------ | --------------------------------------------------------- |
| options    | PrepareOptions | 可选   | 选项，详见PrepareOptions数据结构                          |
| configFile | String         | 可选   | 配置文件路径名。文件内容详见[json格式配置字串](#jsonconf) |
| is         | InputStream    | 可选   | 数据流，流内容详见[json格式配置字串](#jsonconf)           |

**示例代码**

```java
//使用 PrepareOption 初始化
        TTS tts = new TTS();
		PrepareOptions popts = new PrepareOptions();
        popts.host = "apigwws.open.rokid.com";
        popts.port = 443;
        popts.branch = "/api";
        popts.key = "";
        popts.device_type_id = "";
        popts.secret = "";
        popts.device_id ="";
        tts.prepare(popts);
```

##### 2）SDK 关闭

**接口说明**

关闭 Rokid TTS 语音合成服务

**方法预览**

| 返回类型 | 方法      | 备注        |      |
| -------- | --------- | ----------- | ---- |
| void     | release() | TTS SDK关闭 |      |

**示例代码**

```java
	...
	tts.release();
```

##### 3）文字转语音

**接口说明**

发起文字转语音请求

**方法预览**

| 返回类型 | 方法                                   | 备注               |      |
| -------- | -------------------------------------- | ------------------ | ---- |
| int      | speak(String s , TtsCallback callback) | 发起文字转语音请求 |      |

**参数说明**

| 字段     | 类型        | 必须？ | 描述         |
| -------- | ----------- | ------ | ------------ |
| s        | String      | 必须   | 要朗读的文本 |
| callback | TtsCallback | 必须   | 回调接口     |

**返回值**

| 类型 | 描述                                         |
| ---- | -------------------------------------------- |
| int  | 成功将文本加入待处理队列，返回id。失败返回-1 |

**示例代码**

```java
	int id = 0;
	id = tts.speak(s,new TtsCallback() {
                    // 在这里实现回调接口 onStart, onVoice等
                    // 在onVoice中得到语音数据，调用播放器播放
                    @Override
                    public void onStart(int i) {

                    }

                    @Override
                    public void onText(int i, String s) {

                    }

                    public void onVoice(int id, byte[] data) {
                    	...doSth
                    }

                    @Override
                    public void onCancel(int i) {

                    }

                    @Override
                    public void onComplete(int i) {

                    }

                    @Override
                    public void onError(int i, int i1) {

                    }
                });
```

##### 4）取消文字转语音请求

**接口说明**

取消文字转语音请求

**方法预览**

| 返回类型 | 方法           | 备注               |      |
| -------- | -------------- | ------------------ | ---- |
| void     | cancel(int id) | 取消文字转语音请求 |      |

**参数说明**

| 字段     | 类型        | 必须？ | 描述                  |
| -------- | ----------- | ------ | --------------------- |
| id       | String      | 必须   | 此前调用speak返回的id |
| callback | TtsCallback | 必须   | 回调接口              |

**示例代码**

```java
	...
	tts.cancel(id) //此前调用speak返回的id
```

##### 5）修改TTS配置选项

**接口说明**

修改TTS配置选项

**方法预览**

| 返回类型 | 方法                       | 备注                                  |      |
| -------- | -------------------------- | ------------------------------------- | ---- |
| void     | config(TtsOptions options) | TTS的配置选项，详见TtsOptions数据结构 |      |

**参数说明**

| 字段    | 类型       | 必须？ | 描述                                  |
| ------- | ---------- | ------ | ------------------------------------- |
| options | TtsOptions | 是     | TTS的配置选项，详见TtsOptions数据结构 |

**示例代码**

```java
	TtsOptions options = new TtsOptions();
    //son=me config	
	tts.config(options);
	
```

##### 6）OpusPlayer接口

**接口说明**
用于帮助播放opu2格式tts音频数据的工具类

**参数说明**

| 字段 | 类型   | 必须？ | 描述     |
| ---- | ------ | ------ | -------- |
| data | byte[] | 是     | 音频数据 |

**示例代码**

```java
    OpusPlayer opusPlayer = new OpusPlayer();
    opusPlayer.play(data);
```

##### 7）TtsOptions

**set\_codec**

**参数说明**

| 字段  | 类型   | 必须？ | 描述                                             |
| ----- | ------ | ------ | ------------------------------------------------ |
| codec | String | 是     | 编码格式，限定值```pcm```、```opu2```、```mp3``` |

**set\_declaimer**

**参数说明**

| 字段      | 类型   | 必须？ | 描述                          |
| --------- | ------ | ------ | ----------------------------- |
| declaimer | String | 是     | 设定语音朗读者,限定值```zh``` |

**set\_samplerate**

**参数说明**

| 字段       | 类型 | 必须？ | 描述                            |
| ---------- | ---- | ------ | ------------------------------- |
| samplerate | int  | 是     | 设定语音采样率，默认```24000``` |

**示例代码**

```java
	TtsOptions options = new TtsOptions();
	topts.set_codec("opu2");
	topts.set_ declaimer("zh");
	topts.set_samplerate(24000);
	tts.config(options);
```

##### 8）回调接口
###### TtsCallback

| 返回类型 | 方法                        | 备注                       |      |
| -------- | --------------------------- | -------------------------- | ---- |
| void     | onStart(int i)              | 开始接收语音数据流         |      |
| void     | onText(int i,String s)      | 给出当前已经转成语音的文字 |      |
| void     | onVoice(int id,byte[] data) | 语音数据流                 |      |
| void     | onCancel(int i)             | 语音转文字已经取消         |      |
| void     | onComplete(int i)           | 语音数据已经全部给出       |      |
| void     | onError(int id,int i1)      | 文字转语音出错             |      |

**onStart**

**参数说明**

| 字段 | 类型 | 描述                                       |
| ---- | ---- | ------------------------------------------ |
| i    | int  | 成功将文本加入待处理队列,TTS Speak返回的id |

**onText**

| 字段 | 类型   | 描述                   |
| ---- | ------ | ---------------------- |
| i    | int    | TTS Speak返回的id      |
| s    | String | 当前已经转成语音的文字 |

**onVoice**

| 字段 | 类型   | 描述                                 |
| ---- | ------ | ------------------------------------ |
| id   | int    | TTS Speak返回的id                    |
| data | byte[] | 语音数据，根据TtsOptions决定编码格式 |

**onCancel**

| 字段 | 类型 | 描述              |
| ---- | ---- | ----------------- |
| i    | int  | TTS Speak返回的id |

**onComplete**

| 字段 | 类型 | 描述              |
| ---- | ---- | ----------------- |
| i    | int  | TTS Speak返回的id |

**onError**

| 字段 | 类型 | 描述              |
| ---- | ---- | ----------------- |
| id   | int  | TTS Speak返回的id |
| i1   | int  | 错误码            |

##### 数据结构
###### PrepareOptions

| 名称             | 类型   | 描述                                                 |
| ---------------- | ------ | ---------------------------------------------------- |
| host             | String | 语音识别服务host,一般为 ```apigwws.open.rokid.com``` |
| port             | int    | 语音识别服务port ```443```                           |
| branch           | String | 语音识别服务url path ```/api```                      |
| key              | String | 语音识别服务认证key                                  |
| device\_type\_id | String | 设备类型，用于语音识别服务认证                       |
| secret           | String | 用于语音识别服务认证                                 |
| device\_id       | String | 设备id，用于语音识别服务认证                         |

获取key、id等参数，请参考“产品创建和SN导入”章节。

### 五、示例源码

参见[示例源码RokidSpeechTTSDemo](https://github.com/Rokid/RokidSpeechTTSDemo)

