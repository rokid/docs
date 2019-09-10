## TTS(语音合成) WebSocket接口文档

### 概述

本文档目的是描述Rokid云TTS(语音合成)WebSocket接口协议，面向想要了解TTS细节，并具有一定开发能力的开发者或用户。


### 服务地址

| 环境 | 地址                                   | 用途                   |
| ---- | -------------------------------------- | ---------------------- |
| 线上 | wss://mapi.open.rokid.com/ws/tts       | 对外提供的正式稳定环境 |


### 协议详解

- 请求认证：在建立websocket连接时，通过http header authorization 进行[请求认证](https://developer.rokid.com/docs/3-ApiReference/mapi-doc/gw-auth-api.html)
- TTS语音合成

#### WebSocket API 接入参考Demo
- [WebSocket 接入Demo（JAVA）](https://github.com/Rokid/mapi-demo-outer)




### 协议地址

- [github](https://github.com/Rokid/mapi-demo-outer/tree/master/src/main/proto/outer)

### 协议概述

此协议遵循 [websocket](https://zh.wikipedia.org/zh-cn/WebSocket) 协议。协议采用先认证，再使用的方式，步骤如下：

* 建立 wss 连接，注意是 **websocket + ssl**，在此基础上进行[请求认证](https://developer.rokid.com/docs/3-ApiReference/mapi-doc/gw-auth-api.html)
* service 设置为 tts，此连接后续可进行一次或多次语音合成，直至连接断开



#### 语音合成

##### 流程

1. 一次完整的语音合成的数据包以 id 来标识，称为一个 session
2. 在websocket请求和响应中，都是遵循protobuf 2.0协议的；
3. websocket请求Request通过protobuf组装好后需要转化成BinaryWebSocketFrame，目前不支持TextWebSocketFrame

##### Request如下

| 参数     | 类型        | 描述                   | 默认值  |
| ------ | --------- | -------------------- | ---- |
| text   | string    | 需要转换的text文本          | 空   |
| declaimer | string | 发音人，目前支持 中文成人 "zh" 与 中文儿童 "c1" 两种 | 空 |
| codec     | string | 语音流的编码，目前支持PCM、OPU、OPU2、mp3。   | 空 |
| content_type | string | raw: 返回是二进制语音数据  url: 返回是对应语音数据CDN的url | raw  |
| id        | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。   | 0    |
| midi      | bytes  | 用于歌曲合成使用，二进制midi文件   | 空    |
| score  | string | 歌词信息，用于歌曲合成使用  | 空    |
| options  | string | 可选json字段，配合各种需求使用详见下表  | 空    |


4. websocket响应以流式数据返回，每个BinaryWebSocketFrame对应的是一个Response的字节流，Response如下：
##### Response如下

| 参数    | 类型     | 描述            |
| ----- | ------ | ------------- |
| text  | string | voice语音中包含的文字，如果request的content_type=url，则返回的是保存了文字的url |
| voice | bytes  | 合成的voice语音，如果request的content_type=url，则返回的是语音数据CDN的url    |
| finish   | bool | 是否是此次合成请求的最后一个语音包 |
| result  | string | 结果信息  SUCCESS/ERROR等 |
| id        | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。   |


##### 说明

1. result字段值代表本次请求是否成功，除了SUCCESS，其他返回值都表示错误(此时云端会主动断掉WebSocket连接)，返回值如下：
  - SUCCESS 成功
  - BUSY 云端繁忙/调用受限/欠费
  - UNAUTHENTICATED 验证未通过
  - INTERNAL 云端内部错误
  - BADREQUEST 网络或者协议导致的错误



