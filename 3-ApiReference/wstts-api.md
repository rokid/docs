### 语音合成 WebSocket 接口定义文档

### 概述

本文档目的是描述云端语音接口的 WebSocket 版本的开放协议，面向想要了解语音合成（TTS）细节，并具有一定开发能力的开发者或用户。

### 协议详解

- [设备认证](#设备认证)
- [语音合成](#语音合成)（tts）


#### WebSocket API 接入参考Demo
[WebSocket 接入Demo（JAVA）](https://github.com/Rokid/rokid-speech)

[WebSocket  接入Demo（Python）](https://github.com/Rokid/speech-python-demo)



### 服务地址

| 环境 | 地址                                   | 用途                   |
| ---- | -------------------------------------- | ---------------------- |
| 线上 | wss://apigwws.open.rokid.com/api       | 对外提供的正式稳定环境 |

### 协议地址

- [github](https://github.com/Rokid/rokid-openvoice-websocket/tree/master/protobuf)

### 协议概述

此文档用于定义开放平台上云端应用接口开发协议，协议遵循 [websocket](https://zh.wikipedia.org/zh-cn/WebSocket) 协议。协议采用先认证，再使用的方式，步骤如下：

* 建立 wss 连接，注意是 **websocket + ssl**
* 认证
* 如果认证中 service 为 speech，则此连接后续可进行一次或多次语音交互，直至连接断开
* 如果认证中 service 为 tts，则此连接后续可进行一次或多次语音合成，直至连接断开

* 如果需要同时使用语音识别与语音合成，则需要建立**两条** wss 连接，**每条连接需要分别作认证**

#### 设备认证

##### AuthRequest


| 参数             | 类型     | 描述                     | 默认值  |
| -------------- | ------ | ---------------------- | ---- |
| key            | string | 开放接口Key，在[开放平台语音接入](https://developer.rokid.com/docs/2-RokidDocument/2-EnableVoice/get-the-certification-file.html)获取        | 无，必填 |
| device_type_id | string | 设备类型ID                 | 无，必填 |
| device_id      | string | 设备ID                   | 无，必填 |
| service        | string | tts                      | 无，必填 |
| version        | string | 接口版本号                  | 无，必填 |
| timestamp      | string | unix时间戳              | 无，必填 |
| sign           | string | 由以上几项及 secret 按约定的加密方式生成 | 无，必填 |

##### 说明

1. 字段 sign 计算方法：


  1. 拼成如下字符串 utf8 的字符串：key={key}&device_type_id={device_type_id}&device_id={device_id}&service={service}&version={version}&time={time}&secret={secret}，其中 ：
     - {xxx} 由 xxx 的值替代
     - key 及 secret 由开发方通过[开放平台语音接入](https://developer.rokid.com/docs/2-RokidDocument/2-EnableVoice/get-the-certification-file.html)获取
  2. 计算 str 字符串的 md5 值

2. 字段 version 有 1.0 或 2.0，分别对应 [协议地址](#%E5%8D%8F%E8%AE%AE%E5%9C%B0%E5%9D%80) 中 v1 或 v2 目录，目前支持的协议版本：

  - 语音识别： serivce(**speech**)， version(**2**)

  - 语音合成 ：serivce(**tts**)， version(**1**)


##### AuthResponse

| 参数     | 类型    | 描述                |
| ------ | ----- | ----------------- |
| result | int32 | 认证结果(成功:0, 失败:-1) |

##### 说明

1. 当认证失败时，服务端会**主动断开**此连接。

#### 语音合成接入说明

##### 流程
1. 需要先进行 service 为 tts 的 [设备认证](#%E8%AE%BE%E5%A4%87%E8%AE%A4%E8%AF%81)
2. 一次完整的语音合成的数据包以 id 来标识，称为一个 session
3. 语音数据以流的形式返回
4. 中间数据块 finish = false
5. 以 finish = true 的数据块结束

##### TtsRequest

| 参数     | 类型        | 描述                   | 默认值  |
| ------ | --------- | -------------------- | ---- |
| id        | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。   | 0    |
| text   | string    | 需要转换的text文本          | 空   |
| declaimer | string | 发音人，目前支持 中文成人 "zh" 与 中文儿童 "c1" 两种 | 空 |
| codec     | string | 语音流的编码，目前支持PCM、OPU、OPU2、mp3。   | 空 |
| sample_rate | uint32 | 语音流的码率，目前支持 16000 与 24000 | 24000 |

##### 说明

1. declaimer 发音人
   - zh: 成人，会读中文与英文
   - c1: 儿童，会读中文与英文(完善中)
2. text 中的文本中可以设置 SSML 标签，详见[SSML文档](https://developer.rokid.com/docs/2-RokidDocument/1-SkillsKit/ssml-document.html)
3. codec 编码格式：
   - pcm：24000，16bit，mono
   - opu：由数据帧组成，每帧由 1字节（后面数据长度）与 用opus压缩320字节后的数据
   - opu2：与 opu 区别是没有表示数据长度的1字节
   - mp3：mp3编码，保存成文件可以直接用播放器播放
4. sample_rate 可设置为 16000 或 24000，16000 语音数据较少，所需带宽较小，效果较差，默认为24000

##### TtsResponse

| 参数    | 类型     | 描述            |
| ----- | ------ | ------------- |
| id        | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。   |
| result  | SpeechErrorCode | 错误信息 |
| text  | string | voice语音中包含的文字 |
| voice | bytes  | 合成的voice语音    |
| finish   | bool | 是否是此次合成请求的最后一个语音包 |

##### 说明

1. 接收到第一个数据块就可以开始播放，以加快响应速度




