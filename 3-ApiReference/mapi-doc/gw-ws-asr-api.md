## ASR(语音识别) WebSocket接口文档(Beta版)

### 概述

本文档目的是描述Rokid云ASR(语音识别)WebSocket接口协议，面向想要了解ASR细节，并具有一定开发能力的开发者或用户。


### 服务地址

| 环境 | 地址                                   | 用途                   |
| ---- | -------------------------------------- | ---------------------- |
| 线上 | wss://mapi.open.rokid.com/ws/asr       | 对外提供的正式稳定环境 |


### 协议详解

- 请求认证：在建立websocket连接时，通过http header authorization 进行[请求认证](./gw-auth-api.md)
- ASR语音识别

#### WebSocket API 接入参考Demo
- [WebSocket 接入Demo（JAVA）](https://github.com/Rokid/mapi-demo-outer)



### 协议地址

- [github](https://github.com/Rokid/mapi-demo-outer/src/main/proto/outer)

### 协议概述

此协议遵循 [websocket](https://zh.wikipedia.org/zh-cn/WebSocket) 协议。协议采用先认证，再使用的方式，步骤如下：

* 建立 wss 连接，注意是 **websocket + ssl**，在此基础上进行[请求认证](./gw-auth-api.md)
* service 设置为 asr，此连接后续可进行一次或多次语音交互，直至连接断开



#### 语音识别

##### 流程

1. 一次完整的语音识别的数据包以 id 来标识，称为一个 session
2. 设备端发送四种类型的数据
   - START 设置 session 的参数数据
   - VOICE 发送 session 的语音数据
   - END 表示 session 结束
   - ONESHOT 当语音数据小于64K时，所有的数据可以在一个请求包发送完时可以用ONESHOT
   - 所有的数据包都要求小于64K
3. 云端返回三种 RespType 的数据
   - INTERMEDIATE 返回 asr 的中间结果
   - FINISH 返回 asr 结果
4. 每个 session 以 FINISH 结束
5. 在websocket请求和响应中，都是遵循protobuf 2.0协议的；
6. websocket请求AsrRequest通过protobuf组装好后需要转化成BinaryWebSocketFrame，目前不支持TextWebSocketFrame

##### AsrRequest


| 参数     | 类型        | 描述                   | 默认值  |
| ------ | --------- | -------------------- | ---- |
| id      | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。同一连接云端同时处理两个id相同的请求可能会出错 | 0     |
| type   | string | START、VOICE、END 或 ONESHOT | 空  |
| options    | Options     | 辅助理解的选项，内容见下表       | 空   |
| voice  | bytes     | 需要识别的语音流      | 空   |


**options 字段的详细说明**

| 参数     | 类型        | 描述                   | 默认值  |
| ------ | --------- | -------------------- | ---- |
| codec | string | 语音流的编码，目前支持 PCM，OPU，OPU2，OPUS，AMRWB，AMRNB，PCM8K。<br />PCM，OPU，OPU2，OPUS，AMRWB 的语音数据格式为单通道，采样率16Khz，16bit；<br />AMRNB，PCM8K的语音数据格式为单通道，采样率8Khz，16bit； | PCM  
| voiceTrigger      | string | 激活词，即用于唤醒设备的名字，如"若琪"；可用 "\|" 分隔指定多个，如 "若琪\|洛奇" | 空   |
| engine    | string | 语音流引擎，目前支持ZH，KID。  | ZH |
| needHotWords    | bool | 是否需要热词，保留字段，暂不生效  | false |
| deviceTypeId    | string | 设备类型，必填  | N/A |
| deviceId    | string | 设备ID，必填  | N/A |
| noIntermediateAsr   | bool | 是否不需要 asr 的实时识别结果 | false   |

##### 说明

1. voice_trigger 激活词：设备的名字，当用户说这个词时，设备会被唤醒，并给出反应。
2. voice的编码格式如下：
   - 识别支持pcm语音流识别，单通道 数据位宽16bit 采样率16kHZ pcm
   - 识别支持opu语音流识别，单通道 数据位宽16bit 采样率16kHZ opu opu压缩每帧数据格式由1字节（数据长度）+ opus压缩320字节数据

##### AsrResponse

| 参数     | 类型     | 描述             |
| ------ | ------ | -------------- |
| id      | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。 |
| type  | string | 结果类型：INTERMEDIATE、FINISH |
| asr    | string | asr实时识别的结果     |
| scores    | Array[float] | asr实时识别的分数，score[0]=per am score; score[1]=glob am score; score[2]=glob lm score     |
| result  | string | 结果信息  SUCCESS/ERROR等 |
| asr_phoneticisms | string | 每个字的拼音结果，json字符串，如“晓”字的拼音为{"phoneticism":"xiao3","word":"晓","type":"CHINESE"} |


##### 说明

1. result字段值代表本次请求是否成功，除了SUCCESS，其他返回值都表示错误(此时云端会主动断掉WebSocket连接)，返回值如下：
  - SUCCESS 成功
  - BUSY 云端繁忙/调用受限/欠费
  - UNAUTHENTICATED 验证未通过
  - UNINITIALIZED 没有发START或者ONESHOT包导致SESSION顺序错误
  - INTERNAL 云端内部错误
  - BADREQUEST 网络或者协议导致的错误




### ASR 云端一些细节

* AsrRequest.id 为 session id，只要确保同一连接下唯一即可(同一连接云端同时并发处理两个id相同的请求可能会出错)
* 同一 session 中，如果有 **2s** 内没有收到下一个语音，则中止 session，按当时 asr 识别出的结果走后续流程
* 任一 session 的语音不允许超过 **10s**，超过即中止，按当时 asr 识别出的结果走后续流程
* 任一 session 中 asr 返回最终结果为 空，则立即返回 {FINISH, SUCCESS, asr(""), ...}
* AsrResponse.result = BUSY 时，可能是云端处理不过来了；可能是当前deviceTypeId类型的请求受限，如欠费等
