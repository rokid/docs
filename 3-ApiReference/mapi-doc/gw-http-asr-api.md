## ASR(语音识别) HTTP接口文档


### 概述

本文档目的是描述Rokid云ASR(语音识别)Http接口协议，面向想要了解ASR细节，并具有一定开发能力的开发者或用户。


### 服务地址

| 环境 | 地址                                   | 用途                   |
| ---- | -------------------------------------- | ---------------------- |
| 线上 | https://mapi.open.rokid.com/rest/asr/requestid       | 对外提供的正式稳定环境 |


### 协议详解

- 请求认证：在建立http连接时，通过http header authorization 进行权限认证
- ASR语音识别

### HTTP API 接入参考Demo
- [HTTP 接入Demo（JAVA）](https://github.com/Rokid/mapi-demo-outer)

### 协议概述

此协议遵循http协议。协议采用先认证，再使用的方式，步骤如下：

* 建立 https 连接，注意是 **https**，在此基础上进行[请求认证](https://developer.rokid.com/docs/3-ApiReference/mapi-doc/gw-auth-api.html)
* service 设置为 asr，此连接后续可进行一次语音请求



#### 语音识别

##### 请求

1. 需要带包含认证信息的 **authorization** 的 http header [请求认证](https://developer.rokid.com/docs/3-ApiReference/mapi-doc/gw-auth-api.html)
2. 需要带包含asr options信息的 **voice-config**的http header
2. 使用 **HTTP POST** 方式
3. 其中 Content-Type 为 **Content-Type:application/octet-stream**
4. 请求url中的requestid需要自增或者唯一，两个并发请求的requestid相同时可能引发并发错误
5. 一次完整的语音交互序列包含**多个**语音数据时，需要发送如下序列的多个 http post 请求：
   1. 第一个请求的 type 设置为 START，并设置好其它参数，此请求可带上语音数据
   2. 后面的多个请求设置 type  为 VOICE，并带上语音数据
   3. 最后一个请求设置 type 为 END 包表示交互结束，此请求可带上语音数据
   4. 以上请求需要使用相同的url，即相同的requestid
6. 一次完整的语音交互序列只包含**一个**语音数据时，只需发送一个 http post 请求，其中 type 设置为 ONESHOT，并带上语音数据
7. 第1点和第2点的authorization和voice-config http header 只需要在 type=START 或者 type=ONESHOT时设置
8. http header authorization 请看
9. http header voice-config value值组成如下：
 ```text
codec=%s;voice_trigger=%s;engine=%s;need_hotWords=%s
```
 字段说明：
 
| 参数     | 类型        | 描述                   | 默认值  |
| ------ | --------- | -------------------- | ---- |
| codec | string | 语音流的编码，目前支持 PCM，OPU，OPU2，OPUS，AMRWB，AMRNB，PCM8K。<br />PCM，OPU，OPU2，OPUS，AMRWB 的语音数据格式为单通道，采样率16Khz，16bit；<br />AMRNB，PCM8K的语音数据格式为单通道，采样率8Khz，16bit； | PCM  
| voice_trigger      | string | 激活词，即用于唤醒设备的名字，如"若琪"；可用 "\|" 分隔指定多个，如 "若琪\|洛奇" | 空   |
| engine    | string | 语音流引擎，目前支持ZH，KID，ZH-CS。  | ZH |
| need_hotWords    | bool | 是否需要热词，保留字段，暂不生效  | false |

10. http body里面的数据是protobuf 2.0协议的AsrRequest的二进制数据，AsrRequest字段如下是：
  
  
  | 参数     | 类型        | 描述                   | 默认值  |
  | ------ | --------- | -------------------- | ---- |
  | id      | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件| 0     |
  | type   | string | START、VOICE、END 或 ONESHOT | 空  |
  | options    | Options     | http协议里面不起作用       | 空   |
  | voice  | bytes     | 需要识别的语音流      | 空   |
  


##### 响应

| 参数     | 类型     | 描述             |
| ------ | ------ | -------------- |
| id      | int32  | 唯一标识，用于跟踪一个完整的请求，处理及响应事件。 |
| type  | string | 结果类型：INTERMEDIATE、FINISH |
| asr    | string | asr实时识别的结果     |
| scores    | Array[float] | asr实时识别的分数，score[0]=per am score; score[1]=glob am score; score[2]=glob lm score     |
| result  | string | 结果信息  SUCCESS/ERROR等 |
| asr_phoneticisms | string | 每个字的拼音结果，json字符串，如“晓”字的拼音为{"phoneticism":"xiao3","word":"晓","type":"CHINESE"} |


1. 包含**多个**语音数据的语音交互时，仅当是最后一个请求即 type 为 END 的包有以上响应，响应结果是json格式
2. 只包含**一个**语音数据的语音交互时，即 type 为 ONESHOT 的请求同样也有以上响应，响应结果是json格式
3. 其余请求返回为空
4. http code 除了200以外，还有部分非200的code，取值如下：

| code 值         | 涵义           |
| ----------------- | -------------- |
| 400           | Bad Request ：url格式不对，requestId不对或者为空 |
| 405           | 非post方法不可行       |
| 413           | 请求体过大，HTTP BODY 最大支持655350；如果超过这个大小，建议用websocket方式进行流式传输|
| 500           | http协议层错误     |

5. http code 为200时，所有请求成功与否由 result 决定：SUCCESS 为成功，其余的为失败,返回值如下：
  - SUCCESS 成功
  - BUSY 云端繁忙/调用受限/欠费
  - UNAUTHENTICATED 验证未通过
  - UNINITIALIZED 没有发START或者ONESHOT包导致SESSION顺序错误
  - INTERNAL 云端内部错误
  - BADREQUEST 网络或者协议导致的错误

