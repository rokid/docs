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
* [认证设备](https://developer.rokid.com/docs/3-ApiReference/openvoice-auth-api.html)
* 如果认证中 service 为 speech，则此连接后续可进行一次或多次语音交互，直至连接断开
* 如果认证中 service 为 tts，则此连接后续可进行一次或多次语音合成，直至连接断开
* 如果需要同时使用语音识别与语音合成，则需要建立**两条** wss 连接，**每条连接需要分别作认证**


#### 语音合成接入说明

##### 流程
1. 需要先进行 service 为 tts 的 [设备认证](#设备认证)
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




