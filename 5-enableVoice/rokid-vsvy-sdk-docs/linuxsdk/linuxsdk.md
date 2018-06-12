###目录

* [一、概述](#一、概述)
* [二、SDK 目录结构](#二、sdk目录结构)
* [三、快速集成](#三、快速集成)
  * [集成前准备](#集成前准备)
  * [开始集成](#开始集成)
* [四、API接口](#四、api接口)
  * [语音识别服务接口（speech）](#语音识别服务接口定义（speech）)
  * [语音合成服务接口（tts）](#语音合成服务接口定义（tts）)

### 一、概述
#### Rokid 语音识别服务（Speech）
Rokid语音识别服务与Rokid云平台对接，为各位开发者提供包括：文字识别、语音识别两种识别服务。

文字识别可以通过开发者提供的语句返回云平台对应的技能信息。

语音识别可以通过开发者提供的音频流识别出对应的文字，并相应的返回云平台对应的技能信息。
#### Rokid 语音合成服务（TTS）
Rokid语音合成服务可以根据开发者提供的文字合成高质量的音频。

###二、SDK 目录结构
#### speech

语音识别服务（speech）目录

- demo  ---- 语音识别服务（speech）和语音合成服务（tts）demo 源码
  - demo_tts.cc    ----  语音合成服务（tts）demo 源码
  - demo_speech.cc    ---- 语音识别服务（speech）demo 源码

- include  ---- 编译所需的头文件
  - speech.h  ----  语音识别服务（speech）的头文件
  - tts.h  ----  语音合成服务（tts）头文件 
  - speech_common.h   
  - rkcodec.h    --- opus 头文件

- src  ---- 源文件

#### uws

使用语音识别服务需要用到的 WebSocket 服务器库 

- src
- tests

### 三、快速集成
#### 集成前准备

**下载 Linux SDK**

请登录Rokid 开发者社区官网 （https://developer.rokid.com/#/）， 选择语音接入，创建产品，选择【基础语音模块】，并根据网站提示进行配置，最后生成 SDK 后进行下载即可。

#### 开始集成
##### 1）解压 Rokid_voice_sdk_v2_[timestamp].zip 安装包

将下载的 Rokid_voice_sdk_v2_[timestamp].zip 安装包放在你的目录下。

   ```
$ unzip Rokid_voice_sdk_v2_[timestamp].zip
$ cd speech_sdk
   ```

解压后生成两个文件夹 **speech** 和 **uws**。

例如：timestamp = 20180311170803

##### 2）编译

###### 非交叉编译（ubuntu & 树莓派）

非交叉编译适用于 ubuntu 系统或在树莓派上安装 ubuntu 系统的环境。方法如下：

* 安装 cmake
    ```
      $ sudo apt-get install cmake
    ```
  ```
  
* 安装 openssl 

  编译 uWS 模块时要依赖 openssl 库，所以要先安装 openssl 库

  ```
  $ sudo apt-get install libssl-dev
  ```

* 编译 uWS 模块

  ```
  $ cd /[your_path_to]/uWS/ 
  $ make
  ```

* 编译 speech 模块

  * 安装 opus 库

    speech 在传输的过程中要进行编解码，而 opus 是一个开放的，功能强大的编解码器

  ```
    $ cd ../speech/
    $ sudo apt-get install libopus-dev
    ```
    
    * 编译生成 build 目录
    
    build 目录是生成 tts、speech 可执行程序的目标文件夹
    
    ```
    $ rm-rf build/
    $ ./config --uws=../uWS/build/
    ```

###### 交叉编译

如果您的机器镜像是通过ARM交叉编译器编译，则使用如下方法进行编译：

* 首先需要保证您的交叉编译环境包含 openssl 、libopus 两个开源库，再交叉编译 uWS，并保证生成的库文件和头文件安装到您的交叉编译工具链依赖中
* 编译

```
$ cd /[your_path_to]/speech/
$ ./config --toolchain=工具链安装目录 --cross-prefix=工具链编译命令前缀 --cross-root-path=搜索依赖库的根路径
```

**注意：以上要输入的目录和路径等为你的机器工具存放的位置，并且在输入工具链安装目录，工具链编译命令前缀和搜索依赖库的根路径时必须填写绝对路径**。

例如：在 Rokid A113 开发板上编译，相应命令如下：

```
./config --toolchain=~/A113/output/banban_m2_a113/host/usr --cross-prefix=aarch64-linux-gnu- --cross-root-path=~/A113/output/banban_m2_a113/host/usr/aarch64-linux-gnu/sysroot/
```

##### 3）填写认证文件

在下载的 sdk 包里面有一个 speechConfig.json 文件，里面是用于认证的信息：

- KEY ： 用于认证设备
- Secret：用于认证设备
- device_type_id：此 ID 用于标识这一类型的设备，由 Rokid 开放平台生成
- device_id：用户为每个设备指明的设备 ID

将这些信息依次填入 /speech/demo/demo_tts.cc 和 /speech/demo/demo_speech.cc 中

```
$ cd demo/
```

```
int main(int argc, char** argv) {
	PrepareOptions opts;
	opts.host = "apigwws.open.rokid.com";
	opts.port = 443;
	opts.branch = "/api";
	opts.key = "rokid_test_key";                       // key 
	opts.device_type_id = "rokid_test_device_type_id"; // device_type_id
	opts.device_id = "ming.qiwo";                      // device_id
	opts.secret = "rokid_test_secret";                 // secret
	.
	.
	.
	return 0;
}

```

##### 4）编译生成 demo

上述操作完成之后就可以生成 demo 直接运行了，方法如下：

```
$ cd build/
$ make
```

编译完成后会生成 demo_tts，d	emo_speech 等可执行程序。

##### 5）运行

tts 运行方法：

```
$ ./demo_tts "文本信息"
```

执行完之后在同级目录下生成经过 tts 处理后的 data1.wav 的音频文件。

speech 运行方法：

```
$ ./demo_speech xxx.wav（音频文件）
```

执行完之后会识别语音信息，并且解析 nlp（自然语言处理）。

### 四、API接口
#### 语音识别服务接口定义（speech）
##### 1）SDK 初始化

**接口说明**

Rokid Speech 语音合成 SDK 初始化

| ~      | 名称    | 类型           | 描述                             |
| ------ | ------- | -------------- | -------------------------------- |
| 接口   | prepare |                | speech sdk初始化                 |
| 参数   | options | PrepareOptions | 选项，详见PrepareOptions数据结构 |
| 返回值 |         | bool           | true 成功 false 失败             |

**示例代码**

```
shared_ptr<Speech> speech = Speech::new_instance();
PrepareOptions popts;
popts.host = "apigwws.open.rokid.com";
popts.port = 443;
popts.branch = "/api";
// 认证信息，需要申请
popts.key = my_key;
popts.device_type_id = my_device_type;
popts.secret = my_secret;
// 设备名称，类似昵称，可自由选择，不影响认证结果
popts.device_id = "SmartDonkey";
```

##### 2）SDK 关闭

**接口说明**

关闭 Rokid Speech 语音识别服务

| ~      | 名称    | 类型 | 描述           |
| ------ | ------- | ---- | -------------- |
| 接口   | release |      | speech sdk关闭 |
| 参数   | 无      |      |                |
| 返回值 | 无      |      |                |

##### 3）文本识别

**接口说明**

Rokid 语音识别服务允许用户直接发送文字，并根据用户发送的文本，返回对应的数据

| ~      | 名称     | 类型        | 描述           |
| ------ | -------- | ----------- | -------------- |
| 接口   | put_text |             | 发起文本speech |
| 参数   | text     | const char* | speech文本     |
| 返回值 |          | int32       | speech id      |

**示例代码**

```
// 文本speech请求
speech->put_text("若琪你好");

```

#####4）语音识别

**接口说明**

发起语音 speech

| ~      | 名称        | 类型         | 描述                                                 |
| ------ | ----------- | ------------ | ---------------------------------------------------- |
| 接口   | start_voice |              | 发起语音speech                                       |
| 参数   | options     | VoiceOptions | 当前语音speech的选项，详见VoiceOptions。此参数可不带 |
| 返回值 |             | int32        | speech id                                            |

**示例代码**

```
// 语音speech请求
// 不设置VoiceOptions，全部使用默认值。
int32_t id = speech->start_voice();
```

##### 5）发送语音数据

**接口说明**

发送语音数据, 一次 speech 的语音数据可分多次发送

| ~      | 名称      | 类型         | 描述                                           |
| ------ | --------- | ------------ | ---------------------------------------------- |
| 接口   | put_voice |              | 发送语音数据, 一次speech的语音数据可分多次发送 |
| 参数   | id        | int32        | speech id                                      |
| 参数   | data      | const uint8* | 语音数据                                       |
| 参数   | length    | uint32       | 数据长度                                       |
| 返回值 | 无        |              |                                                |

**示例代码**

```
speech->put_voice(id, your_voice_data, len);
speech->put_voice(id, more_voice_data, len);
speech->put_voice(id, ...);
```

##### 6）通知 SDK 语音数据发送完毕

| ~      | 名称      | 类型  | 描述                                |
| ------ | --------- | ----- | ----------------------------------- |
| 接口   | end_voice |       | 通知sdk语音数据发送完毕，结束speech |
| 参数   | id        | int32 | speech id                           |
| 返回值 | 无        |       |                                     |

##### 7）取消语音识别请求

**接口说明**

当用户调用了startVoice请求之后，如果想取消语音识别，可调用此方法，而不是endVoice方法

| ~      | 名称   | 类型  | 描述                 |
| ------ | ------ | ----- | -------------------- |
| 接口   | cancel |       | 取消指定的speech请求 |
| 参数   | id     | int32 | speech id            |
| 返回值 |        |       |                      |

##### 8）获取 sppech 结果数据

**接口说明**

获取 speech 结果数据

| ~      | 名称   | 类型         | 描述                                                         |
| ------ | ------ | ------------ | ------------------------------------------------------------ |
| 接口   | poll   |              | 获取speech结果数据。如无数据则一直阻塞等待，sdk关闭立即返回false。 |
| 参数   | result | SpeechResult | 成功时存放获取到的speech结果数据，详见 SpeechResult 数据结构 |
| 返回值 |        | bool         | true 成功 false sdk已关闭                                    |

##### 9）设置 speech 选项

**接口说明**	

设置 speech 选项

| ~      | 名称    | 类型          | 描述              |
| ------ | ------- | ------------- | ----------------- |
| 接口   | config  |               | 设置speech选项    |
| 参数   | options | SpeechOptions | 详见SpeechOptions |
| 返回值 | 无      |               |                   |

##### 数据结构

**Speech.VoiceOptions**

| 名称           | 类型   | 描述                      |
| -------------- | ------ | ------------------------- |
| host           | string | tts服务host               |
| port           | uint32 | tts服务port               |
| branch         | string | tts服务url path           |
| key            | string | tts服务认证key            |
| device_type_id | string | 设备类型，用于tts服务认证 |
| secret         | string | 用于tts服务认证           |
| device_id      | string | 设备id，用于tts服务认证   |


**VoiceOptions**

| 名称            |  类型  | 描述                       |
| --------------- | :----: | -------------------------- |
| stack           | String |                            |
| voice\_trigger  | string | 激活词                     |
| trigger\_start  | uint32 | 语音数据中激活词的开始位置 |
| trigger\_length | uint32 | 激活词语音数据长度         |
| skill\_options  | string |                            |

**SpeechResult**
| 名称   | 类型                  | 描述                                                         |
| ------ | --------------------- | ------------------------------------------------------------ |
| id     | int32                 | speech请求id                                                 |
| type   | enum SpeechResultType | 0: speech中间结果<br>1: speech结果开始<br>2: speech asr完整结果<br>3: speech nlp/action结果<br>4: speech取消<br>5: speech出错 |
| err    | enum SpeechError      | 详见[错误码](../common/err_code.md)                          |
| asr    | string                | 语音转文本的结果                                             |
| nlp    | string                | 自然语义解析结果                                             |
| action | string                | rokid skill处理结果                                          |
| extra  | string                | 激活结果                                                     |


**SpeechOptions**
使用set\_xxx接口设定选项值，未设定的值将不会更改旧有的设定值

| ~    | 名称      | 类型      | 描述                                                         |
| ---- | --------- | --------- | ------------------------------------------------------------ |
| 接口 | set\_lang |           | 设定文字语言。设定speech put\_text接口要发送的文本的语言; 影响语音识别结果'asr'的文本语言 |
| 参数 | lang      | enum Lang | 限定值ZH EN                                                  |


| ~    | 名称       | 类型       | 描述                                               |
| ---- | ---------- | ---------- | -------------------------------------------------- |
| 接口 | set\_codec |            | 设定语音编码。指定put\_voice接口发送的语音编码格式 |
| 参数 | codec      | enum Codec | 限定值PCM OPU                                      |

| ~    | 名称           | 类型         | 描述                               |
| ---- | -------------- | ------------ | ---------------------------------- |
| 接口 | set\_vad\_mode |              | 设定语音起始结束检查在云端还是本地 |
| 参数 | mode           | enum VadMode | 限定值LOCAL CLOUD                  |

| ~    | 名称         | 类型    | 描述                          |
| ---- | ------------ | ------- | ----------------------------- |
| 接口 | set\_no\_nlp |         | 设定是否需要服务端给出nlp结果 |
| 参数 | v            | boolean |                               |

| ~    | 名称                       | 类型    | 描述                              |
| ---- | -------------------------- | ------- | --------------------------------- |
| 接口 | set\_no\_intermediate\_asr |         | 设定是否需要服务端给出中间asr结果 |
| 参数 | v                          | boolean |                                   |

#### 语音合成服务接口定义（TTS）
##### 1）SDK 初始化

**接口说明**

Rokid TTS 语音合成 SDK 初始化

| ~      | 名称    | 类型           | 描述                             |
| ------ | ------- | -------------- | -------------------------------- |
| 接口   | prepare |                | tts sdk初始化                    |
| 参数   | options | PrepareOptions | 选项，详见PrepareOptions数据结构 |
| 返回值 |         | bool           | true 成功 false 失败             |

**示例代码**

```
PrepareOptions opts;
	opts.host = "apigwws.open.rokid.com";
	opts.port = 443;
	opts.branch = "/api";
	opts.key = "rokid_test_key";
	opts.device_type_id = "rokid_test_device_type_id";
	opts.device_id = "ming.qiwo";
	opts.secret = "rokid_test_secret";
```

##### 2）SDK 关闭

**接口说明**

关闭 Rokid TTS 语音合成服务

| ~      | 名称    | 类型 | 描述        |
| ------ | ------- | ---- | ----------- |
| 接口   | release |      | tts sdk关闭 |
| 参数   | 无      |      |             |
| 返回值 | 无      |      |             |

**示例代码**

```
...
tts.release();
```

##### 3）文字转语音

**接口说明**

发起文字转语音请求

| ~      | 名称    | 类型        | 描述                                         |
| ------ | ------- | ----------- | -------------------------------------------- |
| 接口   | speak   |             | 发起文字转语音                               |
| 参数   | content | const char* | 文本                                         |
| 返回值 | int32   |             | 成功将文本加入待处理队列，返回id。失败返回-1 |

**示例代码**

```
...
int32_t id = tts->speak("我是会说话的机器人，我最爱吃的食物是机油，最喜欢的运动是聊天");
```

##### 4）取消文字转语音请求

**接口说明**

取消文字转语音请求

| ~      | 名称   | 类型  | 描述                       |
| ------ | ------ | ----- | -------------------------- |
| 接口   | cancel |       | 取消id指定的文字转语音请求 |
| 参数   | id     | int32 | 此前调用speak返回的id      |
| 返回值 | 无     |       |                            |

**示例代码**

```
...
tts.cancel(id) //此前调用speak返回的id
```

##### 5）修改 TTS 配置选项

**接口说明**

修改 TTS 配置选项

| ~      |    名称 | 类型       | 描述                                  |
| ------ | ------: | ---------- | ------------------------------------- |
| 接口   |  config |            | 修改tts配置选项                       |
| 参数   | options | TtsOptions | tts的配置选项，详见TtsOptions数据结构 |
| 返回值 |      无 |            |                                       |

**示例代码**

```
// 在prepare后任意时刻，都可以调用config修改配置

// 默认配置codec = PCM, declaimer = ZH, samplerate = 24000

// 下面的代码将codec修改为OPU2，declaimer、samplerate保持原状不变

shared_ptr<TtsOptions> topts = TtsOptions::new_instance();

topts->set_codec(Codec::OPU2);

tts->config(topts);
```

##### 6）获取 TTS 结果数据

**接口说明**

获取tts结果数据。如无数据则一直阻塞等待，sdk关闭立即返回false

| ~      | 名称   | 类型      | 描述                                                         |
| ------ | ------ | --------- | ------------------------------------------------------------ |
| 接口   | poll   |           | 获取tts结果数据。如无数据则一直阻塞等待，sdk关闭立即返回false。 |
| 参数   | result | TtsResult | 成功时存放获取到的tts结果数据，详见TtsResult数据结构         |
| 返回值 |        | bool      | true 成功 false sdk已关闭                                    |

**示例代码**

```
TtsResult result;

while (true) {
	if (!tts->poll(result))
		break;
	// 处理result
	handle_tts_result(result);
}
```

##### 数据结构

**PrepareOptions**

| 名称           | 类型   | 描述                      |
| -------------- | ------ | ------------------------- |
| host           | string | tts服务host               |
| port           | uint32 | tts服务port               |
| branch         | string | tts服务url path           |
| key            | string | tts服务认证key            |
| device_type_id | string | 设备类型，用于tts服务认证 |
| secret         | string | 用于tts服务认证           |

**TtsOptions**

使用set\_xxx接口设定选项值，未设定的值将不会更改旧有的设定值

| ~    | 名称       | 类型       | 描述                  |
| ---- | ---------- | ---------- | --------------------- |
| 接口 | set\_codec |            | 设定编码格式，默认PCM |
| 参数 | codec      | enum Codec | 限定值PCM, OPU2, MP3  |

| ~    | 名称           | 类型   | 描述                     |
| ---- | -------------- | ------ | ------------------------ |
| 接口 | set\_declaimer |        | 设定语音朗读者，默认"zh" |
| 参数 | declaimer      | string | 限定值"zh"               |

| ~    | 名称            | 类型   | 描述                      |
| ---- | --------------- | ------ | ------------------------- |
| 接口 | set\_samplerate |        | 设定语音采样率，默认24000 |
| 参数 | samplerate      | uint32 |                           |

|接口 | set\_lang | | 设定文字语言。设定speech put\_text接口要发送的文本的语言; 影响语音识别结果'asr'的文本语言|


**TtsResult**

| 名称  | 类型               | 描述                                                         |
| ----- | ------------------ | ------------------------------------------------------------ |
| type  | enum TtsResultType | 0: tts语音数据<br>1: tts语音开始<br>2: tts语音结束<br>3: tts请求取消<br>4: tts请求出错 |
| id    | int32              | tts请求id                                                    |
| err   | enum TtsError      | 详见[错误码](../common/err_code.md)                          |
| voice | string             | 语音数据                                                     |
