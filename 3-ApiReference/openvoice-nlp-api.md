### 开放平台 Websocket 协议 nlp 接口定义文档

### 概述

本文档目的是描述云端语音接口的 WebSocket 版本的开放协议，主要包含语音识别、语义理解、语音合成三大部分功能，主要面向想要了解语音交互细节，并具有一定开发能力的开发者或用户。

### 协议详解

协议可分为以下部分：

- [设备认证](#设备认证)
- [语义理解](#语义理解)（nlp）

#### 索引
  - [服务地址](#服务地址)
  - [协议地址](#协议地址)
  - [协议概述](#协议概述)
  - [协议详解](#协议详解)
    - [设备认证](#设备认证)
    - [语音理解](#语音理解)

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
* 设置认证中 service 为 speech，则此连接后续可进行一次或多次语音理解，直至连接断开

#### 设备认证

##### AuthRequest


| 参数             | 类型     | 描述                     | 默认值  |
| -------------- | ------ | ---------------------- | ---- |
| key            | string | 开放接口Key，在[开放平台语音接入](https://developer.rokid.com/docs/2-RokidDocument/2-EnableVoice/get-the-certification-file.html)获取        | 无，必填 |
| device_type_id | string | 设备类型ID                 | 无，必填 |
| device_id      | string | 设备ID                   | 无，必填 |
| service        | string | tts 或 speech         | 无，必填 |
| version        | string | 接口版本号                  | 无，必填 |
| timestamp      | string | unix时间戳              | 无，必填 |
| sign           | string | 由以上几项及 secret 按约定的加密方式生成 | 无，必填 |

##### 说明

1. 字段 sign 计算方法：


  1. 拼成如下字符串 utf8 的字符串：key={key}&device_type_id={device_type_id}&device_id={device_id}&service={service}&version={version}&time={time}&secret={secret}，其中 ：
     - {xxx} 由 xxx 的值替代
     - key 及 secret 由开发方通过[开放平台语音接入](https://developer.rokid.com/docs/2-RokidDocument/2-EnableVoice/get-the-certification-file.html)获取
  2. 计算 str 字符串的 md5 值

2. 字段 version 有 2.0，分别对应 [协议地址](#%E5%8D%8F%E8%AE%AE%E5%9C%B0%E5%9D%80) 中 v2 目录，目前支持的协议版本：

  - 语义理解： serivce(**speech**)， version(**2**)


##### AuthResponse

| 参数     | 类型    | 描述                |
| ------ | ----- | ----------------- |
| result | int32 | 认证结果(成功:0, 失败:-1) |

##### 说明

1. 当认证失败时，服务端会**主动断开**此连接。

#### 语音理解

##### 流程

1. 需要先进行 service 为 speech 的 [设备认证](#%E8%AE%BE%E5%A4%87%E8%AE%A4%E8%AF%81)
2. 一次完整的语音识别的数据包以 id 来标识，称为一个 session
3. 设备端发送以下的数据
   - TEXT 发送需要理解的文本数据
4. 云端返回 RespType 的数据
   - FINISH 返回 nlp 结果
5. 每个 session 以 FINISH 结束

##### SpeechRequest


| 参数     | 类型        | 描述                   | 默认值  |
| ------ | --------- | -------------------- | ---- |
| id      | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。 | 0     |
| type   | ReqType | TEXT | 空  |
| voice  | bytes     | 需要识别的语音流      | 空   |
| asr    | bytes     | 需要理解的 asr 文本      | 空   |

##### SpeechResponse

| 参数     | 类型     | 描述             |
| ------ | ------ | -------------- |
| id      | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。 |
| result  | SpeechErrorCode | 错误信息 |
| type  | RespType | 结果类型：FINISH |
| asr    | string | asr实时识别的结果     |
| nlp    | string | nlp识别的结果: {"appId": "技能id", "appName": "技能名称", "asr": "asr识别结果", "cloud": "是否为云端技能: true / fasle", "intent": "意图", "pattern": "设定的用户语句","slots": { "槽名称": { "type": "槽类型", "value": "槽的值" }}}|
| action | string | cloud app处理的结果，json字符串 |
| extra | string | 目前有：{"activation": "xxx"} |

