#语音识别服务（speech）接口定义

## 1. SDK 初始化

**接口说明**

Rokid Speech 语音合成 SDK 初始化

| ~      | 名称    | 类型                  | 描述                                    |
| ------ | ------- | --------------------- | --------------------------------------- |
| 接口   | prepare |                       | speech sdk初始化                        |
| 参数   | options | PrepareOptions | 选项，详见PrepareOptions数据结构 |
| 返回值 |         | bool                  | true 成功 false 失败                    |

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

## 2. SDK 关闭

**接口说明**

关闭 Rokid Speech 语音识别服务

| ~      | 名称    | 类型 | 描述           |
| ------ | ------- | ---- | -------------- |
| 接口   | release |      | speech sdk关闭 |
| 参数   | 无      |      |                |
| 返回值 | 无      |      |                |

## 3. 文本识别

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

## 4. 语音识别

**接口说明**

发起语音 speech

| ~      | 名称        | 类型                | 描述                                                        |
| ------ | ----------- | ------------------- | ----------------------------------------------------------- |
| 接口   | start_voice |                     | 发起语音speech                                              |
| 参数   | options     | VoiceOptions | 当前语音speech的选项，详见VoiceOptions。此参数可不带 |
| 返回值 |             | int32               | speech id                                                   |

**示例代码**

```
// 语音speech请求
// 不设置VoiceOptions，全部使用默认值。
int32_t id = speech->start_voice();
```

## 5. 发送语音数据

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

##6. 通知 SDK 语音数据发送完毕 

| ~      | 名称      | 类型  | 描述                                |
| ------ | --------- | ----- | ----------------------------------- |
| 接口   | end_voice |       | 通知sdk语音数据发送完毕，结束speech |
| 参数   | id        | int32 | speech id                           |
| 返回值 | 无        |       |                                     |

##7. 取消语音识别请求

**接口说明**

当用户调用了startVoice请求之后，如果想取消语音识别，可调用此方法，而不是endVoice方法

| ~      | 名称   | 类型  | 描述                 |
| ------ | ------ | ----- | -------------------- |
| 接口   | cancel |       | 取消指定的speech请求 |
| 参数   | id     | int32 | speech id            |
| 返回值 |        |       |                      |

##8. 获取 sppech 结果数据 

**接口说明**

获取 speech 结果数据

| ~      | 名称   | 类型                | 描述                                                         |
| ------ | ------ | ------------------- | ------------------------------------------------------------ |
| 接口   | poll   |                     | 获取speech结果数据。如无数据则一直阻塞等待，sdk关闭立即返回false。 |
| 参数   | result | SpeechResult | 成功时存放获取到的speech结果数据，详见 SpeechResult 数据结构 |
| 返回值 |        | bool                | true 成功 false sdk已关闭                                    |

## 9. 设置 speech 选项

**接口说明**	

设置 speech 选项

| ~      | 名称    | 类型                 | 描述                     |
| ------ | ------- | -------------------- | ------------------------ |
| 接口   | config  |                      | 设置speech选项           |
| 参数   | options | SpeechOptions | 详见SpeechOptions |
| 返回值 | 无      |                      |                          |


# 数据结构

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
| err    | enum SpeechError      | 详见[错误码](../common/err_code.md)                                       |
| asr    | string                | 语音转文本的结果                                             |
| nlp    | string                | 自然语义解析结果                                             |
| action | string                | rokid skill处理结果                                          |
| extra  | string                | 激活结果                                                     |


**SpeechOptions**
使用set\_xxx接口设定选项值，未设定的值将不会更改旧有的设定值

|~ | 名称 | 类型 | 描述|
|---|---|---|---|
|接口 | set\_lang | | 设定文字语言。设定speech put\_text接口要发送的文本的语言; 影响语音识别结果'asr'的文本语言|
|参数 | lang | enum Lang | 限定值ZH EN|


|~ | 名称 | 类型 | 描述|
|---|---|---|---|
|接口 | set\_codec | | 设定语音编码。指定put\_voice接口发送的语音编码格式|
|参数 | codec | enum Codec | 限定值PCM OPU|

|~ | 名称 | 类型 | 描述|
|---|---|---|---|
|接口 | set\_vad\_mode | | 设定语音起始结束检查在云端还是本地|
|参数 | mode | enum VadMode | 限定值LOCAL CLOUD|

|~ | 名称 | 类型 | 描述|
|---|---|---|---|
|接口 | set\_no\_nlp | | 设定是否需要服务端给出nlp结果|
|参数 | v | boolean | |

|~ | 名称 | 类型 | 描述|
|---|---|---|---|
|接口 | set\_no\_intermediate\_asr | | 设定是否需要服务端给出中间asr结果|
|参数 | v | boolean |

